#ifndef INITEXCEPTION_H
#define INITEXCEPTION_H

#include <exception>

class InitException : public std::exception {
    const char* what() const throw() {
        return "InitException";
    }
};

#endif // INITEXCEPTION_H
