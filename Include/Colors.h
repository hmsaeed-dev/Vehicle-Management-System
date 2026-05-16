#ifndef COLORS_H
#define COLORS_H

#include <string>

/**
 * @file Colors.h
 * @brief ANSI Color Codes for terminal UI enhancement.
 */

namespace Color
{
    const std::string RESET   = "\033[0m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string BOLD    = "\033[1m";

    // Semantic helpers
    const std::string SUCCESS = GREEN;
    const std::string ERR     = RED;
    const std::string WARNING = YELLOW;
    const std::string INFO    = CYAN;
}


#endif // COLORS_H
