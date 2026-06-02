cmake_minimum_required(VERSION 3.16)

project(SARS_Student_Ranking_System LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sars
    src/AppMain.cpp
    src/Club.cpp
    src/DerivedStudents.cpp
    src/ExtracurricularProfile.cpp
    src/GeminiBridge.cpp
    src/InputUtils.cpp
    src/MentalProfile.cpp
    src/Physical.cpp
    src/Student.cpp
    src/StudentRankingSystem.cpp
)
