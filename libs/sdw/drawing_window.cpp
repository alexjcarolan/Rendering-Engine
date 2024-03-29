#include "drawing_window.h"

// Simple constructor method
DrawingWindow::DrawingWindow()
{
}

// Complex constructor method
DrawingWindow::DrawingWindow(int w, int h, bool fullscreen)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
  {
    printMessageAndQuit("Could not initialise SDL: ", SDL_GetError());
  }

  width = w;
  height = h;
  pixelBuffer = new uint32_t[width * height];
  depthBuffer = new float[width * height];
  clearPixels();

  uint32_t flags = SDL_WINDOW_OPENGL;
  if (fullscreen)
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  window = SDL_CreateWindow("Rendering Engine", 0, 0, width, height, flags);
  if (window == 0)
    printMessageAndQuit("Could not set video mode: ", SDL_GetError());

  flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer = SDL_CreateRenderer(window, -1, flags);
  if (renderer == 0)
    printMessageAndQuit("Could not create renderer: ", SDL_GetError());

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer, width, height);

  int PIXELFORMAT = SDL_PIXELFORMAT_ARGB8888;
  texture = SDL_CreateTexture(renderer, PIXELFORMAT, SDL_TEXTUREACCESS_STATIC, width, height);
  if (texture == 0)
    printMessageAndQuit("Could not allocate texture: ", SDL_GetError());
}

// Deconstructor method
void DrawingWindow::destroy()
{
  delete[] pixelBuffer;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void DrawingWindow::renderFrame()
{
  SDL_UpdateTexture(texture, NULL, pixelBuffer, width * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

bool DrawingWindow::pollForInputEvents(SDL_Event *event)
{
  if (SDL_PollEvent(event))
  {
    if ((event->type == SDL_QUIT) || ((event->type == SDL_KEYDOWN) && (event->key.keysym.sym == SDLK_ESCAPE)))
    {
      destroy();
      printMessageAndQuit("Exiting", NULL);
    }
    return true;
  }
  return false;
}

void DrawingWindow::setPixelDepth(int x, int y, float depth)
{
  if ((x < 0) || (x >= width) || (y < 0) || (y >= height))
  {
  }
  else
    depthBuffer[(y * width) + x] = depth;
}

void DrawingWindow::setPixelColour(int x, int y, float depth, uint32_t colour)
{
  if ((x < 0) || (x >= width) || (y < 0) || (y >= height))
  {
  }
  else
  {
    if (getPixelDepth(x, y) >= depth)
    {
      pixelBuffer[(y * width) + x] = colour;
      setPixelDepth(x, y, depth);
    }
  }
}

uint32_t DrawingWindow::getPixelColour(int x, int y)
{
  if ((x < 0) || (x >= width) || (y < 0) || (y >= height))
  {
    return -1;
  }
  else
    return pixelBuffer[(y * width) + x];
}

float DrawingWindow::getPixelDepth(int x, int y)
{
  if ((x < 0) || (x >= width) || (y < 0) || (y >= height))
  {
    return -1;
  }
  else
    return depthBuffer[(y * width) + x];
}

void DrawingWindow::clearPixels()
{
  memset(pixelBuffer, 0, width * height * sizeof(uint32_t));
  memset(depthBuffer, std::numeric_limits<float>::infinity(), width * height * sizeof(float));
}