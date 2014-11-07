#include "pnmhandler.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

Pixmap PnmHandler::loadFrom(std::string filename)
{
   // Open the file for reading ...
   std::ifstream imageStream{filename};

   // ... and validate the presence of this file.
   if(imageStream.fail()) {
      // TODO: Do some error handling here.
      std::cerr << "Failed to open file!" << std::endl;
   }

   // Define a line buffer and match object, ...
   std::string buffer{};
   std::smatch matches;

   // ... initialize pnm type, width, height ...
   PnmComment skipComment;
   std::string magic;
   PnmType type;
   std::size_t width = 0;
   std::size_t height = 0;
   std::size_t maxPixels = 0;
   std::size_t maxValue = 0;

   // ... and parse the pnm header.
   imageStream >> skipComment 
      >> magic >> skipComment 
      >> width >> skipComment 
      >> height >> skipComment;

   std::cout << "Image is of pnm type " << magic << "." << std::endl; 
   std::cout << "Type: " << magic << std::endl
      << "Width: " << width << std::endl 
      << "Height: " << height << std::endl 
      << "Max pixels: " << maxPixels << std::endl;

   std::vector<Color> pixmap(width * height, 0);

   type = static_cast<PnmType>(std::stoi(magic.substr(1,1)));
   std::cout << "Image has pnm type code " << type << "." << std::endl; 

   if (imageStream && type >= 1 && type <= 6 && width > 0 && height > 0) {
      if(type == PnmType::PLAIN_PIXEL_MAP || type == PnmType::PIXEL_MAP) {
         imageStream >> maxPixels >> skipComment;
      }

      if(type == PnmType::PLAIN_GRAYSCALE_MAP || type == PnmType::GRAYSCALE_MAP) {
         imageStream >> maxValue >> skipComment;
      }

      if(type == PnmType::PLAIN_BINARY_MAP || type == PnmType::PLAIN_GRAYSCALE_MAP || type == PnmType::PLAIN_PIXEL_MAP) {
         std::cout << "Parsing plain image content." << std::endl; 
         PnmHandler::readAsciiGrid(imageStream, pixmap, width, height, type);
      } else if(type == PnmType::BINARY_MAP || type == PnmType::GRAYSCALE_MAP || type == PnmType::PIXEL_MAP) {
         std::cout << "Parsing encoded image content." << std::endl; 
         PnmHandler::readBinaryGrid(filename, imageStream.tellg(), pixmap, width, height, type);
      }
   }

   // Finally close the open image file.
   if(imageStream.is_open()) {
      imageStream.close();
   }

   return Pixmap(pixmap, width, height);
}

void PnmHandler::readAsciiGrid(std::ifstream& imageStream, std::vector<Color>& pixmap, std::size_t width, std::size_t height, PnmType type)
{
   PnmComment skipComment;
   int red = 0;
   int green = 0;
   int blue = 0;

   for (std::size_t y = 0; y < height; ++y) {
      for(std::size_t x = 0; x < width; ++x) {
         try {
            imageStream >> red >> skipComment;

            if(type == PnmType::PLAIN_BINARY_MAP) {
               if(red == 0) {
                  pixmap[y * width + x] = Color::WHITE;
               } else {
                  pixmap[y * width + x] = Color::BLACK;
               }
            } else if(type == PnmType::PLAIN_GRAYSCALE_MAP) {
               pixmap[y * width + x] = Color{static_cast<std::uint8_t>(red)};
            } else {
               imageStream >> green >> skipComment;
               imageStream >> blue >> skipComment;

               pixmap[y * width + x] = Color{
                  static_cast<std::uint8_t>(red), 
                  static_cast<std::uint8_t>(green), 
                  static_cast<std::uint8_t>(blue)};
            }
         } catch ( ... ) {
            pixmap[y * width + x] = Color::BLACK;
         }
      }
   }
}

void PnmHandler::readBinaryGrid(std::string filename, std::size_t pos, std::vector<Color>& pixmap, std::size_t width, std::size_t height, PnmType type)
{
   std::uint8_t red = 0;
   std::uint8_t green = 0;
   std::uint8_t blue = 0;
   std::ifstream binaryStream(filename, std::ios::binary | std::ios::in);
   binaryStream.seekg(pos);

   if(type == PnmType::BINARY_MAP) {
      std::cout << "PnmType::BINARY_MAP" << std::endl;
   } else if(type == PnmType::GRAYSCALE_MAP) {
      std::cout << "PnmType::GRAYSCALE_MAP" << std::endl;
   } else if(type == PnmType::PIXEL_MAP) {
      std::cout << "PnmType::PIXEL_MAP" << std::endl;
   }

   char byte;
   for (std::size_t y = 0; y < height; ++y) {
      for(std::size_t x = 0; x < width; ++x) {
         try {
            if(type == PnmType::BINARY_MAP && ((y * width + x) % 8 == 0)) {
               binaryStream.get(byte);
            }

            if(type == PnmType::BINARY_MAP) {
               pos = 7 - (y * width + x) % 8;
               red = static_cast<std::uint8_t>((byte >> pos) & 1);
                  
               if(red == 0) {
                  pixmap[y * width + x] = Color::WHITE;
               } else {
                  pixmap[y * width + x] = Color::BLACK;
               }
            } else if(type == PnmType::GRAYSCALE_MAP) {
               binaryStream.get(byte);
               red = static_cast<std::uint8_t>(byte);
               pixmap[y * width + x] = Color{static_cast<std::uint8_t>(red)};
            } else {
               binaryStream.get(byte);
               red = static_cast<std::uint8_t>(byte);
               binaryStream.get(byte);
               green = static_cast<std::uint8_t>(byte);
               binaryStream.get(byte);
               blue = static_cast<std::uint8_t>(byte);

               pixmap[y * width + x] = Color{static_cast<std::uint8_t>(red), static_cast<std::uint8_t>(green), static_cast<std::uint8_t>(blue)};
            }
         } catch ( ... ) {
            pixmap[y * width + x] = Color::BLACK;
         }
      }
   }
}

bool PnmHandler::saveTo(std::string filename, const Pixmap& pixmap)
{
   // Not implemented yet.
   return true;
}