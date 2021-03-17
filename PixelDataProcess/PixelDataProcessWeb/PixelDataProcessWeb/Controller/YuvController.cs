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
        public async Task<FileStreamResult> SimplestYuv420Split(IFormFile formFile, int width, int height)
        {
            var stream = formFile.OpenReadStream();
            var buffer = new byte[stream.Length];
            var ss = await  stream.ReadAsync(buffer, 0, (int)stream.Length);

            var y = buffer.Skip(0).Take(width * height).ToArray();
            var u = buffer.Skip(width * height ).Take(width * height / 4 ).ToArray();
            var v = buffer.Skip(width * height * 3 / 4).Take(width * height / 4).ToArray();
            
            var outYStream = new MemoryStream(y);
            var outUStream = new MemoryStream(u);
            var outVStream = new MemoryStream(v);
            return File(outYStream, "application/octet-stream", "output_420_y.y");
        }

        [HttpPost("/Yuv420ToGray")]
        public async Task<FileStreamResult> Yuv420ToGray(IFormFile formFile, int width, int height)
        {
            var stream = formFile.OpenReadStream();
            var buffer = new byte[stream.Length];
            await  stream.ReadAsync(buffer, 0, (int)stream.Length);
            
            var y = buffer.Skip(0).Take(width * height).ToArray();
            var append = Enumerable.Repeat((byte) 0x80, width * height / 2).ToArray();
            var resByteArray = y.Concat(append).ToArray();
            
            var outStream = new MemoryStream(resByteArray);
            return File(outStream, "application/octet-stream", "output_gray_256x256_yuv420p.yuv");
        }

        public void SimplestYuv444Split()
        {
            
        }
    }
}