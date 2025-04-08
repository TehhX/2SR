#pragma once

#include <exception>
#include <string>

class TSRException : public std::exception {
protected:
    const std::string err;

public:
    inline TSRException(std::string_view err)
    : err { err } {}

    inline virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
        return err.c_str();
    }
};

class CLIInputException : public TSRException {
public:
    inline CLIInputException(std::string_view err)
    : TSRException(err) {}
};

class LoggerException : public TSRException {
public:
    inline LoggerException(std::string_view err)
    : TSRException(err) {}
};
