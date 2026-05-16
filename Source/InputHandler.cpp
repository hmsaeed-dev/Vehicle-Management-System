#include "InputHandler.h"
#include "Colors.h"
#include "Validator.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

namespace InputHandler
{
    void clearBuffer()
    {
        // When using getline consistently, the buffer is usually clean.
        // We only clear if the fail bit is set.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void waitForEnter()
    {
        cout << "\n" << Color::INFO << "Press Enter to continue..." << Color::RESET;
        string dummy;
        getline(cin, dummy);
    }

    bool isBackKey(const string& input)
    {
        if (input.empty()) return false;
        string upper = input;
        transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return (upper == "Z");
    }

    int getInt(const string& prompt, int min, int max, bool allowCancel)
    {
        string input;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << Color::CYAN << " [Z:Back]" << Color::RESET;
            cout << ": ";
            
            if (!getline(cin, input)) { clearBuffer(); continue; }
            if (input.empty()) continue; 

            if (allowCancel && isBackKey(input)) return CANCEL_INT;

            try {
                size_t pos;
                int value = stoi(input, &pos);
                if (pos == input.length()) {
                    if (Validator::inRange(value, min, max)) return value;
                    cout << Color::ERR << "[ERROR] Out of range (" << min << "-" << max << ")." << Color::RESET << endl;
                } else {
                    throw invalid_argument("Extra characters");
                }
            } catch (...) {
                cout << Color::ERR << "[ERROR] Invalid numeric input. Please enter a whole number." << Color::RESET << endl;
            }
        }
    }

    float getFloat(const string& prompt, float min, float max, bool allowCancel)
    {
        string input;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << Color::CYAN << " [Z:Back]" << Color::RESET;
            cout << ": ";

            if (!getline(cin, input)) { clearBuffer(); continue; }
            if (input.empty()) continue;

            if (allowCancel && isBackKey(input)) return CANCEL_FLOAT;

            try {
                size_t pos;
                float value = stof(input, &pos);
                if (pos == input.length()) {
                    if (Validator::inRange(value, min, max)) return value;
                    cout << Color::ERR << "[ERROR] Out of range." << Color::RESET << endl;
                } else {
                    throw invalid_argument("Extra characters");
                }
            } catch (...) {
                cout << Color::ERR << "[ERROR] Invalid decimal input. Please enter a number." << Color::RESET << endl;
            }
        }
    }

    string getAlphaString(const string& prompt, bool allowCancel)
    {
        string value;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << Color::CYAN << " [Z:Back]" << Color::RESET;
            cout << ": ";

            if (!getline(cin, value)) { clearBuffer(); continue; }

            if (allowCancel && isBackKey(value)) return CANCEL_STR;
            if (value.empty()) {
                cout << Color::ERR << "[ERROR] Input cannot be empty." << Color::RESET << endl;
                continue;
            }
            
            if (Validator::isAlphaOnly(value, true)) return value;

            cout << Color::ERR << "[ERROR] Invalid input. Please use only letters and spaces." << Color::RESET << endl;
        }
    }

    string getString(const string& prompt, bool fullLine, bool allowCancel, bool allowEmpty)
    {
        string value;
        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << Color::CYAN << " [Z:Back]" << Color::RESET;
            cout << ": ";
            
            if (!getline(cin, value)) { clearBuffer(); continue; }

            if (allowCancel && isBackKey(value)) return CANCEL_STR;
            if (allowEmpty || !value.empty()) return value;

            cout << Color::ERR << "[ERROR] Input cannot be empty." << Color::RESET << endl;
        }
    }

    char getChar(const string& prompt, const string& allowedOptions, bool allowCancel)
    {
        string input;
        string options = allowedOptions;
        transform(options.begin(), options.end(), options.begin(), ::toupper);

        while (true)
        {
            cout << prompt;
            if (allowCancel) cout << Color::CYAN << " [Z:Back]" << Color::RESET;
            cout << ": ";
            
            if (!getline(cin, input)) { clearBuffer(); continue; }
            if (input.empty()) continue;

            if (allowCancel && isBackKey(input)) return 'Z'; 
            
            if (input.length() == 1) {
                char value = toupper(input[0]);
                if (options.find(value) != string::npos) return value;
            }

            cout << Color::ERR << "[ERROR] Invalid choice. Allowed: [" << allowedOptions << "]" << (allowCancel ? " or 'Z'." : ".") << Color::RESET << endl;
        }
    }
}


