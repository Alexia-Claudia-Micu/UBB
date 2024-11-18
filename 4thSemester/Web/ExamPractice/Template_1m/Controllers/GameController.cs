using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.EntityFrameworkCore;
using Template_1m.Data;
using Template_1m.Models;
using Template_1m.Models.Entities;

namespace Template_1m.Controllers
{
    public class GameController : Controller
    {
        private readonly ApplicationDbContext _context;

        public GameController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            var userId = int.Parse(HttpContext.Session.GetString("UserId"));
            var games = await _context.Games.Where(g => g.UserId == userId).ToListAsync();
            return View(games);
        }

        [HttpGet]
        public IActionResult Add()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Add(AddGameViewModel viewModel)
        {
            if (ModelState.IsValid)
            {
                // Map viewModel to Game entity
                var game = new Game
                {
                    Name = viewModel.Name,
                    Price = viewModel.Price,
                    ReleaseDate = viewModel.ReleaseDate,
                    UserId = int.Parse(HttpContext.Session.GetString("UserId")) // Set the UserId based on session
                                                                                // Optionally, you can set other properties of Game entity here
                };

                // Add the game to the context and save changes
                _context.Games.Add(game);
                await _context.SaveChangesAsync();

                return RedirectToAction(nameof(Index)); // Redirect to the list of games
            }

            // If ModelState is not valid, return the view with validation errors
            return View(viewModel);
        }

        [HttpGet]

        public async Task<IActionResult> Edit(int id)
        {
            var game = await _context.Games.FindAsync(id);
            return View(game);
        }

        [HttpPost]
        public async Task<IActionResult> Edit(Game viewModel)
        {
            var game = await _context.Games.FindAsync(viewModel.Id);
            if (game is not null)
            {
                game.Name = viewModel.Name;
                game.Price = viewModel.Price;
                game.ReleaseDate = viewModel.ReleaseDate;
                game.UserId = int.Parse(HttpContext.Session.GetString("UserId")); // Set the UserId based on session
                                                                                // Optionally, you can set other properties of Game entity here

               await _context.SaveChangesAsync();
            }
            return RedirectToAction("Index", "Game");
        }


        [HttpPost]
        public async Task<IActionResult> Delete(Game viewModel)
        {
            var game = await _context.Games.AsNoTracking().FirstOrDefaultAsync(x => x.Id == viewModel.Id);
            if (game is not null)
            {
                _context.Games.Remove(viewModel);
                await _context.SaveChangesAsync();
            }
            return RedirectToAction("Index", "Game");
        }
    }
}
