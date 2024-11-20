using System;
using System.IO;
using System.Text.RegularExpressions;

namespace rt;

public class RawCtMask: Geometry
{
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0;
    private readonly Vector _v1;

    public RawCtMask(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) : base(Color.NONE)
    {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines)
        {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution")
            {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            }
            else if (kv[0] == "SliceThickness")
            {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        var diagonal = new Vector(_resolution[0] * _thickness[0] * scale,
                                            _resolution[1] * _thickness[1] * scale,
                                            _resolution[2] * _thickness[2] * scale);

        _v1 = position + diagonal;
        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len)
        {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }
    }

    private ushort Value(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
        {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }

    public override Intersection GetIntersection(Line line, double minDist, double maxDist)
    {
        // Start by computing the intersection of the ray (line) with the 3D bounding box
        var (t1, t2) = GetBoundingBoxIntersections(line);
        if (t1 == null || t2 == null)
        {
            return Intersection.NONE;
        }

        var start = Math.Max(t1 ?? 0, minDist);
        var end = Math.Min(t2 ?? 0, maxDist);

        double stepSize = _scale;
        double firstIntersection = 0d;
        var normal = new Vector();
        Color globalColor = new Color();
        double lastTransparency = 1d; // maximum transparency
        bool passedFirst = false;

        for (var i = start; i <= end; i += stepSize)
        {
            // Calculate the position along the ray at distance 'i'
            var point = line.CoordinateToPosition(i);
            var voxelCoordinates = GetIndexes(point); // Convert the 3D point to voxel indices
            var voxelColor = GetColor(voxelCoordinates); // Get the color of the voxel at these indices
            if (voxelColor.Alpha == 0) continue; // Skip transparent voxels

            // The first time a non-transparent voxel is encountered
            if (!passedFirst)
            {
                firstIntersection = i; // Record 'i' as first intersection
                normal = GetNormal(voxelCoordinates); // Compute the normal for lighting calculations
                passedFirst = true;
            }

            // Accumulate color based on voxel transparency
            globalColor += voxelColor * voxelColor.Alpha * lastTransparency;
            lastTransparency *= 1 - voxelColor.Alpha; // Remaining transparency along the ray

            // If almost no light remains, break the loop
            if (lastTransparency < 1e-10)
                break;
        }

        return new Intersection
        (
            true,
            passedFirst,
            this,
            line,
            firstIntersection,
            normal,
            Material.FromColor(globalColor),
            globalColor
        );
    }

    private Tuple<double?, double?> GetBoundingBoxIntersections(Line line)
    {
        // Calculate the intersections of the ray (line) with the bounding box of the 3D mask
        double tmin = 0;
        double tmax = double.MaxValue;

        // For each axis (X, Y, Z), calculate the intersection points with the box
        for (int i = 0; i < 3; i++)
        {
            double invDir = 0;
            double t0 = 0, t1 = 0;
            // Calculate intersections in each dimension
            switch (i)
            {
                case 0:
                    invDir = 1.0 / line.Dx.X;
                    t0 = (_v0.X - line.X0.X) * invDir;
                    t1 = (_v1.X - line.X0.X) * invDir;
                    break;
                case 1:
                    invDir = 1.0 / line.Dx.Y;
                    t0 = (_v0.Y - line.X0.Y) * invDir;
                    t1 = (_v1.Y - line.X0.Y) * invDir;
                    break;
                case 2:
                    invDir = 1.0 / line.Dx.Z;
                    t0 = (_v0.Z - line.X0.Z) * invDir;
                    t1 = (_v1.Z - line.X0.Z) * invDir;
                    break;
            }

            if (invDir < 0)
            {
                // Swap t0 and t1 if the direction is negative
                (t0, t1) = (t1, t0);
            }

            tmin = Math.Max(tmin, t0);
            tmax = Math.Min(tmax, t1);

            if (tmin > tmax)
            {
                return new Tuple<double?, double?>(null, null); // No intersection with the bounding box
            }
        }

        return new Tuple<double?, double?>(tmin, tmax); // Return the intersection range
    }

    private int[] GetIndexes(Vector v)
    {
        return new[] {
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale),
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)
        };
    }

    private Color GetColor(int[] idx)
    {
        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(int[] idx)
    {
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}