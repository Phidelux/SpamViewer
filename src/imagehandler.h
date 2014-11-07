#ifndef IMAGE_HANDLER_H
#define IMAGE_HANDLER_H

#include "pixmap.h"

class ImageHandler {
public:
   static Pixmap loadFrom(std::string filename);
   static bool saveTo(std::string filename, const Pixmap& pixmap);
};

#endif