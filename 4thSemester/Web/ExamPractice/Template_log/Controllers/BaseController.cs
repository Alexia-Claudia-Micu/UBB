using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;

namespace Template_Log.Controllers
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
