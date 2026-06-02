#pragma once
#include "Student.h"

class EngineeringStudent : public Student {
public:
    EngineeringStudent(const std::string& n);
    std::string getStudentCategory() const override;
    double getExtracurricularScore() const override;
};

class ComputerScienceStudent : public Student {
public:
    ComputerScienceStudent(const std::string& n);
    std::string getStudentCategory() const override;
    double getExtracurricularScore() const override;
};

class LifeScienceStudent : public Student {
public:
    LifeScienceStudent(const std::string& n);
    std::string getStudentCategory() const override;
    double getExtracurricularScore() const override;
};
