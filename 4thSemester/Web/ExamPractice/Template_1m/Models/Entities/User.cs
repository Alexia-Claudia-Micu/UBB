using System.ComponentModel.DataAnnotations;

namespace Template_1m.Models.Entities
{
    public class User
    {
        [Key]
        public int Id { get; set; }
        public string Username { get; set; }
        public string Password { get; set; } // Ideally, store hashed passwords
        public string Email { get; set; }
        public ICollection<Game> Games { get; set; }

    }
}
