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

    // Semantic helpers (basic)
    const std::string SUCCESS = GREEN;
    const std::string ERR     = RED;
    const std::string WARNING = YELLOW;
    const std::string INFO    = CYAN;

    // --- Semantic role colors ---
    // Use these throughout the UI for consistent theming.
    const std::string HEADER            = BOLD + YELLOW;   // Page / module headers
    const std::string SUBHEADER         = BOLD + CYAN;     // Sub-sections and table titles
    const std::string PROMPT            = CYAN;            // User prompts and input hints
    const std::string TABLE_HEADER      = BOLD + CYAN;     // Column headers / table borders
    const std::string NOTICE            = BOLD + BLUE;     // Informational boxed text
    const std::string HIGHLIGHT         = BOLD + MAGENTA;  // Feature highlights

    // Status / category specific
    const std::string STATUS_AVAILABLE  = GREEN;
    const std::string STATUS_RENTED     = RED;
    const std::string STATUS_SOLD       = YELLOW;

    // Category colors (use when displaying categories consistently)
    const std::string CATEGORY_ECONOMY  = GREEN;
    const std::string CATEGORY_LUXURY   = MAGENTA;
    const std::string CATEGORY_SUV      = YELLOW;
    const std::string CATEGORY_VAN      = BLUE;
}


#endif // COLORS_H
