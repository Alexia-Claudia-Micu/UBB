using Microsoft.EntityFrameworkCore;
using Template_1m.Models.Entities;

namespace Template_1m.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options)
        {
        }

        public DbSet<User> Users { get; set; }
        public DbSet<Game> Games { get; set; }
        public DbSet<DC> DCs { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<User>()
                .HasMany(u => u.Games) // User has many Games
                .WithOne(g => g.User) // Game belongs to one User
                .HasForeignKey(g => g.UserId) // Foreign key in Game table
                .IsRequired();

            modelBuilder.Entity<Game>()
                .HasMany(g => g.DCs) // Game has many DCs
                .WithOne(dc => dc.Game) // DC belongs to one Game
                .HasForeignKey(dc => dc.GameId) // Foreign key in DC table
                .IsRequired();
        }
    }
}
