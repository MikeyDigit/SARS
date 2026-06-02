#pragma once
#include <string>
#include <vector>

class MentalActivity {
private:
    std::string type;
    double hoursPerWeek;
    double disciplineScore;

public:
    MentalActivity(std::string t = "", double h = 0.0, double d = 0.0);
    std::string getType() const;
    double getHoursPerWeek() const;
    double getDisciplineScore() const;
    double calculateScore() const;
};

class MentalProfile {
private:
    std::vector<MentalActivity> activities;

public:
    bool hasType(const std::string& type) const;
    bool addActivity(const MentalActivity& activity);
    double calculateScore() const;
    const std::vector<MentalActivity>& getActivities() const;
    void display() const;
};
