#include "StudentRankingSystem.h"
#include "DerivedStudents.h"
#include "InputUtils.h"
#include "Club.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

int StudentRankingSystem::findStudentIndexByName(const std::string& name) const {
    std::string target = toLowerCopy(name);
    for (int i = 0; i < static_cast<int>(students.size()); i++) {
        if (toLowerCopy(students[i]->getName()) == target) return i;
    }
    return -1;
}

std::unique_ptr<Student> StudentRankingSystem::createStudentByCategory(const std::string& name) {
    std::cout << "\nChoose student category:\n";
    std::cout << "1. Engineering\n";
    std::cout << "2. Computer Science\n";
    std::cout << "3. Life Science\n";
    int choice = getIntInRange("Choice: ", 1, 3);
    if (choice == 1) return std::make_unique<EngineeringStudent>(name);
    if (choice == 2) return std::make_unique<ComputerScienceStudent>(name);
    return std::make_unique<LifeScienceStudent>(name);
}

void StudentRankingSystem::addPhysicalAttributes(Student& student) {
    int count = getIntInRange("How many physical activities do you want to add? ", 0, 10);
    for (int i = 0; i < count; i++) {
        std::cout << "\nPhysical Activity " << i + 1 << "\n";
        std::string type = getNonEmptyLine("Activity name: ");
        double hours = getDoubleInRange("Hours per week: ", 0.0, 168.0);
        double intensity = getDoubleInRange("Intensity from 1 to 10: ", 1.0, 10.0);
        if (!student.getPhysicalProfile().addActivity(PhysicalActivity(type, hours, intensity))) {
            std::cout << "This physical activity already exists for this student. Skipped.\n";
        }
    }
}

void StudentRankingSystem::addMentalAttributes(Student& student) {
    int count = getIntInRange("How many mental/discipline activities do you want to add? ", 0, 10);
    for (int i = 0; i < count; i++) {
        std::cout << "\nMental Activity " << i + 1 << "\n";
        std::string type = getNonEmptyLine("Activity name: ");
        double hours = getDoubleInRange("Hours per week: ", 0.0, 168.0);
        double discipline = getDoubleInRange("Discipline score from 1 to 10: ", 1.0, 10.0);
        if (!student.getMentalProfile().addActivity(MentalActivity(type, hours, discipline))) {
            std::cout << "This mental activity already exists for this student. Skipped.\n";
        }
    }
}

void StudentRankingSystem::addExtracurricularAttributes(Student& student) {
    int count = getIntInRange("How many extracurricular activities/clubs do you want to add? ", 0, 10);
    for (int i = 0; i < count; i++) {
        std::cout << "\nExtracurricular " << i + 1 << "\n";
        std::string name = getNonEmptyLine("Club/activity name: ");
        double hours = getDoubleInRange("Hours per week: ", 0.0, 168.0);
        Club club(name, static_cast<float>(hours));
        std::cout << "  [*] Running AI analysis for " << name << "...\n";
        club.runRAGAnalysis();
        if (!student.getExtracurricularProfile().addClub(club)) {
            std::cout << "This extracurricular already exists for this student. Skipped.\n";
        }
    }
}

void StudentRankingSystem::rankStudents() {
    std::sort(students.begin(), students.end(), [](const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b) {
        return a->getFinalScore() > b->getFinalScore();
    });
}

void StudentRankingSystem::addStudent() {
    std::string name = getNonEmptyLine("Enter student name: ");
    if (findStudentIndexByName(name) != -1) {
        std::cout << "A student with this name already exists.\n";
        return;
    }
    std::unique_ptr<Student> student = createStudentByCategory(name);
    addPhysicalAttributes(*student);
    addMentalAttributes(*student);
    addExtracurricularAttributes(*student);
    students.push_back(std::move(student));
    rankStudents();
    std::cout << "\nStudent added successfully.\n";
}

void StudentRankingSystem::removeStudent() {
    if (students.empty()) {
        std::cout << "No students to remove.\n";
        return;
    }
    std::string name = getNonEmptyLine("Enter student name to remove: ");
    int index = findStudentIndexByName(name);
    if (index == -1) {
        std::cout << "Student not found.\n";
        return;
    }
    students.erase(students.begin() + index);
    rankStudents();
    std::cout << "Student removed successfully.\n";
}

void StudentRankingSystem::displayRankings() const {
    if (students.empty()) {
        std::cout << "No students in the system yet.\n";
        return;
    }
    std::cout << "\n===== SARS Rankings =====\n";
    for (int i = 0; i < static_cast<int>(students.size()); i++) {
        students[i]->displaySummary(i + 1);
    }
}

void StudentRankingSystem::displayStudentDetails() const {
    if (students.empty()) {
        std::cout << "No students in the system yet.\n";
        return;
    }
    std::string name = getNonEmptyLine("Enter student name to view: ");
    int index = findStudentIndexByName(name);
    if (index == -1) {
        std::cout << "Student not found.\n";
        return;
    }
    std::cout << "\n===== Student Details =====\n";
    students[index]->displayFull();
}

void StudentRankingSystem::runMenu() {
    std::cout << std::fixed << std::setprecision(2);
    bool running = true;
    while (running) {
        std::cout << "\n===== SARS: Student Academic Ranking System =====\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Display rankings\n";
        std::cout << "3. View student details\n";
        std::cout << "4. Remove student\n";
        std::cout << "5. Exit\n";
        int choice = getIntInRange("Choose an option: ", 1, 5);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: rankStudents(); displayRankings(); break;
            case 3: displayStudentDetails(); break;
            case 4: removeStudent(); break;
            case 5: running = false; break;
        }
    }
    std::cout << "Program ended.\n";
}
