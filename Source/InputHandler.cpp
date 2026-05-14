#include "InputHandler.h"
#include "Colors.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

namespace InputHandler
{
    void clearBuffer()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void waitForEnter()
    {
        cout << "\n" << Color::INFO << "Press Enter to continue..." << Color::RESET;
        // If there was something in the buffer, we might need to clear it first or ignore it
        // cin.get() often picks up the newline from the previous entry
        cin.get();
    }

    int getInt(const string& prompt, int min, int max, bool allowCancel)
    {
        int value;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << " (or 0 to cancel): ";
            
            if (cin >> value)
            {
                if (allowCancel && value == 0) return CANCEL_INT;
                if (value >= min && value <= max)
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return value;
                }
                cout << Color::ERROR << "[ERROR] Input out of range (" << min << "-" << max << ")." << Color::RESET << endl;
            }
            else
            {
                cout << Color::ERROR << "[ERROR] Invalid input. Please enter a number." << Color::RESET << endl;
                clearBuffer();
            }
        }
    }

    float getFloat(const string& prompt, float min, float max, bool allowCancel)
    {
        float value;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << " (or 0 to cancel): ";

            if (cin >> value)
            {
                if (allowCancel && value == 0.0f) return CANCEL_FLOAT;
                if (value >= min && value <= max)
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return value;
                }
                cout << Color::ERROR << "[ERROR] Input out of range." << Color::RESET << endl;
            }
            else
            {
                cout << Color::ERROR << "[ERROR] Invalid input. Please enter a decimal number." << Color::RESET << endl;
                clearBuffer();
            }
        }
    }

    string getAlphaString(const string& prompt, bool allowCancel)
    {
        string value;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << " (type '0' to cancel): ";

            getline(cin >> ws, value);

            if (allowCancel && value == "0") return CANCEL_STR;
            if (value.empty())
            {
                cout << Color::ERROR << "[ERROR] Input cannot be empty." << Color::RESET << endl;
                continue;
            }

            bool allAlpha = true;
            for (char c : value)
            {
                if (!isalpha(c) && !isspace(c))
                {
                    allAlpha = false;
                    break;
                }
            }

            if (allAlpha) return value;

            cout << Color::ERROR << "[ERROR] Invalid input. Use only letters and spaces." << Color::RESET << endl;
        }
    }

    string getString(const string& prompt, bool fullLine, bool allowCancel)
    {
        string value;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << " (type '0' to cancel): ";
            
            // ws discards leading whitespace (including leftover newlines)
            if (fullLine)
                getline(cin >> ws, value);
            else
                cin >> value;

            if (allowCancel && value == "0") return CANCEL_STR;
            if (!value.empty()) return value;

            cout << Color::ERROR << "[ERROR] Input cannot be empty." << Color::RESET << endl;
        }
    }

    char getChar(const string& prompt, const string& allowedOptions, bool allowCancel)
    {
        char value;
        string options = allowedOptions;
        transform(options.begin(), options.end(), options.begin(), ::toupper);

        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << " (or '0' to cancel): ";
            
            cin >> value;
            value = toupper(value);

            if (allowCancel && value == '0') return '0'; // We use '0' as a signal
            
            if (options.find(value) != string::npos)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }

            cout << Color::ERROR << "[ERROR] Invalid choice. Allowed: " << allowedOptions << Color::RESET << endl;
            clearBuffer();
        }
    }
}
