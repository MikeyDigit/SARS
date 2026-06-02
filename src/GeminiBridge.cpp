#define _CRT_SECURE_NO_WARNINGS
#include "GeminiBridge.h"

#include <algorithm>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

std::string GeminiBridge::escapeJsonString(const std::string& input) {
    std::string out;
    out.reserve(input.size());

    for (char c : input) {
        switch (c) {
            case '\\': out += "\\\\"; break;
            case '"':  out += "\\\""; break;
            case '\b': out += "\\b";  break;
            case '\f': out += "\\f";  break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:   out += c;      break;
        }
    }

    return out;
}

std::string GeminiBridge::toLower(std::string data) {
    for (char& c : data) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return data;
}

static std::string offlineKeywordFallback(const std::string& clubName) {
    std::string lowered = GeminiBridge::toLower(clubName);
    std::string keywords;

    auto addKeyword = [&](const std::string& keyword) {
        if (!keywords.empty()) keywords += ", ";
        keywords += keyword;
    };

    if (lowered.find("robot") != std::string::npos) addKeyword("Robotics");
    if (lowered.find("circuit") != std::string::npos || lowered.find("electric") != std::string::npos) addKeyword("Circuit");
    if (lowered.find("cad") != std::string::npos || lowered.find("design") != std::string::npos) addKeyword("CAD");
    if (lowered.find("program") != std::string::npos || lowered.find("coding") != std::string::npos || lowered.find("software") != std::string::npos) addKeyword("Programming");
    if (lowered.find("prototype") != std::string::npos || lowered.find("build") != std::string::npos) addKeyword("Prototyping");
    if (lowered.find("lead") != std::string::npos || lowered.find("president") != std::string::npos || lowered.find("captain") != std::string::npos) addKeyword("Leadership");
    if (lowered.find("outreach") != std::string::npos || lowered.find("volunteer") != std::string::npos) addKeyword("Outreach");
    if (lowered.find("research") != std::string::npos || lowered.find("science") != std::string::npos || lowered.find("biology") != std::string::npos) addKeyword("Analysis");

    if (keywords.empty()) keywords = "General";
    return "{\"text\": \"" + keywords + "\"}";
}

std::string GeminiBridge::fetchRawWebInfo(const std::string& clubName) {
    const char* apiKeyFromEnv = std::getenv("GEMINI_API_KEY");

    if (apiKeyFromEnv == nullptr || std::string(apiKeyFromEnv).empty()) {
        std::cout << "   [AI Notice] GEMINI_API_KEY not set. Using offline keyword fallback.\n";
        return offlineKeywordFallback(clubName);
    }

    const std::string apiKey = apiKeyFromEnv;
    const std::string tempFile = "api_data.json";
    const std::string requestFile = "request.json";
    const std::string modelName = "gemini-2.5-flash";
    const std::string escapedClubName = escapeJsonString(clubName);

    std::ofstream reqOut(requestFile);
    reqOut << "{"
           << "\"contents\":[{"
           << "\"parts\":[{"
           << "\"text\":\"From the following list, return up to 5 keywords which apply to this extracurricular. Be strict. If it is not a real extracurricular, return no keywords: circuit,cad,programming,robotics,analysis,prototyping,management,coordination,leadership,outreach '"
           << escapedClubName
           << "'. Return only a comma-separated list with first letters capitalized.\""
           << "}]"
           << "}]"
           << "}";
    reqOut.close();

    std::ostringstream cmd;
    cmd << "curl -s -X POST "
        << "\"https://generativelanguage.googleapis.com/v1/models/" << modelName << ":generateContent\" "
        << "-H \"x-goog-api-key: " << apiKey << "\" "
        << "-H \"Content-Type: application/json\" "
        << "-d @" << requestFile << " "
        << "> " << tempFile;

    int rc = std::system(cmd.str().c_str());
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    if (rc != 0) {
        std::cout << "[WARN] curl exited with code " << rc << ". Using offline fallback.\n";
        std::remove(requestFile.c_str());
        return offlineKeywordFallback(clubName);
    }

    std::ifstream inFile(tempFile);
    if (!inFile.is_open()) {
        std::remove(requestFile.c_str());
        return offlineKeywordFallback(clubName);
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string response = buffer.str();
    inFile.close();

    std::remove(tempFile.c_str());
    std::remove(requestFile.c_str());
    return response;
}

float GeminiBridge::analyzeContextForRigor(const std::string& rawJson) {
    if (rawJson.empty()) return 1.1f;

    const std::string key = "\"text\": \"";
    std::size_t textPos = rawJson.find(key);

    if (textPos == std::string::npos) {
        if (rawJson.find("\"message\":") != std::string::npos) {
            size_t mStart = rawJson.find("\"message\": \"") + 12;
            size_t mEnd = rawJson.find("\"", mStart);
            std::cout << "   [API Notice] " << rawJson.substr(mStart, mEnd - mStart) << "\n";
        }
        return 1.1f;
    }

    std::string rawKeywords = rawJson.substr(textPos + key.size());
    std::size_t endQuote = rawKeywords.find('"');
    if (endQuote != std::string::npos) rawKeywords = rawKeywords.substr(0, endQuote);

    std::string keywords = toLower(rawKeywords);
    float score = 1.1f;

    if (keywords.find("circuit") != std::string::npos) score += 0.35f;
    if (keywords.find("cad") != std::string::npos) score += 0.30f;
    if (keywords.find("programming") != std::string::npos) score += 0.35f;
    if (keywords.find("robotics") != std::string::npos) score += 0.35f;
    if (keywords.find("prototyping") != std::string::npos) score += 0.30f;
    if (keywords.find("management") != std::string::npos) score += 0.20f;
    if (keywords.find("coordination") != std::string::npos) score += 0.20f;
    if (keywords.find("leadership") != std::string::npos) score += 0.25f;
    if (keywords.find("outreach") != std::string::npos) score += 0.20f;
    if (keywords.find("analysis") != std::string::npos) score += 0.20f;

    return (score > 2.5f) ? 2.5f : score;
}
