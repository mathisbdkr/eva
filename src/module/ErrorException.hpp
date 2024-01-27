/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** ERROR_EXCEPTION_HPP
*/

#ifndef ERROR_EXCEPTION_HPP
#define ERROR_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class FileOpenException : public std::exception {
private:
    std::string message;

public:
    FileOpenException() {};
    ~FileOpenException() noexcept {};
    const char *what() const noexcept {
        return ("File could not be opened.");
    }
};

class OSNotFoundException : public std::exception {
private:
    std::string message;

public:
    OSNotFoundException() {};
    ~OSNotFoundException() noexcept {}
    const char *what() const noexcept {
        return ("OS not found.");
    }
};

#endif /* ERROR_EXCEPTION_HPP */
