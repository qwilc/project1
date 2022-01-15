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
    Header(const std::vector<std::string>& attributes);

    std::vector<std::string> GetAttributes();

    void Print();
};


#endif //PROJECT1_HEADER_H
