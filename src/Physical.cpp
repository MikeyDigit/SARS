#include "Physical.h"
#include "InputUtils.h"
#include <iostream>

PhysicalActivity::PhysicalActivity(std::string t, double h, double i)
    : type(t), hoursPerWeek(h), intensity(i) {}

std::string PhysicalActivity::getType() const { return type; }
double PhysicalActivity::getHoursPerWeek() const { return hoursPerWeek; }
double PhysicalActivity::getIntensity() const { return intensity; }
double PhysicalActivity::calculateScore() const { return hoursPerWeek * intensity; }

bool PhysicalProfile::hasType(const std::string& type) const {
    std::string target = toLowerCopy(type);
    for (const auto& activity : activities) {
        if (toLowerCopy(activity.getType()) == target) return true;
    }
    return false;
}

bool PhysicalProfile::addActivity(const PhysicalActivity& activity) {
    if (hasType(activity.getType())) return false;
    activities.push_back(activity);
    return true;
}

double PhysicalProfile::calculateScore() const {
    double total = 0.0;
    for (const auto& activity : activities) total += activity.calculateScore();
    return total;
}

const std::vector<PhysicalActivity>& PhysicalProfile::getActivities() const {
    return activities;
}

void PhysicalProfile::display() const {
    if (activities.empty()) {
        std::cout << "   None\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(activities.size()); i++) {
        std::cout << "   [" << i + 1 << "] "
                  << activities[i].getType()
                  << " | Hours/Week: " << activities[i].getHoursPerWeek()
                  << " | Intensity: " << activities[i].getIntensity()
                  << " | Score: " << activities[i].calculateScore()
                  << "\n";
    }
}
