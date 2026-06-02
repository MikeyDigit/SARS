#include "MentalProfile.h"
#include "InputUtils.h"
#include <iostream>

MentalActivity::MentalActivity(std::string t, double h, double d)
    : type(t), hoursPerWeek(h), disciplineScore(d) {}

std::string MentalActivity::getType() const { return type; }
double MentalActivity::getHoursPerWeek() const { return hoursPerWeek; }
double MentalActivity::getDisciplineScore() const { return disciplineScore; }
double MentalActivity::calculateScore() const { return hoursPerWeek * disciplineScore; }

bool MentalProfile::hasType(const std::string& type) const {
    std::string target = toLowerCopy(type);
    for (const auto& activity : activities) {
        if (toLowerCopy(activity.getType()) == target) return true;
    }
    return false;
}

bool MentalProfile::addActivity(const MentalActivity& activity) {
    if (hasType(activity.getType())) return false;
    activities.push_back(activity);
    return true;
}

double MentalProfile::calculateScore() const {
    double total = 0.0;
    for (const auto& activity : activities) total += activity.calculateScore();
    return total;
}

const std::vector<MentalActivity>& MentalProfile::getActivities() const {
    return activities;
}

void MentalProfile::display() const {
    if (activities.empty()) {
        std::cout << "   None\n";
        return;
    }
    for (int i = 0; i < static_cast<int>(activities.size()); i++) {
        std::cout << "   [" << i + 1 << "] " << activities[i].getType()
                  << " | Hours/Week: " << activities[i].getHoursPerWeek()
                  << " | Discipline: " << activities[i].getDisciplineScore()
                  << " | Score: " << activities[i].calculateScore() << "\n";
    }
}
