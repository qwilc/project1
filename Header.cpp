//
// Created by qgwil on 1/15/2022.
//

#include "Header.h"

Header::Header(const std::vector<std::string>& attributes) {
    this->attributes = attributes;
}
std::vector<std::string> Header::GetAttributes() {
    return attributes;
}
void Header::Print() {
    for(const std::string& attribute : attributes) {
        std::cout << attribute << ", ";
    }
    std::cout << std::endl;
}