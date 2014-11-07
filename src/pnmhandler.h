#ifndef PNM_HANDLER_H
#define PNM_HANDLER_H

#include "pixmap.h"

#include <istream>
#include <string>

enum PnmType {
	PLAIN_BINARY_MAP = 1,
	PLAIN_GRAYSCALE_MAP,
	PLAIN_PIXEL_MAP,
	BINARY_MAP,
	GRAYSCALE_MAP,
	PIXEL_MAP
};

class PnmHandler {
public:
   static Pixmap loadFrom(std::string filename);
   static bool saveTo(std::string filename, const Pixmap& pixmap);

private:
	static void readAsciiGrid(std::ifstream& imageStream, std::vector<Color>& pixmap, std::size_t width, std::size_t height, PnmType type);
	static void readBinaryGrid(std::string filename, std::size_t pos, std::vector<Color>& pixmap, std::size_t width, std::size_t height, PnmType type);
};

class PnmComment {
public:
	std::istream& operator()(std::istream& is) const {
		is >> std::ws;
		while(is.peek() == '#') {
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			is >> std::ws;
		}

		return is;
	}
};

inline std::istream& operator>>(std::istream& is, const PnmComment& comment) {
   return comment(is);
}

#endif