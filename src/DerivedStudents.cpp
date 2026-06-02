#include "DerivedStudents.h"
#include <map>

EngineeringStudent::EngineeringStudent(const std::string& n) : Student(n) {}

std::string EngineeringStudent::getStudentCategory() const {
    return "Engineering";
}

double EngineeringStudent::getExtracurricularScore() const {
    std::map<std::string, double> weights = {
        {"Robotics", 0.20},
        {"CAD", 0.15},
        {"Circuit", 0.15},
        {"Programming", 0.10},
        {"Prototyping", 0.15},
        {"Technical", 0.10},
        {"Leadership", 0.08}
    };
    return scoreExtracurricularWithWeights(weights);
}

ComputerScienceStudent::ComputerScienceStudent(const std::string& n) : Student(n) {}

std::string ComputerScienceStudent::getStudentCategory() const {
    return "Computer Science";
}

double ComputerScienceStudent::getExtracurricularScore() const {
    std::map<std::string, double> weights = {
        {"Programming", 0.20},
        {"Software", 0.20},
        {"Algorithm", 0.18},
        {"AI", 0.20},
        {"Technical", 0.12},
        {"Analysis", 0.10},
        {"Leadership", 0.05}
    };
    return scoreExtracurricularWithWeights(weights);
}

LifeScienceStudent::LifeScienceStudent(const std::string& n) : Student(n) {}

std::string LifeScienceStudent::getStudentCategory() const {
    return "Life Science";
}

double LifeScienceStudent::getExtracurricularScore() const {
    std::map<std::string, double> weights = {
        {"Research", 0.20},
        {"Biology", 0.18},
        {"Laboratory", 0.18},
        {"Clinical", 0.20},
        {"Analysis", 0.10},
        {"Leadership", 0.05}
    };
    return scoreExtracurricularWithWeights(weights);
}
