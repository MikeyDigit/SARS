#include "MentalProfile.h"

#include <iostream>

MentalActivity::MentalActivity(const std::string& n, double h, double d)
    : name(n), hoursPerWeek(h), disciplineScore(d) {}

std::string MentalActivity::getName() const { return name; }
double MentalActivity::getHoursPerWeek() const { return hoursPerWeek; }
double MentalActivity::getDisciplineScore() const { return disciplineScore; }
double MentalActivity::calculateScore() const { return hoursPerWeek * disciplineScore; }

void MentalProfile::addActivity(const MentalActivity& activity) {
    activities.push_back(activity);
}

double MentalProfile::calculateScore() const {
    double total = 0.0;
    for (const auto& activity : activities) total += activity.calculateScore();
    return total;
}

void MentalProfile::display() const {
    if (activities.empty()) {
        std::cout << "   None\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(activities.size()); i++) {
        std::cout << "   [" << i + 1 << "] " << activities[i].getName()
                  << " | Hours/Week: " << activities[i].getHoursPerWeek()
                  << " | Discipline: " << activities[i].getDisciplineScore()
                  << " | Score: " << activities[i].calculateScore() << "\n";
    }
}
