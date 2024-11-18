using System.Reflection.Metadata;
using Microsoft.EntityFrameworkCore;
using template_pagination.Models.Entities;

namespace template_pagination.Data
{
	public class ApplicationDbContext:DbContext
	{
		public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options)
		{
		}

		public DbSet<Models.Entities.Document> Documents { get; set; }
		public DbSet<Website> Websites { get; set; }
	}
}
