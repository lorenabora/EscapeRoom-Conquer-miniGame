#pragma once

#include <exception>

#ifndef EXCEPTIONSG_H
#define EXCEPTIONSG_H

//clasa pentru exceptia de incarcare a unui fisier
class FileLoadingException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error at loading file!";
    }
};
//clasa pentru exceptia de miscare invalida( o folosesc in entitatea hero)
class InvalidMovementException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error: entity slipped outside the boundaries!";
    }
};
//clasa pentru exceptia atacurilor invalide( folosita in entitatea hero)
class InvalidAttackException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error: invalid attack!";
    }
};

#endif