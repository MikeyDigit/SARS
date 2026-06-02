#pragma once

#include <string>
#include <vector>
#include "Club.h"

class ExtracurricularProfile {
private:
    std::vector<Club> clubs;

public:
    bool hasClub(const std::string& name) const;
    bool addClub(const Club& club);
    const std::vector<Club>& getClubs() const;
    void displayRaw() const;
};
