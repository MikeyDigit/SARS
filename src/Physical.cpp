#include "Physical.h"

#include <iostream>

PhysicalActivity::PhysicalActivity(const std::string& n, double h, double i)
    : name(n), hoursPerWeek(h), intensity(i) {}

std::string PhysicalActivity::getName() const { return name; }
double PhysicalActivity::getHoursPerWeek() const { return hoursPerWeek; }
double PhysicalActivity::getIntensity() const { return intensity; }
double PhysicalActivity::calculateScore() const { return hoursPerWeek * intensity; }

void PhysicalProfile::addActivity(const PhysicalActivity& activity) {
    activities.push_back(activity);
}

double PhysicalProfile::calculateScore() const {
    double total = 0.0;
    for (const auto& activity : activities) total += activity.calculateScore();
    return total;
}

void PhysicalProfile::display() const {
    if (activities.empty()) {
        std::cout << "   None\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(activities.size()); i++) {
        std::cout << "   [" << i + 1 << "] " << activities[i].getName()
                  << " | Hours/Week: " << activities[i].getHoursPerWeek()
                  << " | Intensity: " << activities[i].getIntensity()
                  << " | Score: " << activities[i].calculateScore() << "\n";
    }
}
