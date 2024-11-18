using System.ComponentModel.DataAnnotations;

namespace Template_1m.Models
{
    public class AddDCViewModel
    {
        [Required(ErrorMessage = "The Name field is required.")]
        public string Name { get; set; }

        public bool IsFree { get; set; }
    }
}
