using System.ComponentModel.DataAnnotations;

namespace template_filter.Models.Entities
{
    public class Hotel
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public DateTime Date { get; set; }
        public string City { get; set; }
        public int AvailableRooms { get; set; }

    }
}
