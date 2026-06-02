#include "Club.h"
#include "GeminiBridge.h"

Club::Club(std::string n, float h)
    : name(n), hours(h), multiplier(1.1f) {}

void Club::runRAGAnalysis() {
    response = GeminiBridge::fetchRawWebInfo(name);
    multiplier = GeminiBridge::analyzeContextForRigor(response);
}

std::string Club::getName() const {
    return name;
}

float Club::getHours() const {
    return hours;
}

float Club::getBaseMultiplier() const {
    return multiplier;
}

std::string Club::getRawResponse() const {
    return response;
}
