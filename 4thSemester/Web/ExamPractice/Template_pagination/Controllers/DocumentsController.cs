using System.Reflection.Metadata;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using template_pagination.Data;
using template_pagination.Models;

namespace template_pagination.Controllers
{
    public class DocumentsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public DocumentsController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> UpdateDocuments(int pageNumber = 1, int pageSize = 3)
        {
            var totalDocuments = await _context.Documents.CountAsync();
            var documents = await _context.Documents
                                          .Skip((pageNumber - 1) * pageSize)
                                          .Take(pageSize)
                                          .ToListAsync();

            var viewModel = new PagedDocumentsViewModel
            {
                Documents = documents,
                PageNumber = pageNumber,
                PageSize = pageSize,
                TotalDocuments = totalDocuments
            };

            return View(viewModel);
        }

        public async Task<IActionResult> EditDocuments(int id)
        {
            var document = await _context.Documents.FindAsync(id);
            return View(document);
        }

        [HttpPost]
        public async Task<IActionResult> EditDocuments(Models.Entities.Document viewModel)
        {
            var document = await _context.Documents.FindAsync(viewModel.Id);
            document.Keyword1 = viewModel.Keyword1;
            document.Keyword2 = viewModel.Keyword2;
            document.Keyword3 = viewModel.Keyword3;
            document.Keyword4 = viewModel.Keyword4;
            document.Keyword5 = viewModel.Keyword5;

            await _context.SaveChangesAsync();
            return RedirectToAction("UpdateDocuments");
        }

        public async Task<IActionResult> ListWebsites()
        {
            List<WebsitesViewModel> list = new List<WebsitesViewModel>();
            var websites = await _context.Websites.ToListAsync();
            foreach (var website in websites)
            {
                var documents = await _context.Documents.Where(d => d.IdWebSite == website.Id).ToListAsync();

                WebsitesViewModel viewModel = new WebsitesViewModel
                {
                    Id = website.Id,
                    URL = website.URL,
                    NrDocuments = documents.Count
                };

                list.Add(viewModel);
            }

            return View(list);
        }
    }
}
