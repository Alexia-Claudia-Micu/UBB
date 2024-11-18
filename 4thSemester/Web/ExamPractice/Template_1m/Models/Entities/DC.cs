using System.ComponentModel.DataAnnotations;

namespace Template_1m.Models.Entities
{
    public class DC
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; }
        public bool IsFree { get; set; }
        public int GameId { get; set; } // Foreign key to Game
        public Game Game { get; set; } // Navigation property
    }
}
