using Microsoft.EntityFrameworkCore;
using template_exam.Models.Entities;

namespace template_exam.Data
{
    public class ApplicationDbContext:DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options)
        {
        }

        public DbSet<Movie> Movies { get; set; }
        public DbSet<Author> Authors { get; set; }
        public DbSet<Document> Documents { get; set; }
    }
}
