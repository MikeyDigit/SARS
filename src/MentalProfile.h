#pragma once
#include <string>
#include <vector>

class MentalActivity {
private:
    std::string name;
    double hoursPerWeek;
    double disciplineScore;

public:
    MentalActivity(const std::string& n, double h, double d);
    std::string getName() const;
    double getHoursPerWeek() const;
    double getDisciplineScore() const;
    double calculateScore() const;
};

class MentalProfile {
private:
    std::vector<MentalActivity> activities;

public:
    void addActivity(const MentalActivity& activity);
    double calculateScore() const;
    void display() const;
};
