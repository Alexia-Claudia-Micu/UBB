using System.ComponentModel.DataAnnotations;

namespace template_exam.Models.Entities
{
    public class Document
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Contents { get; set; }
    }
}
