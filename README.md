# SARS — Student Academic Ranking System

SARS is a fully C++ coded student ranking system built as a final project. The program ranks students using more than one category of performance instead of only using academic marks.

The system allows the user to:

- add students
- choose a student category
- enter physical activities
- enter mental/discipline activities
- enter extracurricular activities
- calculate a final score
- rank students from highest to lowest
- view a full score breakdown for each student

This version is organized as a clean GitHub submission and demonstrates both C++ programming skills and responsible AI use.

## What the Project Demonstrates

This project demonstrates:

- object-oriented programming
- classes and objects
- inheritance
- polymorphism
- vectors
- maps
- smart pointers
- input validation
- sorting
- menu-driven console design
- AI-assisted scoring logic
- safe project documentation for GitHub

## AI Use

AI was used as a support tool for planning, debugging, explanation, and improving project structure. The project also includes an AI-style extracurricular keyword scoring system. The code still requires understanding of C++ logic, class design, data flow, and ranking algorithms.

AI was not used as a replacement for learning. The goal was to use AI the same way a developer would use documentation, debugging help, or code review support.

See `AI_USAGE.md` for the full AI-use explanation.

## Build Instructions

### Using CMake

```bash
cmake -S . -B build
cmake --build build
```

Run the program:

```bash
./build/sars
```

On Windows, the executable may be inside:

```text
build/Debug/sars.exe
```

## File Structure

```text
SARS/
├── src/
│   └── SARS.cpp
├── CMakeLists.txt
├── README.md
├── AI_USAGE.md
├── PROJECT_BREAKDOWN.md
└── .gitignore
```

## Project Summary

SARS ranks students using three main score areas:

```text
Final Score = Physical Score + Mental Score + Extracurricular Score
```

Each student belongs to a category such as Engineering, Computer Science, or Life Science. The category affects how extracurricular activities are scored, which shows inheritance and polymorphism in action.