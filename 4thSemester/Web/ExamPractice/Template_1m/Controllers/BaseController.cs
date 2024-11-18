using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;

namespace Template_1m.Controllers
{
    public class BaseController : Controller
    {
        public override void OnActionExecuting(ActionExecutingContext filterContext)
        {
            if (HttpContext.Session.GetString("Username") == null)
            {
                filterContext.Result = RedirectToAction("Login", "Auth");
            }
            else
            {
                base.OnActionExecuting(filterContext);
            }
        }
    }
}
