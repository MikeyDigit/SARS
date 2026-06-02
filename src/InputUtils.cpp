#include "InputUtils.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

int getIntInRange(const std::string& prompt, int minVal, int maxVal) {
    int value;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal && value <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Invalid input. Enter a value from " << minVal << " to " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double getDoubleInRange(const std::string& prompt, double minVal, double maxVal) {
    double value;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal && value <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Invalid input. Enter a value from " << minVal << " to " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getNonEmptyLine(const std::string& prompt) {
    std::string text;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, text);
        if (!text.empty()) return text;
        std::cout << "Input cannot be empty.\n";
    }
}

bool askYesNo(const std::string& prompt) {
    while (true) {
        std::string answer = toLowerCopy(getNonEmptyLine(prompt + " (y/n): "));
        if (answer == "y" || answer == "yes") return true;
        if (answer == "n" || answer == "no") return false;
        std::cout << "Please enter y or n.\n";
    }
}

std::string toLowerCopy(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return s;
}
