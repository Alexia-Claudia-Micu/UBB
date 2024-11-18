using System.ComponentModel.DataAnnotations;

namespace template_filter.Models.Entities
{
    public class Flight
    {
        [Key]
        public int Id { get; set; }
        public DateTime Date { get; set; }
        public string DestinationCity { get; set; }
        public int AvailableSeats { get; set; }
    }
}
