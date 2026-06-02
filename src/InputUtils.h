#pragma once

#include <string>

int getIntInRange(const std::string& prompt, int minVal, int maxVal);
double getDoubleInRange(const std::string& prompt, double minVal, double maxVal);
std::string getNonEmptyLine(const std::string& prompt);
bool askYesNo(const std::string& prompt);
std::string toLowerCopy(std::string s);
