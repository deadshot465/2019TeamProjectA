using SDL2;
using System;

namespace SDL2_Sharp
{
    public class Window
    {
        private IntPtr window;
        private IntPtr surface;
        private SDL.SDL_Event eventHandle;
        public bool IsInit { get; private set; }

        private CoreSystem coreSystem;

        public Window(string title, int width, int height)
        {
            try
            {
                var bounds = new SDL.SDL_Rect();
                bounds.w = width;
                bounds.h = height;

                Helper.ThrowIfFailed(SDL.SDL_Init(SDL.SDL_INIT_VIDEO),
                    "SDL failed to initialize.\n");

                /*
                var displays = SDL.SDL_GetNumVideoDisplays();                
                SDL.SDL_GetCurrentDisplayMode(displays - 1, out SDL.SDL_DisplayMode display_mode);
                SDL.SDL_GetDisplayBounds(displays - 1, out bounds);
                width = bounds.w;
                height = bounds.h;
                */

                window = SDL.SDL_CreateWindow(title,
                    SDL.SDL_WINDOWPOS_CENTERED, SDL.SDL_WINDOWPOS_CENTERED, width, height,
                SDL.SDL_WindowFlags.SDL_WINDOW_SHOWN | SDL.SDL_WindowFlags.SDL_WINDOW_RESIZABLE);
                //SDL.SDL_SetWindowFullscreen(window, (uint)SDL.SDL_WindowFlags.SDL_WINDOW_FULLSCREEN_DESKTOP);

                surface = SDL.SDL_GetWindowSurface(window);

                Helper.ThrowIfFailed(SDL.SDL_UpdateWindowSurface(window),
                    "SDL failed to update the surface.\n");

                coreSystem = new CoreSystem(window, bounds);

                IsInit = true;
            }
            catch (Exception)
            {
                throw;
            }
        }

        ~Window()
        {
            SDL.SDL_FreeSurface(surface);
            SDL.SDL_DestroyWindow(window);
            SDL.SDL_Quit();
        }

        public void Broadcast()
        {
            try
            {
                while (SDL.SDL_PollEvent(out eventHandle) > 0)
                {
                    switch (eventHandle.type)
                    {
                        case SDL.SDL_EventType.SDL_FIRSTEVENT:
                            break;
                        case SDL.SDL_EventType.SDL_QUIT:
                            IsInit = false;
                            break;
                        case SDL.SDL_EventType.SDL_WINDOWEVENT:
                            break;
                        case SDL.SDL_EventType.SDL_SYSWMEVENT:
                            break;
                        case SDL.SDL_EventType.SDL_KEYDOWN:
                            {
                                switch (eventHandle.key.keysym.sym)
                                {
                                    case SDL.SDL_Keycode.SDLK_ESCAPE:
                                        IsInit = false;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            }
                        case SDL.SDL_EventType.SDL_KEYUP:
                            break;
                        case SDL.SDL_EventType.SDL_TEXTEDITING:
                            break;
                        case SDL.SDL_EventType.SDL_TEXTINPUT:
                            break;
                        case SDL.SDL_EventType.SDL_MOUSEMOTION:
                            break;
                        case SDL.SDL_EventType.SDL_MOUSEBUTTONDOWN:
                            break;
                        case SDL.SDL_EventType.SDL_MOUSEBUTTONUP:
                            break;
                        case SDL.SDL_EventType.SDL_MOUSEWHEEL:
                            break;
                        case SDL.SDL_EventType.SDL_JOYAXISMOTION:
                            break;
                        case SDL.SDL_EventType.SDL_JOYBALLMOTION:
                            break;
                        case SDL.SDL_EventType.SDL_JOYHATMOTION:
                            break;
                        case SDL.SDL_EventType.SDL_JOYBUTTONDOWN:
                            break;
                        case SDL.SDL_EventType.SDL_JOYBUTTONUP:
                            break;
                        case SDL.SDL_EventType.SDL_JOYDEVICEADDED:
                            break;
                        case SDL.SDL_EventType.SDL_JOYDEVICEREMOVED:
                            break;
                        case SDL.SDL_EventType.SDL_CONTROLLERAXISMOTION:
                            break;
                        case SDL.SDL_EventType.SDL_CONTROLLERBUTTONDOWN:
                            break;
                        case SDL.SDL_EventType.SDL_CONTROLLERBUTTONUP:
                            break;
                        case SDL.SDL_EventType.SDL_CONTROLLERDEVICEADDED:
                            break;
                        case SDL.SDL_EventType.SDL_CONTROLLERDEVICEREMOVED:
                            break;
                        case SDL.SDL_EventType.SDL_CONTROLLERDEVICEREMAPPED:
                            break;
                        case SDL.SDL_EventType.SDL_FINGERDOWN:
                            break;
                        case SDL.SDL_EventType.SDL_FINGERUP:
                            break;
                        case SDL.SDL_EventType.SDL_FINGERMOTION:
                            break;
                        case SDL.SDL_EventType.SDL_DOLLARGESTURE:
                            break;
                        case SDL.SDL_EventType.SDL_DOLLARRECORD:
                            break;
                        case SDL.SDL_EventType.SDL_MULTIGESTURE:
                            break;
                        case SDL.SDL_EventType.SDL_CLIPBOARDUPDATE:
                            break;
                        case SDL.SDL_EventType.SDL_DROPFILE:
                            break;
                        case SDL.SDL_EventType.SDL_RENDER_TARGETS_RESET:
                            break;
                        case SDL.SDL_EventType.SDL_USEREVENT:
                            break;
                        case SDL.SDL_EventType.SDL_LASTEVENT:
                            break;
                        default:
                            break;
                    }
                }

                coreSystem.ClearColor(0xFF, 0x00, 0xFF);
                coreSystem.Render();

                SDL.SDL_Delay(1);
            }
            catch (Exception)
            {
                throw;
            }
        }
    }
}
