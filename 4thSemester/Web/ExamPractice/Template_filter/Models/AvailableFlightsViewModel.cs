namespace template_filter.Models
{
    public class AvailableFlightsViewModel
    {
        public int Id { get; set; }
        public DateTime Date { get; set; }
        public string DestinationCity { get; set; }
        public int AvailableSeats { get; set; }
    }
}
