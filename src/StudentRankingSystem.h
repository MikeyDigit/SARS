#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Student.h"

class StudentRankingSystem {
private:
    std::vector<std::unique_ptr<Student>> students;

    int findStudentIndexByName(const std::string& name) const;
    std::unique_ptr<Student> createStudentByCategory(const std::string& name);

    void addPhysicalAttributes(Student& student);
    void addMentalAttributes(Student& student);
    void addExtracurricularAttributes(Student& student);

public:
    void rankStudents();
    void addStudent();
    void removeStudent();
    void displayRankings() const;
    void displayStudentDetails() const;
    void runMenu();
};
