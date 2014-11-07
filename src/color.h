#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <vector>
#include <regex>

class Color {
private:
   static const std::regex HEX_COLOR_REGEX;

   std::uint32_t red;
   std::uint32_t green;
   std::uint32_t blue;
   std::uint32_t alpha;

public:
   static const Color BLACK;
   static const Color WHITE;

   Color();
   Color(std::uint32_t val);
   Color(std::string hexCode);
   Color(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a = 0);

   std::vector<std::uint32_t> hex2rgb(std::string hexCode) const;
   std::string rgb2hex(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a = 0) const;
   std::uint32_t getUint() const;

   bool isValidHexColor(std::string hexCode) const;
};

#endif