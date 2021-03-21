namespace PixelDataProcessWeb.BmpHeadParams
{
    public struct  BmpHead
    {
        public long ImageSize { get; set; }

        public long Blank { get; set; }

        public long StartPosition { get; set; }
    }
    public struct  InfoHead
    {
        public long Length { get; set; }

        public long Width { get; set; }

        public long Height { get; set; }

        public ushort ColorPlane { get; set; }

        public ushort BitColor { get; set; }

        public long ZipFormat { get; set; }

        public long RealSize { get; set; }

        public long XPel { get; set; }

        public long YPel { get; set; }

        public long ColorUse { get; set; }

        public long ColorImportant { get; set; }
    }
}