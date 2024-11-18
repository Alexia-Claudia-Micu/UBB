namespace template_pagination.Models
{
    public class PagedDocumentsViewModel
    {
        public List<Entities.Document> Documents { get; set; }
        public int PageNumber { get; set; }
        public int PageSize { get; set; }
        public int TotalDocuments { get; set; }

        public int TotalPages => (int)Math.Ceiling((double)TotalDocuments / PageSize);
    }
}
