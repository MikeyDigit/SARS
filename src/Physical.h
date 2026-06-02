#pragma once

#include <string>
#include <vector>

class PhysicalActivity {
private:
    std::string name;
    double hoursPerWeek;
    double intensity;

public:
    PhysicalActivity(const std::string& n, double h, double i);
    std::string getName() const;
    double getHoursPerWeek() const;
    double getIntensity() const;
    double calculateScore() const;
};

class PhysicalProfile {
private:
    std::vector<PhysicalActivity> activities;

public:
    void addActivity(const PhysicalActivity& activity);
    double calculateScore() const;
    void display() const;
};
