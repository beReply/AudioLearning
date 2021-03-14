using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace PixelDataProcessWeb.Controller
{
    public class YuvController : ControllerBase
    {
        [HttpPost("/SimplestYuv420Split")]
        public async Task<string> SimplestYuv420Split(IFormFile formFile, int width, int height, int num)
        {
            var stream = formFile.OpenReadStream();
            var buffer = new byte[stream.Length];
            var ss = await stream.ReadAsync(buffer, 0, (int)stream.Length);

            var y = buffer.Skip(0).Take(width * height).ToArray();
            var u = buffer.Skip(width * height ).Take(width * height / 4 ).ToArray();
            var v = buffer.Skip(width * height * 3 / 4).Take(width * height / 4).ToArray();

            return "hello";
        }
    }
}