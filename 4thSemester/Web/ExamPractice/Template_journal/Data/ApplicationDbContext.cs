using Microsoft.EntityFrameworkCore;
using template_journal.Models.Entities;

namespace template_journal.Data
{
    public class ApplicationDbContext :DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options)
        {
        }

        public DbSet<Article> Articles { get; set; }
        public DbSet<Journal> Journals { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Journal>()
                .HasMany(j => j.Articles)
                .WithOne(a => a.Journal)
                .HasForeignKey(a => a.JournalId)
                .IsRequired();

        }
    }
}
