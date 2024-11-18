using System.ComponentModel.DataAnnotations;

namespace template_journal.Models.Entities
{
    public class Journal
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public ICollection<Article> Articles { get; set; }

    }
}
