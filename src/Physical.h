#pragma once
#include <string>
#include <vector>

class PhysicalActivity {
private:
    std::string type;
    double hoursPerWeek;
    double intensity;

public:
    PhysicalActivity(std::string t = "", double h = 0.0, double i = 0.0);
    std::string getType() const;
    double getHoursPerWeek() const;
    double getIntensity() const;
    double calculateScore() const;
};

class PhysicalProfile {
private:
    std::vector<PhysicalActivity> activities;

public:
    bool hasType(const std::string& type) const;
    bool addActivity(const PhysicalActivity& activity);
    double calculateScore() const;
    const std::vector<PhysicalActivity>& getActivities() const;
    void display() const;
};
