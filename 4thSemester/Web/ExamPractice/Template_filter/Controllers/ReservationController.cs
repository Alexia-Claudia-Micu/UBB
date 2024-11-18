using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using template_filter.Data;
using template_filter.Models.Entities;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Linq;
using template_filter.Models;

namespace template_filter.Controllers
{
    public class ReservationController : Controller
    {
        private readonly ApplicationDbContext _context;

        public ReservationController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> CancelAllReservations()
        {
            List<Reservation> reservations = await _context.Reservations.ToListAsync();

            foreach (Reservation reservation in reservations)
            {
                if(reservation.Type == "Flight")
                {
                    Flight flight = await _context.Flights.FindAsync(reservation.IdReservedResource);
                    flight.AvailableSeats++;
                    await _context.SaveChangesAsync();
                }
                else
                {
                    Hotel hotel = await _context.Hotels.FindAsync(reservation.IdReservedResource);
                    hotel.AvailableRooms++;
                    await _context.SaveChangesAsync();
                }
            }

            var allReservations = _context.Reservations.ToList();

            // Remove all reservations
            _context.Reservations.RemoveRange(allReservations);

            // Save changes to the database
            await _context.SaveChangesAsync();
            return View();
        }

        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Index(BookingViewModel viewModel)
        {
            TempData["City"] = viewModel.City;
            TempData["Date"] = viewModel.Date;
            TempData["Person"] = viewModel.Person;

            return View(viewModel);
        }

        [HttpGet]
        public async Task<IActionResult> Flights()
        {
            DateTime date = (DateTime)TempData["Date"];
            TempData["Date"] = date;
            string city = (string)TempData["City"];
            TempData["City"] = city;
            List<Flight> flights = await _context.Flights
                .Where(f => f.AvailableSeats > 0 && f.Date == date && f.DestinationCity == city)
                .ToListAsync();
            return View(flights);
        }

        [HttpPost]
        public async Task<IActionResult> BookFlights(int flightId)
        {
            string person = (string)TempData["Person"];
            TempData["Person"] = person;
            Reservation reservation = new Reservation
            {
                Person = person,
                IdReservedResource = flightId,
                Type = "Flight"
            };
            await _context.Reservations.AddAsync(reservation);
            await _context.SaveChangesAsync();

            Flight flight = await _context.Flights.FindAsync(flightId);
            flight.AvailableSeats--;
            await _context.SaveChangesAsync();

            return RedirectToAction("Flights"); // Redirect to Flights after booking
        }

        [HttpPost]
        public async Task<IActionResult> BookHotels(int hotelId)
        {
            string person = (string)TempData["Person"];
            TempData["Person"] = person;

            Reservation reservation = new Reservation
            {
                Person = person,
                IdReservedResource = hotelId,
                Type = "Hotel"
            };
            await _context.Reservations.AddAsync(reservation);
            await _context.SaveChangesAsync();

            Hotel hotel = await _context.Hotels.FindAsync(hotelId);
            hotel.AvailableRooms--;
            await _context.SaveChangesAsync();


            return RedirectToAction("Hotels");
        }

        public async Task<IActionResult> Hotels()
        {
            DateTime date = (DateTime)TempData["Date"];
            TempData["Date"] = date;
            string city = (string)TempData["City"];
            TempData["City"] = city;
            List<Hotel> hotels = await _context.Hotels
                .Where(h => h.City == city && h.AvailableRooms > 0 && h.Date == date)
                .ToListAsync();
            return View(hotels);
        }

        [HttpGet]
        public async Task<IActionResult> Filter(int filter) // you have to make this in list/index to actually see it - check cars project for more
        {
            DateTime date = (DateTime)TempData["Date"];
            TempData["Date"] = date;
            string city = (string)TempData["City"];
            TempData["City"] = city;
            List<Hotel> hotels = await _context.Hotels
                .Where(h => h.City == city && h.AvailableRooms > 0 && h.Date == date && h.AvailableRooms>filter)
                .ToListAsync();
            return RedirectToAction("Hotels");

        }
    }
}
