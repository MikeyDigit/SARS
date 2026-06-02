#ifndef CLUB_H
#define CLUB_H

#include <string>

class Club {
private:
    std::string name;
    std::string response;
    float hours;
    float multiplier;

public:
    Club(std::string n, float h);

    void runRAGAnalysis();

    std::string getName() const;
    float getHours() const;
    float getBaseMultiplier() const;
    std::string getRawResponse() const;
};

#endif
