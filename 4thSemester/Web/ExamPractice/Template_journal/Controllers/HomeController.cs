using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ApplicationModels;
using Microsoft.EntityFrameworkCore;
using template_journal.Data;
using template_journal.Models;
using template_journal.Models.Entities;

namespace template_journal.Controllers
{
    public class HomeController : Controller
    {
        private readonly ApplicationDbContext _context;

        public HomeController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> List(string journalFilter)
        {
            string user = (string)TempData["user"];
			TempData["User"] = user;

            List<Article> articles = string.IsNullOrEmpty(journalFilter)
                ? await _context.Articles.Where(a => a.User == user).ToListAsync()
                :await _context.Articles.Where(a=>a.User == user && a.Journal.Name == journalFilter).ToListAsync();
            foreach(Article article in articles)
            {
                article.Journal = await _context.Journals.FindAsync(article.JournalId);
            }


            return View(articles);
        }

        public IActionResult Login()
        {
            return View(); 
        }
        [HttpPost]
        public IActionResult Login(LoginViewModel viewModel)
        {
            TempData["User"] = viewModel.User;
            return RedirectToAction("List");
        }
    }
}
