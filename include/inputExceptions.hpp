#pragma once

#include <exception>
#include <string>

class TSRInputException : public std::exception {
private:
    const std::string err;

public:
    inline TSRInputException(std::string_view err)
    : err { err } {}

    inline virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
        return err.c_str();
    }
};
