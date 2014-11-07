#include "color.h"

const std::regex Color::HEX_COLOR_REGEX{"^#?([A-Fa-f0-9]{8}|[A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$"};

const Color Color::BLACK{0, 0, 0, 0};
const Color Color::WHITE{255, 255, 255, 0};

Color::Color()
      : red(0), green(0), blue(0), alpha(0)
{

}

Color::Color(std::string hexCode)
{
   std::vector<std::uint32_t> rgba = this->hex2rgb(hexCode);
   this->red = rgba[0];
   this->green = rgba[1];
   this->blue = rgba[2];
   this->alpha = rgba[3];
}

Color::Color(std::uint32_t val)
      : red(val), green(val), blue(val), alpha(0)
{

}

Color::Color(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a)
      : red(r), green(g), blue(b), alpha(a)
{

}

std::vector<std::uint32_t> Color::hex2rgb(std::string hexCode) const
{
   // Initialize the result array ...
   std::vector<std::uint32_t> rgba{0, 0, 0, 0};

   // ... and validate the result.
   if(!isValidHexColor(hexCode)) {
      return rgba;
   }

   // Remove leading hashtag, ...
   if(hexCode.at(0) == '#') {
      hexCode = hexCode.erase(0, 1);
   }

   // ... duplicate entries if too short, ...
   if(hexCode.length() == 3) {
      hexCode.insert(2, 1, hexCode[2]);
      hexCode.insert(1, 1, hexCode[1]);
      hexCode.insert(0, 1, hexCode[0]);
   }

   // ... append missing alpha values ...
   if(hexCode.length() == 6) {
      hexCode.append("00");
   }

   // ... and extract the rgb values.
   std::istringstream(hexCode.substr(0,2)) >> std::hex >> rgba[0];
   std::istringstream(hexCode.substr(2,2)) >> std::hex >> rgba[1];
   std::istringstream(hexCode.substr(4,2)) >> std::hex >> rgba[2];
   std::istringstream(hexCode.substr(6,2)) >> std::hex >> rgba[3];

   return rgba;
}

std::string Color::rgb2hex(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a) const
{
   return "";
}

bool Color::isValidHexColor(std::string hexCode) const
{
   return std::regex_match(hexCode, Color::HEX_COLOR_REGEX);
}

std::uint32_t Color::getUint() const
{
   return (this->red << 16 | this->green << 8 | this->blue);
}