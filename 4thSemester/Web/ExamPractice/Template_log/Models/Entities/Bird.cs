namespace Template_Log.Models.Entities
{
    public class Bird
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Species { get; set; }
        public int UserId { get; set; } // Foreign key to User
        public User User { get; set; }
    }
}
