#include "ExtracurricularProfile.h"
#include "InputUtils.h"

#include <iostream>

bool ExtracurricularProfile::hasClub(const std::string& name) const {
    std::string target = toLowerCopy(name);
    for (const auto& club : clubs) {
        if (toLowerCopy(club.getName()) == target) return true;
    }
    return false;
}

bool ExtracurricularProfile::addClub(const Club& club) {
    if (hasClub(club.getName())) return false;
    clubs.push_back(club);
    return true;
}

const std::vector<Club>& ExtracurricularProfile::getClubs() const {
    return clubs;
}

void ExtracurricularProfile::displayRaw() const {
    if (clubs.empty()) {
        std::cout << "   None\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(clubs.size()); i++) {
        std::cout << "   [" << i + 1 << "] " << clubs[i].getName()
                  << " | Hours/Week: " << clubs[i].getHours()
                  << " | Base Multiplier: " << clubs[i].getBaseMultiplier()
                  << "\n";
    }
}
