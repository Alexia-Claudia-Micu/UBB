namespace Cars.Models.Entities
{
    public class Car
    {
        public Guid Id { get; set; }

        public string Model { get; set; }

        public int EnginePower { get; set; }

        public string Fuel { get; set; }

        public int Price { get; set; }

        public string Color { get; set; }

        public int Age { get; set; }

        public string History { get; set; }


    }
}
