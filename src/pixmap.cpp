#include "pixmap.h"

Pixmap::Pixmap(const std::valarray<Color>& pixmap, std::size_t width, std::size_t height)
      : width(width), height(height), pixmap(pixmap)
{
   // Nothing to do here!
}

Pixmap::Pixmap(const std::vector<Color>& pixmap, std::size_t width, std::size_t height)
      : width(width), height(height), pixmap(pixmap.data(), pixmap.size())
{
   // Nothing to do here!
}

std::size_t Pixmap::getWidth() const
{
   return this->width;
}

std::size_t Pixmap::getHeight() const
{
   return this->height;
}

bool Pixmap::isMonochrome() const
{
   return this->monochrome;
}

std::valarray<Color> Pixmap::getPixmap() const
{
   return this->pixmap;
}

std::uint32_t Pixmap::getPixel(std::size_t x, std::size_t y) const 
{
	return this->pixmap[y * this->width + x].getUint();
}