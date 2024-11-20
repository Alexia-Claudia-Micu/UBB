using System;

namespace rt
{
    class RayTracer
    {
        private Geometry[] geometries;
        private Light[] lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            this.geometries = geometries;
            this.lights = lights;
        }

        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = Intersection.NONE;

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }


        private bool IsLit(Vector point, Light light)
        {
            // Direction from the point to the light source
            Vector directionToLight = (light.Position - point).Normalize();

            // Distance to the light source
            double maxDistance = (light.Position - point).Length();

            // Shadow ray starting slightly off the intersection point to avoid self-intersection
            Line shadowRay = new Line(point + directionToLight * 0.001, light.Position);

            // Check if any geometry blocks the light
            return !Array.Exists(geometries, geometry =>
                !(geometry is RawCtMask) && // Skip RawCtMask geometries
                geometry.GetIntersection(shadowRay, 0.001, maxDistance).Visible);
        }


        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color(0.2, 0.2, 0.2, 1.0);
            var image = new Image(width, height);

            // Normalize the camera and the view vectors
            camera.Normalize();

            // Compute the up direction in the camera's view space
            Vector upDirectionNormalized = (camera.Up ^ camera.Direction).Normalize();
            Vector upNormalized = camera.Up.Normalize();

            // Loop through every pixel in the image
            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    // Calculate the pixel's position in view space
                    double x = ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                    double y = ImageToViewPlane(j, height, camera.ViewPlaneHeight);

                    // Calculate the point on the view plane where the ray intersects
                    Vector pointOnViewPlane = camera.Position +
                                              camera.Direction * camera.ViewPlaneDistance +
                                              upDirectionNormalized * x + upNormalized * y;

                    // Create a ray from the camera to the point on the view plane
                    Line ray = new Line(camera.Position, pointOnViewPlane);

                    // Find the first intersection of the ray with the scene
                    Intersection firstIntersection = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance);

                    // If the intersection is valid and visible, calculate pixel color
                    if (firstIntersection.Visible && firstIntersection.Valid)
                    {
                        Color pixelColor = new Color(); // Initialize the pixel color

                        Material material = firstIntersection.Geometry.Material;
                        Vector normal = firstIntersection.Normal;
                        Vector intersectionToCamera = (camera.Position - firstIntersection.Position).Normalize();

                        // Process each light source to compute lighting effects
                        foreach (var light in lights)
                        {
                            // Ambient light contribution
                            Color ambient = material.Ambient * light.Ambient;

                            // Check if the point is lit by this light
                            if (IsLit(firstIntersection.Position, light))
                            {
                                Vector intersectionToLight = (light.Position - firstIntersection.Position).Normalize();
                                Vector reflection = (normal * (normal * intersectionToLight) * 2 - intersectionToLight).Normalize();

                                // Calculate diffuse lighting
                                double diffuseFactor = Math.Max(0, normal * intersectionToLight);
                                if (diffuseFactor > 0)
                                {
                                    pixelColor += firstIntersection.Material.Diffuse * light.Diffuse * diffuseFactor;
                                }

                                // Calculate specular lighting
                                double specularFactor = Math.Pow(Math.Max(0, intersectionToCamera * reflection), material.Shininess);
                                if (specularFactor > 0)
                                {
                                    pixelColor += material.Specular * light.Specular * specularFactor;
                                }

                                // Apply light intensity
                                pixelColor *= light.Intensity;
                            }

                            // Add ambient light to the pixel color
                            pixelColor += ambient;
                        }

                        image.SetPixel(i, j, pixelColor);
                    }
                    else
                    {
                        image.SetPixel(i, j, background);
                    }
                }
            }

            image.Store(filename);
        }

        private double CalculateDotProduct(Vector a, Vector b)
        {
            return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
        }
    }
}