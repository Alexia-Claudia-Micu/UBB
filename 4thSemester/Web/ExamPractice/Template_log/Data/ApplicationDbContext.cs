using Microsoft.EntityFrameworkCore;
using Template_Log.Models.Entities;

namespace Template_Log.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options)
        {
        }

        public DbSet<User> Users { get; set; }
        public DbSet<Bird> Birds { get; set; }

    }
}
