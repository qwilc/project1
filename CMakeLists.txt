cmake_minimum_required(VERSION 3.17)
project(project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project1
        Automaton.h
        ExactMatchAutomaton.cpp
        ExactMatchAutomaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
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
        Token.h)
