using System;


namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; } 


        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius; 
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            Vector origin = line.X0 - Center;
            Vector direction = line.Dx;

            double a = SemiAxesLength.X;
            double b = SemiAxesLength.Y;
            double c = SemiAxesLength.Z;

            Vector originTransformed = new Vector(origin.X / a, origin.Y / b, origin.Z / c);
            Vector directionTransformed = new Vector(direction.X / a, direction.Y / b, direction.Z / c);

            double A = directionTransformed.X * directionTransformed.X +
                       directionTransformed.Y * directionTransformed.Y +
                       directionTransformed.Z * directionTransformed.Z;

            double B = 2 * (originTransformed.X * directionTransformed.X +
                            originTransformed.Y * directionTransformed.Y +
                            originTransformed.Z * directionTransformed.Z);

            double C = originTransformed.X * originTransformed.X +
                       originTransformed.Y * originTransformed.Y +
                       originTransformed.Z * originTransformed.Z - Radius*Radius;

            double discriminant = B * B - 4 * A * C;

            if (discriminant < 0)
            {
                return Intersection.NONE; 
            }

            double sqrtDiscriminant = Math.Sqrt(discriminant);
            double t1 = (-B - sqrtDiscriminant) / (2 * A);
            double t2 = (-B + sqrtDiscriminant) / (2 * A);

            if (t1 > t2) (t1, t2) = (t2, t1);

            double t = t1;
            if (t < minDist || t > maxDist )
            {
                return Intersection.NONE;
            }

            Vector intersectionPosition = line.CoordinateToPosition(t);
            Vector normal = Normal(intersectionPosition);

            return new Intersection(true, true, this, line, t, normal, Material, Color);
        }

        public Vector Normal(Vector point)
        {
            // Transform the point relative to the center and semi-axis lengths
            Vector relativePoint = new Vector((point.X - Center.X) / (SemiAxesLength.X * SemiAxesLength.X),
                                              (point.Y - Center.Y) / (SemiAxesLength.Y * SemiAxesLength.Y),
                                              (point.Z - Center.Z) / (SemiAxesLength.Z * SemiAxesLength.Z));
            return relativePoint.Normalize();
        }

    }
}