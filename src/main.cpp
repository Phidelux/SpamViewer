#include <iostream>
#include <fstream>
#include "SDL2/SDL.h"

#include "pnmhandler.h"

int main(int argc, char* argv[]) {
   if(argc != 2) {
      std::cerr << "Usage: "<< argv[0] <<" <filename>" << std::endl;
      return 1;
   }

   std::string filename = argv[1];
   std::ifstream imageFile ( filename );
   // Always check to see if file opening succeeded
   if ( !imageFile.is_open() ) {
      std::cerr << "Usage: "<< argv[0] <<" <filename>" << std::endl;
   } else {
      imageFile.close();
   }

   bool running = true;
   SDL_Event event;

   // Read in the pgm file.
   Pixmap pixi = PnmHandler::loadFrom(filename);

   // Initialize SDL.
   if (SDL_Init(SDL_INIT_VIDEO) == 0) {
      // Setup a new SDL window and renderer, ...
      SDL_Window *window = SDL_CreateWindow("Simple PNM Viewer",
         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pixi.getWidth(), pixi.getHeight(), SDL_WINDOW_SHOWN);
      SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

      // ... allocate space for the pixel buffer, ...
      Uint32 * pixels = new Uint32[pixi.getWidth() * pixi.getHeight()];
      memset(pixels, 255, pixi.getWidth() * pixi.getHeight() * sizeof(Uint32));

      // ... setup a texture and pixel buffer ...
      SDL_Texture * texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, pixi.getWidth(), pixi.getHeight());

      //... and draw the image pixel by pixel to the screen.
      for(std::size_t y = 0; y < pixi.getHeight(); ++y) {
         for(std::size_t x = 0; x < pixi.getWidth(); ++x) {
            pixels[y * pixi.getWidth() + x] = pixi.getPixel(x, y);
         }
      }

      if (window) {
         while(running) {
            SDL_UpdateTexture(texture, nullptr, pixels, pixi.getWidth() * sizeof(Uint32));
            SDL_WaitEvent(&event);

            if (event.type == SDL_QUIT) {
                  running = false;
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
         }
      } else {
         std::cerr << "Failed to initialize window!" << std::endl;
         return -1;
      }

      std::cout << "Closing the Application ..." << std::endl;

      delete[] pixels;
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();

      return 0;
   } else {
      std::cerr << "Failed to initialize SDL!" << std::endl;
      return false;
   }

   return 0;
}