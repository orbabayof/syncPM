//
// Created by light on 12/3/24.
//

#ifndef COLOR_H
#define COLOR_H

#include <sstream>
#include <string>

namespace color
{
    inline std::string red(std::string_view text)
    {
        std::ostringstream coloredText {};
        coloredText << "\033[1;31m" << text << "\033[0m";

        return coloredText.str();
    }
}

#endif //COLOR_H
