using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Template_1m.Data;
using Template_1m.Models;
using Template_1m.Models.Entities;

namespace Template_1m.Controllers
{
    public class DCController : Controller
    {
        private readonly ApplicationDbContext _context;
        static int _gameId;

        public DCController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index(int gameId)
        {
            _gameId = gameId;
            var dcs = await _context.DCs.Where(dc => dc.GameId == gameId).ToListAsync();
            return View(dcs);
        }

        [HttpGet]
        public IActionResult Add(int gameId)
        {
            ViewBag.GameId = gameId; // Pass the gameId to the view
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Add(AddDCViewModel viewModel)
        {
            if (ModelState.IsValid)
            {
                var dc = new DC
                {
                    Name = viewModel.Name,
                    IsFree = viewModel.IsFree,
                    GameId = _gameId
                };

                _context.DCs.Add(dc);
                await _context.SaveChangesAsync();

                return RedirectToAction(nameof(Index), new { gameId = _gameId });
            }

            return View(viewModel);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(DC viewModel)
        {
            var dc = await _context.DCs.FindAsync(viewModel.Id);
            if (dc is not null)
            {
                dc.Name = viewModel.Name;
                dc.IsFree = viewModel.IsFree;

                await _context.SaveChangesAsync();

                return RedirectToAction("Index", new { gameId = dc.GameId });
            }

            return View(viewModel);
        }
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Delete(int id)
        {
            var dc = await _context.DCs.FindAsync(id);
            if (dc is not null)
            {
                var gameId = dc.GameId; // Get the GameId before deletion
                _context.DCs.Remove(dc);
                await _context.SaveChangesAsync();

                return RedirectToAction("Index", new { gameId });
            }

            return NotFound();
        }

    }
}