#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

using namespace std;

string lowerText(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return static_cast<char>(tolower(c));
    });
    return text;
}

string getLineInput(const string& prompt) {
    string value;
    do {
        cout << prompt;
        getline(cin, value);
        if (value.empty()) cout << "Input cannot be empty.\n";
    } while (value.empty());
    return value;
}

int getIntInput(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Enter a number from " << minValue << " to " << maxValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getDoubleInput(const string& prompt, double minValue, double maxValue) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Enter a value from " << minValue << " to " << maxValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

class PhysicalActivity {
private:
    string name;
    double hours;
    double intensity;

public:
    PhysicalActivity(string activityName, double weeklyHours, double activityIntensity)
        : name(activityName), hours(weeklyHours), intensity(activityIntensity) {}

    string getName() const { return name; }
    double getHours() const { return hours; }
    double getIntensity() const { return intensity; }
    double score() const { return hours * intensity; }
};

class MentalActivity {
private:
    string name;
    double hours;
    double discipline;

public:
    MentalActivity(string activityName, double weeklyHours, double disciplineScore)
        : name(activityName), hours(weeklyHours), discipline(disciplineScore) {}

    string getName() const { return name; }
    double getHours() const { return hours; }
    double getDiscipline() const { return discipline; }
    double score() const { return hours * discipline; }
};

class Club {
private:
    string name;
    double hours;

public:
    Club(string clubName, double weeklyHours) : name(clubName), hours(weeklyHours) {}
    string getName() const { return name; }
    double getHours() const { return hours; }
};

class Student {
protected:
    string name;
    vector<PhysicalActivity> physicalActivities;
    vector<MentalActivity> mentalActivities;
    vector<Club> clubs;

    bool containsKeyword(const string& text, const string& keyword) const {
        return lowerText(text).find(lowerText(keyword)) != string::npos;
    }

    double keywordExtracurricularScore(const vector<pair<string, double>>& weights) const {
        double total = 0.0;

        for (const Club& club : clubs) {
            double multiplier = 1.0;

            for (const auto& weight : weights) {
                if (containsKeyword(club.getName(), weight.first)) {
                    multiplier += weight.second;
                }
            }

            if (multiplier > 2.5) multiplier = 2.5;
            total += club.getHours() * multiplier;
        }

        return total;
    }

public:
    Student(string studentName) : name(studentName) {}
    virtual ~Student() = default;

    string getName() const { return name; }
    virtual string getCategory() const = 0;
    virtual double getExtracurricularScore() const = 0;

    void addPhysicalActivity(const PhysicalActivity& activity) {
        physicalActivities.push_back(activity);
    }

    void addMentalActivity(const MentalActivity& activity) {
        mentalActivities.push_back(activity);
    }

    void addClub(const Club& club) {
        clubs.push_back(club);
    }

    double getPhysicalScore() const {
        double total = 0.0;
        for (const PhysicalActivity& activity : physicalActivities) total += activity.score();
        return total;
    }

    double getMentalScore() const {
        double total = 0.0;
        for (const MentalActivity& activity : mentalActivities) total += activity.score();
        return total;
    }

    double getFinalScore() const {
        return getPhysicalScore() + getMentalScore() + getExtracurricularScore();
    }

    void displaySummary(int rank) const {
        cout << left << setw(5) << rank
             << setw(22) << name
             << setw(18) << getCategory()
             << setw(12) << fixed << setprecision(1) << getPhysicalScore()
             << setw(12) << getMentalScore()
             << setw(18) << getExtracurricularScore()
             << setw(12) << getFinalScore() << "\n";
    }

    void displayDetails() const {
        cout << "\n===== Student Breakdown =====\n";
        cout << "Name: " << name << "\n";
        cout << "Category: " << getCategory() << "\n";

        cout << "\nPhysical Activities:\n";
        if (physicalActivities.empty()) cout << "  None\n";
        for (const PhysicalActivity& activity : physicalActivities) {
            cout << "  " << activity.getName()
                 << " | Hours: " << activity.getHours()
                 << " | Intensity: " << activity.getIntensity()
                 << " | Score: " << activity.score() << "\n";
        }

        cout << "\nMental Activities:\n";
        if (mentalActivities.empty()) cout << "  None\n";
        for (const MentalActivity& activity : mentalActivities) {
            cout << "  " << activity.getName()
                 << " | Hours: " << activity.getHours()
                 << " | Discipline: " << activity.getDiscipline()
                 << " | Score: " << activity.score() << "\n";
        }

        cout << "\nExtracurriculars:\n";
        if (clubs.empty()) cout << "  None\n";
        for (const Club& club : clubs) {
            cout << "  " << club.getName() << " | Hours: " << club.getHours() << "\n";
        }

        cout << "\nFinal Score: " << getFinalScore() << "\n";
    }
};

class EngineeringStudent : public Student {
public:
    EngineeringStudent(string name) : Student(name) {}
    string getCategory() const override { return "Engineering"; }

    double getExtracurricularScore() const override {
        return keywordExtracurricularScore({
            {"robotics", 1.0}, {"engineering", 0.9}, {"design", 0.7},
            {"prototype", 0.7}, {"baja", 0.8}, {"stem", 0.6}
        });
    }
};

class ComputerScienceStudent : public Student {
public:
    ComputerScienceStudent(string name) : Student(name) {}
    string getCategory() const override { return "Computer Science"; }

    double getExtracurricularScore() const override {
        return keywordExtracurricularScore({
            {"programming", 1.0}, {"coding", 1.0}, {"software", 0.9},
            {"ai", 0.9}, {"hackathon", 0.8}, {"robotics", 0.5}
        });
    }
};

class LifeScienceStudent : public Student {
public:
    LifeScienceStudent(string name) : Student(name) {}
    string getCategory() const override { return "Life Science"; }

    double getExtracurricularScore() const override {
        return keywordExtracurricularScore({
            {"biology", 1.0}, {"health", 0.9}, {"medical", 0.9},
            {"research", 0.8}, {"hospital", 0.8}, {"science", 0.6}
        });
    }
};

class StudentRankingSystem {
private:
    vector<unique_ptr<Student>> students;

    Student* findStudentByName(const string& name) const {
        string target = lowerText(name);
        for (const auto& student : students) {
            if (lowerText(student->getName()) == target) return student.get();
        }
        return nullptr;
    }

    void sortStudents() {
        sort(students.begin(), students.end(), [](const unique_ptr<Student>& a, const unique_ptr<Student>& b) {
            return a->getFinalScore() > b->getFinalScore();
        });
    }

public:
    void addStudent() {
        string name = getLineInput("Enter student name: ");

        cout << "\nChoose category:\n";
        cout << "1. Engineering\n";
        cout << "2. Computer Science\n";
        cout << "3. Life Science\n";
        int choice = getIntInput("Choice: ", 1, 3);

        unique_ptr<Student> student;
        if (choice == 1) student = make_unique<EngineeringStudent>(name);
        else if (choice == 2) student = make_unique<ComputerScienceStudent>(name);
        else student = make_unique<LifeScienceStudent>(name);

        int physicalCount = getIntInput("How many physical activities? ", 0, 10);
        for (int i = 0; i < physicalCount; i++) {
            cout << "\nPhysical Activity " << i + 1 << "\n";
            string activityName = getLineInput("Activity name: ");
            double hours = getDoubleInput("Hours per week: ", 0, 80);
            double intensity = getDoubleInput("Intensity from 1 to 10: ", 1, 10);
            student->addPhysicalActivity(PhysicalActivity(activityName, hours, intensity));
        }

        int mentalCount = getIntInput("How many mental/discipline activities? ", 0, 10);
        for (int i = 0; i < mentalCount; i++) {
            cout << "\nMental Activity " << i + 1 << "\n";
            string activityName = getLineInput("Activity name: ");
            double hours = getDoubleInput("Hours per week: ", 0, 80);
            double discipline = getDoubleInput("Discipline score from 1 to 10: ", 1, 10);
            student->addMentalActivity(MentalActivity(activityName, hours, discipline));
        }

        int clubCount = getIntInput("How many extracurriculars/clubs? ", 0, 10);
        for (int i = 0; i < clubCount; i++) {
            cout << "\nExtracurricular " << i + 1 << "\n";
            string clubName = getLineInput("Club/activity name: ");
            double hours = getDoubleInput("Hours per week: ", 0, 80);
            student->addClub(Club(clubName, hours));
        }

        students.push_back(move(student));
        cout << "\nStudent added successfully.\n";
    }

    void displayRankings() {
        if (students.empty()) {
            cout << "No students in the system yet.\n";
            return;
        }

        sortStudents();
        cout << "\n===== SARS Rankings =====\n";
        cout << left << setw(5) << "Rank"
             << setw(22) << "Name"
             << setw(18) << "Category"
             << setw(12) << "Physical"
             << setw(12) << "Mental"
             << setw(18) << "Extracurricular"
             << setw(12) << "Final" << "\n";
        cout << string(99, '-') << "\n";

        for (size_t i = 0; i < students.size(); i++) {
            students[i]->displaySummary(static_cast<int>(i + 1));
        }
    }

    void viewStudentDetails() const {
        if (students.empty()) {
            cout << "No students in the system yet.\n";
            return;
        }

        string name = getLineInput("Enter student name to search: ");
        Student* student = findStudentByName(name);

        if (student == nullptr) {
            cout << "Student not found.\n";
        } else {
            student->displayDetails();
        }
    }

    void removeStudent() {
        if (students.empty()) {
            cout << "No students to remove.\n";
            return;
        }

        string name = getLineInput("Enter student name to remove: ");
        string target = lowerText(name);

        auto oldSize = students.size();
        students.erase(remove_if(students.begin(), students.end(), [&](const unique_ptr<Student>& student) {
            return lowerText(student->getName()) == target;
        }), students.end());

        if (students.size() < oldSize) cout << "Student removed.\n";
        else cout << "Student not found.\n";
    }

    void loadDemoData() {
        auto engineering = make_unique<EngineeringStudent>("Michael Di Giacinto");
        engineering->addPhysicalActivity(PhysicalActivity("Volleyball", 8, 8));
        engineering->addMentalActivity(MentalActivity("C++ project development", 6, 9));
        engineering->addClub(Club("Robotics and engineering design team", 5));
        engineering->addClub(Club("STEM outreach", 3));
        students.push_back(move(engineering));

        auto cs = make_unique<ComputerScienceStudent>("Alex Chen");
        cs->addPhysicalActivity(PhysicalActivity("Gym", 4, 7));
        cs->addMentalActivity(MentalActivity("Algorithm practice", 7, 8));
        cs->addClub(Club("Programming club and AI hackathon", 6));
        students.push_back(move(cs));

        auto life = make_unique<LifeScienceStudent>("Sara Patel");
        life->addPhysicalActivity(PhysicalActivity("Running", 5, 6));
        life->addMentalActivity(MentalActivity("Research reading", 5, 8));
        life->addClub(Club("Medical science research club", 6));
        students.push_back(move(life));

        cout << "Demo students loaded.\n";
    }

    void runMenu() {
        cout << fixed << setprecision(1);
        bool running = true;

        while (running) {
            cout << "\n===== SARS: Student Academic Ranking System =====\n";
            cout << "1. Add student\n";
            cout << "2. Display rankings\n";
            cout << "3. View student details\n";
            cout << "4. Remove student\n";
            cout << "5. Load demo data\n";
            cout << "6. Exit\n";

            int choice = getIntInput("Choose an option: ", 1, 6);

            switch (choice) {
                case 1: addStudent(); break;
                case 2: displayRankings(); break;
                case 3: viewStudentDetails(); break;
                case 4: removeStudent(); break;
                case 5: loadDemoData(); break;
                case 6: running = false; break;
            }
        }

        cout << "Program ended.\n";
    }
};

int main() {
    StudentRankingSystem system;
    system.runMenu();
    return 0;
}
