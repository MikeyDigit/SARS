# SARS — Student Academic Ranking System

SARS is a fully C++ coded student ranking system built as a final project. The program ranks students using more than one category of performance instead of only using academic marks.

The system allows the user to:

- add students
- choose a student category
- enter physical activities
- enter mental/discipline activities
- enter extracurricular activities
- use a Gemini bridge / offline fallback to analyze extracurricular context
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
- Gemini API bridge design
- safe project documentation for GitHub

## AI Use

AI was used as a support tool for planning, debugging, explanation, and improving project structure. The project also includes an AI-style extracurricular keyword scoring system through `GeminiBridge.cpp` and `Club.cpp`.

The public GitHub version does **not** hardcode an API key. To use the Gemini bridge, set an environment variable using `.env.example` as a guide:

```text
GEMINI_API_KEY=your_key_here
```

If no key is set, the project uses an offline keyword fallback so the program can still run safely.

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
│   ├── AppMain.cpp
│   ├── StudentRankingSystem.cpp / .h
│   ├── Student.cpp / .h
│   ├── DerivedStudents.cpp / .h
│   ├── Physical.cpp / .h
│   ├── MentalProfile.cpp / .h
│   ├── ExtracurricularProfile.cpp / .h
│   ├── Club.cpp / .h
│   ├── GeminiBridge.cpp / .h
│   └── InputUtils.cpp / .h
├── CMakeLists.txt
├── README.md
├── AI_USAGE.md
├── PROJECT_BREAKDOWN.md
├── .env.example
└── .gitignore
```

## Project Summary

SARS ranks students using three main score areas:

```text
Final Score = Physical Score + Mental Score + Extracurricular Score
```

Each student belongs to a category such as Engineering, Computer Science, or Life Science. The category affects how extracurricular activities are scored, which shows inheritance and polymorphism in action.

The extracurricular score is supported by `Club` and `GeminiBridge`, where the program attempts to classify the context of extracurricular activities using Gemini. If Gemini is unavailable, an offline keyword fallback is used.