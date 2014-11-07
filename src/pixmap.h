#ifndef PIXMAP_H
#define PIXMAP_H

#include <string>
#include <vector>
#include <valarray>

#include "color.h"

class Pixmap {
private:
   std::size_t width;
   std::size_t height;
   std::valarray<Color> pixmap;
   bool monochrome;

public:
   Pixmap(const std::valarray<Color>& pixmap, std::size_t width, std::size_t height);
   Pixmap(const std::vector<Color>& pixmap, std::size_t width, std::size_t height);

   std::size_t getWidth() const;
   std::size_t getHeight() const;
   bool isMonochrome() const;

   std::valarray<Color> getPixmap() const;
   std::uint32_t getPixel(std::size_t x, std::size_t y) const;
};

#endif