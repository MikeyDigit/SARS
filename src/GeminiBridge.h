#ifndef GEMINI_BRIDGE_H
#define GEMINI_BRIDGE_H

#include <string>

class GeminiBridge {
public:
    static std::string escapeJsonString(const std::string& input);
    static std::string toLower(std::string data);
    static std::string fetchRawWebInfo(const std::string& clubName);
    static float analyzeContextForRigor(const std::string& rawJson);
};

#endif
