//
// Created by qgwil on 9/28/2021.
//

#include "DatalogProgram.h"
#include <sstream>

std::string DatalogProgram::toString() {
    std::stringstream output;

    output << "Schemes(" << schemes.size() << "):" << std::endl;
    for(unsigned int i = 0; i < schemes.size(); i++) {
        output << "  " << schemes.at(i).toString() << std::endl;
    }

    output << "Facts(" << facts.size() << "):" << std::endl;
    for(unsigned int i = 0; i < facts.size(); i++) {
        output << "  " << facts.at(i).toString() << "." << std::endl;
    }

    output << "Rules(" << rules.size() << "):" << std::endl;
    for(unsigned int i = 0; i < rules.size(); i++) {
        output << "  " << rules.at(i).toString() << std::endl;
    }

    output << "Queries(" << queries.size() << "):" << std::endl;
    for(unsigned int i = 0; i < queries.size(); i++) {
        output << "  " << queries.at(i).toString() << "?" << std::endl;
    }

    output << "Domain(" << domain.size() << "):" << std::endl;
    for(std::string s : domain) {
        output << "  " << s << std::endl; //TODO: should there be a new line at the very end?
    }

    std::string returnStr = output.str();
    returnStr = returnStr.substr(0, returnStr.size()-1);

    return returnStr;
}
