using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using Template_1m.Models.Entities;

namespace Template_1m.Models
{
    public class AddGameViewModel
    {
        [Required(ErrorMessage = "The Name field is required.")]
        public string Name { get; set; }

        [Required(ErrorMessage = "The Price field is required.")]
        [Range(0, int.MaxValue, ErrorMessage = "Please enter a valid price.")]
        public int Price { get; set; }

        [Required(ErrorMessage = "The Release Date field is required.")]
        [DataType(DataType.Date)]
        public DateTime ReleaseDate { get; set; }

        // Additional properties if needed
    }
}
