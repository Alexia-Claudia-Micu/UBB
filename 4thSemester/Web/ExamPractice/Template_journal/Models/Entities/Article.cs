using System.ComponentModel.DataAnnotations;

namespace template_journal.Models.Entities
{
    public class Article
    {
        [Key]
        public int Id { get; set; }
        public string User {  get; set; }
        public int JournalId { get; set; }
        public Journal Journal { get; set; }
        public string Summary {  get; set; }
        public DateTime Date { get; set; }
    }
}
