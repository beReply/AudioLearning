namespace PixelDataProcessWeb.Extensions
{
    public static  class TypeExtension
    {
        /// <summary>
        /// 使用不安全的方式获取类型T的size
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public static unsafe int UnsafeGetSize<T>() where T : unmanaged
        {
            return sizeof(T);
        }
    }
}