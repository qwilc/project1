cmake_minimum_required(VERSION 3.17)
project(project1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(project1
        Automaton.h
        ExactMatchAutomaton.cpp
        ExactMatchAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h
        Parser.cpp
        Parser.h
        DatalogProgram.h
        DatalogProgram.cpp
        Parameter.h
        Parameter.cpp
        Predicate.h
        Predicate.cpp
        Rule.h
        Rule.cpp
        Database.h
        Relation.h
        Header.h
        Tuple.h
        Interpreter.h
        Graph.h
        )
