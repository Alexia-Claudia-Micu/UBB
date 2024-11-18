using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Template_Log.Data;
using Template_Log.Models.Entities;

namespace Template_Log.Controllers
{
    [Authorize]
    public class BirdController : Controller
    {
        private readonly ApplicationDbContext _context;

        public BirdController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            var userId = int.Parse(HttpContext.Session.GetString("UserId"));
            var birds = await _context.Birds.Where(b => b.UserId == userId).ToListAsync();
            return View(birds);
        }

        public IActionResult Create()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create(Bird bird)
        {
            if (ModelState.IsValid)
            {
                bird.UserId = int.Parse(HttpContext.Session.GetString("UserId"));
                _context.Add(bird);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(bird);
        }
    }
}
