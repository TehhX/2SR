#pragma once

#include <exception>
#include <string>

// General exception class for 2SR that all others derive from
class TSRException : public std::exception {
private:
    const std::string err;

protected:
    inline TSRException(std::string_view err)
    : err { err } {}

public:
    inline virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
        return err.c_str();
    }
};

// Error with inputting data
class CLIInputException : public TSRException {
public:
    inline CLIInputException(std::string_view err)
    : TSRException { err } {}
};

// Error with recording data
class LoggerException : public TSRException {
public:
    inline LoggerException(std::string_view err)
    : TSRException { err } {}
};

// Error with converting a card's elements (suit, value) to string or vice versa
class CardConversionException : public TSRException {
public:
    inline CardConversionException(std::string_view err)
    : TSRException { err } {}
};
