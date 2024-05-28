using Cars.Data;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Cars.Models;
using Cars.Models.Entities;
using Cars.Data;
using Microsoft.AspNetCore.Authorization;

namespace Cars.Controllers
{
    public class CarsController : Controller
    {
        private readonly ApplicationDbContext dbContext;
        public CarsController(ApplicationDbContext dBContext)
        {
            this.dbContext = dBContext;
        }

        [HttpGet]
        public IActionResult Add()
        {
            return View();
        }

        [HttpPost]
        [Authorize]

        public async Task<IActionResult> Add(AddCarViewModel viewModel)
        {
            var car = new Car
            {
                Model = viewModel.Model,
                Fuel = viewModel.Fuel,
                EnginePower = viewModel.EnginePower,
                Price = viewModel.Price,
                Age = viewModel.Age,
                History = viewModel.History,
                Color = viewModel.Color
            };

            await dbContext.Cars.AddAsync(car);
            await dbContext.SaveChangesAsync();
            if (car is not null)
            {
                await dbContext.SaveChangesAsync();
            }
            return RedirectToAction("List", "Cars");
        }

        [HttpGet]
        [Authorize]
        public async Task<IActionResult> List(string selectedModel)
        {
            var models = await dbContext.Cars.Select(c => c.Model).Distinct().ToListAsync();
            var cars = string.IsNullOrEmpty(selectedModel)
                ? await dbContext.Cars.ToListAsync()
                : await dbContext.Cars.Where(c => c.Model == selectedModel).ToListAsync();

            ViewBag.Models = models;
            ViewBag.SelectedModel = selectedModel;
            ViewBag.PreviouslyFilteredBy = "Model";

            return View(cars);
        }



        [HttpGet]
        [Authorize]

        public async Task<IActionResult> Edit(Guid id)
        {
            var car = await dbContext.Cars.FindAsync(id);
            return View(car);
        }

        [HttpPost]
        public async Task<IActionResult> Edit(Car viewModel)
        {
            var car = await dbContext.Cars.FindAsync(viewModel.Id);
            if (car is not null)
            {
                car.Model = viewModel.Model;
                car.EnginePower = viewModel.EnginePower;
                car.Fuel = viewModel.Fuel;
                car.Price = viewModel.Price;
                car.Color = viewModel.Color;
                car.Age = viewModel.Age;
                car.History = viewModel.History;

                await dbContext.SaveChangesAsync();
            }
            return RedirectToAction("List", "Cars");
        }

        [HttpPost]
        public async Task<IActionResult> Delete(Car viewModel)
        {
            var car = await dbContext.Cars.AsNoTracking().FirstOrDefaultAsync(x => x.Id == viewModel.Id);
            if (car is not null)
            {
                dbContext.Cars.Remove(viewModel);
                await dbContext.SaveChangesAsync();
            }
            return RedirectToAction("List", "Cars");
        }
    }
}
