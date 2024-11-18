using System.ComponentModel.DataAnnotations;

namespace template_exam.Models.Entities
{
    public class Author
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public string DocumentList { get; set; }
        public string MovieList { get; set; }
    }
}
