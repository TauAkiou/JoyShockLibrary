//
// Created by robin on 3/9/21.
//

#ifndef JOYSHOCKLIBRARY_CONTROLLEREXCEPTIONS_H
#define JOYSHOCKLIBRARY_CONTROLLEREXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>
#include <memory>


class ControllerTimeout : public std::runtime_error {
private:
    int jsl_handle = 0;
public:
    ControllerTimeout(int handle) : std::runtime_error("") {
        jsl_handle = handle;
        auto str = "Controller handle " + std::to_string(jsl_handle) + " has disconnected.";
        static_cast<std::runtime_error&>(*this) = std::runtime_error(str);
    }
};

#endif //JOYSHOCKLIBRARY_CONTROLLEREXCEPTIONS_H
