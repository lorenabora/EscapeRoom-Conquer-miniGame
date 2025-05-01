#pragma once

#include <exception>

#ifndef EXCEPTIONSG_H
#define EXCEPTIONSG_H

class FileLoadingException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error at loading file!";
    }
};

class InvalidMovementException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error: entity slipped outside the boundaries!";
    }
};

class InvalidAttackException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error: invalid attack!";
    }
};

#endif