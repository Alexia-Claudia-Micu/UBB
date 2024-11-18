using System.ComponentModel.DataAnnotations;

namespace template_pagination.Models.Entities
{
	public class Document
	{
		[Key]
		public int Id { get; set; }
		public int IdWebSite {  get; set; }
		public string Keyword1 { get; set; }
		public string Keyword2 { get; set; }
		public string Keyword3 { get; set; }
		public string Keyword4 { get; set; }
		public string Keyword5 { get; set; }
	}
}
