using System.ComponentModel.DataAnnotations;

namespace template_pagination.Models.Entities
{
	public class Website
	{
		[Key]
		public int Id { get; set; }
		public string URL { get; set; }
	}
}
