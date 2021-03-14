using Microsoft.AspNetCore.Mvc;

namespace PixelDataProcessWeb.Controller
{
    public class TestController : ControllerBase
    {
        [HttpPost("Test")]
        public string Test()
        {
            return "test";
        }
    }
}