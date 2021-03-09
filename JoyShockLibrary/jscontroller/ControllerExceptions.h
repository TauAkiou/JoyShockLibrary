//
// Created by robin on 3/9/21.
//

#ifndef JOYSHOCKLIBRARY_CONTROLLEREXCEPTIONS_H
#define JOYSHOCKLIBRARY_CONTROLLEREXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>


class ControllerTimeout : public std::exception {
private:
    int jsl_handle = 0;
public:
    const char * what() const noexcept override {
        return "Controller " + std::to_string(jsl_handle).c_str() + "has timed out.";
    }
};

#endif //JOYSHOCKLIBRARY_CONTROLLEREXCEPTIONS_H
