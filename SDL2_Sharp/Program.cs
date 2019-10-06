using System;

namespace SDL2_Sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                var window = new Window("SDL Game", Helper.WINDOW_WIDTH, Helper.WINDOW_HEIGHT);

                while (window.IsInit)
                {
                    window.Broadcast();
                }
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine(ex.Message);
            }
        }
    }
}
