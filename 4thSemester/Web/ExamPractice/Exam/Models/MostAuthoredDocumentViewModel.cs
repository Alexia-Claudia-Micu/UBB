using System.Globalization;

namespace template_exam.Models
{
    public class MostAuthoredDocumentViewModel
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Contents {  get; set; }
        public int Authors {  get; set; }
    }
}
