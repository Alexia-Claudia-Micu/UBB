using System.ComponentModel.DataAnnotations;

namespace Template_1m.Models.Entities
{
    public class Game
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public int Price { get; set; }
        public DateTime ReleaseDate { get; set; }
        public int UserId { get; set; } // Foreign key to User
        public User User { get; set; } // Navigation property

        // Navigation property for DCs related to this game
        public ICollection<DC> DCs { get; set; }
    }
}