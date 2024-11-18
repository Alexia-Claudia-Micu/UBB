using System.Reflection.Metadata;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using template_exam.Data;
using template_exam.Models;
using template_exam.Models.Entities;

namespace template_exam.Controllers
{
    public class AuthorsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public AuthorsController(ApplicationDbContext context)
        {
           _context = context;
        }

        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Login(LoginViewModel viewModel)
        {
            var author = await _context.Authors.FirstOrDefaultAsync(a => a.Name == viewModel.Name);
            if(author is not null)
            {
                string docs = author.DocumentList;
                string movies = author.MovieList;

                List<string> docss = docs.Split(',').ToList();
                List<string> moviess = movies.Split(',').ToList();

                foreach(string doc in docss)
                {
                    if (int.Parse(doc) == viewModel.Creation) 
                    {
                        TempData["Author"] = viewModel.Name;
                        return RedirectToAction("Index", "Home"); 
                    }
                }
                foreach(string movie in moviess)
                {
                    if (int.Parse(movie) == viewModel.Creation)
                    {
                        TempData["Author"] = viewModel.Name;
                        return RedirectToAction("Index", "Home");
                    }
                }
            }

            return View(viewModel);
        }

        public IActionResult AddDocument()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> AddDocument(Models.Entities.Document document)
        {
            Models.Entities.Document doc = new Models.Entities.Document
            {
                Name = document.Name,
                Contents = document.Contents
            };
            await _context.Documents.AddAsync(doc);
            await _context.SaveChangesAsync();

            string authorName = (string)TempData["Author"];
            TempData["Author"] = authorName;

            var author = await _context.Authors.FirstOrDefaultAsync(a => a.Name == authorName);

            string docs = author.DocumentList + "," + doc.Id;
            author.DocumentList = docs;
            await _context.SaveChangesAsync();
            return View();
        }

        public async Task<IActionResult> MostAuthoredDocument()
        {
            int maxNr = 0;
            int docId = 0;
            Dictionary<string, int> nrAuthorsForEachDoc = new Dictionary<string, int>();
            var authors = await _context.Authors.ToListAsync();
            foreach(var author in authors)
            {
                var docList = author.DocumentList;
                List<string> docs = docList.Split(",").ToList();
                foreach(var doc in docs)
                {
                    if (nrAuthorsForEachDoc.ContainsKey(doc))
                        nrAuthorsForEachDoc[doc]++;
                    else
                        nrAuthorsForEachDoc[doc] = 1;

                    if (nrAuthorsForEachDoc[doc] > maxNr)
                    {
                        maxNr = nrAuthorsForEachDoc[doc];
                        docId = int.Parse(doc);
                    }
                }
            }
            var document = await _context.Documents.FindAsync(docId);
            MostAuthoredDocumentViewModel viewModel = new MostAuthoredDocumentViewModel
            {
                Id = docId,
                Name = document.Name,
                Contents = document.Contents,
                Authors = maxNr
            };
            return View(viewModel);
        }

        public async Task<IActionResult> ListInterleaved()
        {
            List<ListInterleaved> viewModel = new List<ListInterleaved>();
            var movies = await _context.Movies.ToListAsync();
            var docs = await _context.Documents.ToListAsync();
            int i = 0;
            int j = 0;
            while(i < movies.Count && j < docs.Count)
            {
                var model = new ListInterleaved
                {
                    Movie = movies[i].Title,
                    Doc = docs[i].Name
                };
                viewModel.Add(model);
                i++;
                j++;
            }
            while(i < movies.Count)
            {
                var model = new ListInterleaved
                {
                    Movie = movies[i].Title
                };
                viewModel.Add(model);
                i++;
            }
            while (j < docs.Count)
            {
                var model = new ListInterleaved
                {
                    Doc = docs[i].Name
                };
                viewModel.Add(model);
                j++;
            }

            return View(viewModel);
        }

    }
}
