#pragma once
#include <map>
#include <string>
#include "Physical.h"
#include "MentalProfile.h"
#include "ExtracurricularProfile.h"

class Student {
protected:
    std::string name;
    PhysicalProfile physical;
    MentalProfile mental;
    ExtracurricularProfile extracurricular;
    double scoreExtracurricularWithWeights(const std::map<std::string, double>& weights) const;

public:
    Student(const std::string& n = "");
    virtual ~Student() = default;

    std::string getName() const;
    PhysicalProfile& getPhysicalProfile();
    MentalProfile& getMentalProfile();
    ExtracurricularProfile& getExtracurricularProfile();
    const PhysicalProfile& getPhysicalProfile() const;
    const MentalProfile& getMentalProfile() const;
    const ExtracurricularProfile& getExtracurricularProfile() const;

    double getPhysicalScore() const;
    double getMentalScore() const;
    virtual double getExtracurricularScore() const = 0;
    virtual std::string getStudentCategory() const = 0;
    double getFinalScore() const;

    void displaySummary(int rank) const;
    void displayFull() const;
};
