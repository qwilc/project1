//
// Created by qgwil on 10/22/2021.
//

#ifndef PROJECT1_HEADER_H
#define PROJECT1_HEADER_H
#include <vector>
#include <string>
#include <iostream>


class Header {
private:
    std::vector<std::string> attributes;
public:
    Header(const std::vector<std::string>& attributes) {
        this->attributes = attributes;
    }
    std::vector<std::string> GetAttributes() {
        return attributes;
    }
    void Print() {
        for(std::string attribute : attributes) {
            std::cout << attribute << ", ";
        }
        std::cout << std::endl;
    }
};


#endif //PROJECT1_HEADER_H
