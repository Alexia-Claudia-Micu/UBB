using System.ComponentModel.DataAnnotations;

namespace template_exam.Models.Entities
{
    public class Movie
    {
        [Key]
        public int Id { get; set; }
        public string Title { get; set; }
        public int Duration { get; set; }
    }
}
