using template_journal.Models.Entities;

namespace template_journal.Models
{
	public class ArticleViewModel
	{
		public string User { get; set; }
		public int JournalId { get; set; }
		public Journal Journal { get; set; }
		public string Summary { get; set; }
		public DateTime Date { get; set; }
	}
}
