#include "Student.h"
#include "InputUtils.h"
#include <iostream>

Student::Student(const std::string& n) : name(n) {}

std::string Student::getName() const { return name; }

PhysicalProfile& Student::getPhysicalProfile() { return physical; }
MentalProfile& Student::getMentalProfile() { return mental; }
ExtracurricularProfile& Student::getExtracurricularProfile() { return extracurricular; }

const PhysicalProfile& Student::getPhysicalProfile() const { return physical; }
const MentalProfile& Student::getMentalProfile() const { return mental; }
const ExtracurricularProfile& Student::getExtracurricularProfile() const { return extracurricular; }

double Student::getPhysicalScore() const { return physical.calculateScore(); }
double Student::getMentalScore() const { return mental.calculateScore(); }

double Student::scoreExtracurricularWithWeights(const std::map<std::string, double>& weights) const {
    double total = 0.0;

    for (const auto& club : extracurricular.getClubs()) {
        double adjustedMultiplier = club.getBaseMultiplier();
        std::string info = toLowerCopy(club.getRawResponse() + " " + club.getName());

        for (const auto& pair : weights) {
            if (info.find(toLowerCopy(pair.first)) != std::string::npos) {
                adjustedMultiplier += pair.second;
            }
        }

        if (adjustedMultiplier > 2.5) adjustedMultiplier = 2.5;
        total += club.getHours() * adjustedMultiplier;
    }

    return total;
}

double Student::getFinalScore() const {
    return getPhysicalScore() + getMentalScore() + getExtracurricularScore();
}

void Student::displaySummary(int rank) const {
    std::cout << rank << ". " << name
              << " | Category: " << getStudentCategory()
              << " | Physical: " << getPhysicalScore()
              << " | Mental: " << getMentalScore()
              << " | Extracurricular: " << getExtracurricularScore()
              << " | Final: " << getFinalScore()
              << "\n";
}

void Student::displayFull() const {
    std::cout << "Name: " << name << "\n";
    std::cout << "Category: " << getStudentCategory() << "\n";

    std::cout << "\nPhysical Profile:\n";
    physical.display();
    std::cout << "Physical Score: " << getPhysicalScore() << "\n";

    std::cout << "\nMental Profile:\n";
    mental.display();
    std::cout << "Mental Score: " << getMentalScore() << "\n";

    std::cout << "\nExtracurricular Profile:\n";
    extracurricular.displayRaw();
    std::cout << "Extracurricular Score: " << getExtracurricularScore() << "\n";

    std::cout << "Final Score: " << getFinalScore() << "\n";
}
