cmake_minimum_required(VERSION 3.27)
project(cs236)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lab1)
include_directories(project1)

add_executable(cs236
        lab0/hello.cpp
        lab1/main.cpp
        lab1/Scanner.h
        lab1/Token.h
        project1/main.cpp
        project1/Scanner.h
        project1/Token.h
        project2-practice/Predicate.h
        lab2/Parser.h
        project2/Parser.h
        project2/DatalogProgram.h
        project2/Parameter.h
        project2/Predicate.h
        project2/Rule.h
        project2/Scanner.h
        project2/Token.h
        lab3/Scheme.h
        lab3/Tuple.h
        lab3/main.cpp
        lab3/Relation.h
        project3/main.cpp
        project3/DatalogProgram.h
        project3/Database.h
        p4-practice/Interpreter.h
        p4-practice/Predicate.h
        p4-practice/Parser.h
        p4-practice/Parameter.h
        p4-practice/Database.h
        p4-practice/DatalogProgram.h
        p4-practice/main.cpp
        project5/Node.h
        project5/Graph.h
        project5/Rule.h
        project5/Interpreter.h
        project5/Rule.h
)
