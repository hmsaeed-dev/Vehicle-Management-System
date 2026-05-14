#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>

/**
 * @namespace InputHandler
 * @brief Provides robust, fail-safe methods for gathering user input.
 * Handles buffer clearing, type validation, and range checking.
 */
namespace InputHandler
{
    // Special constants for "Go Back" / "Cancel" actions
    const int CANCEL_INT = -1;
    const float CANCEL_FLOAT = -1.0f;
    const std::string CANCEL_STR = "__CANCEL__";

    /**
     * @brief Reads an integer from console with validation.
     * @param prompt The message shown to user.
     * @param min Minimum valid value.
     * @param max Maximum valid value.
     * @param allowCancel If true, entering 0 returns CANCEL_INT.
     */
    int getInt(const std::string& prompt, int min = 0, int max = 1000000, bool allowCancel = false);

    /**
     * @brief Reads a float from console with validation.
     */
    float getFloat(const std::string& prompt, float min = 0.0f, float max = 1000000.0f, bool allowCancel = false);

    /**
     * @brief Reads a string and ensures it only contains alphabetic characters and spaces.
     */
    std::string getAlphaString(const std::string& prompt, bool allowCancel = false);

    /**
     * @brief Reads a single word or a full line of text.
     */
    std::string getString(const std::string& prompt, bool fullLine = true, bool allowCancel = false);

    /**
     * @brief Reads a single character and validates against a list of allowed options.
     */
    char getChar(const std::string& prompt, const std::string& allowedOptions, bool allowCancel = false);

    /**
     * @brief Utility to wait for the user to press Enter.
     */
    void waitForEnter();

    /**
     * @brief Clears the cin buffer and reset fail flags.
     */
    void clearBuffer();
}

#endif // INPUT_HANDLER_H
