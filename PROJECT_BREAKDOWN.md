# SARS Project Breakdown

## Project Name

SARS — Student Academic Ranking System

## Main Purpose

SARS is a C++ console application that ranks students using multiple performance categories. Instead of only comparing grades, the system evaluates physical activity, mental discipline, and extracurricular involvement.

The purpose of the project is to show that a C++ program can be built as a real system with multiple classes, data structures, functions, and scoring logic.

## Main Features

- Add students
- Select a student category
- Add physical activities
- Add mental activities
- Add extracurricular activities
- Calculate category scores
- Calculate a final score
- Sort and rank students
- Display rankings
- View a full student breakdown
- Remove students from the system

## Main C++ Concepts Used

```text
classes
objects
inheritance
polymorphism
vectors
maps
smart pointers
functions
loops
conditionals
sorting
input validation
```

## Class Design

### Student

`Student` is the abstract base class. It stores the shared data that every student has, including their name and activity profiles.

It also contains common scoring functions such as:

```cpp
double getPhysicalScore() const;
double getMentalScore() const;
double getFinalScore() const;
```

Because `Student` has pure virtual functions, it cannot be created directly. A specific type of student must be created instead.

### EngineeringStudent, ComputerScienceStudent, LifeScienceStudent

These are derived classes. Each one represents a different student category.

Each category scores extracurriculars differently. For example, robotics and prototyping are stronger for Engineering, while programming and AI are stronger for Computer Science.

This demonstrates polymorphism because the same function call can behave differently depending on the actual student type.

### StudentRankingSystem

`StudentRankingSystem` controls the full program.

It is responsible for:

- storing students
- running the menu
- adding students
- removing students
- sorting students
- displaying rankings
- showing student details

The student list is stored using:

```cpp
vector<unique_ptr<Student>> students;
```

This allows different student types to be stored in the same vector.

## Scoring System

The final score is calculated using:

```text
Final Score = Physical Score + Mental Score + Extracurricular Score
```

Physical score uses:

```text
hours per week × intensity
```

Mental score uses:

```text
hours per week × discipline score
```

Extracurricular score uses:

```text
hours per week × category-based multiplier
```

## AI Demonstration

The project demonstrates AI use in two ways:

1. AI was used during development for debugging, explanation, and structure.
2. The program includes AI-style keyword classification for extracurricular scoring.

This allows the system to treat activities differently based on the student's pathway. For example, the keyword `Robotics` is weighted more heavily for Engineering, while `Programming` is weighted more heavily for Computer Science.

## Why This Project Is Useful

This project is useful because it turns C++ concepts into a complete system. It is not just a calculator or a single function. It has classes that interact, stores data dynamically, validates input, ranks results, and separates logic into meaningful parts.

## Future Improvements

Future improvements could include:

- saving and loading data from files
- exporting rankings to CSV
- adding academic grades
- adding a GUI
- connecting to a real AI API
- adding unit tests
- adding a login/admin system