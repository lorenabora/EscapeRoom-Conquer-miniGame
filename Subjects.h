#pragma once

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>
#include <algorithm>
#include <iostream>

class Subjects 
{
private:
    std::vector<Observer*> observers;  //Lista observatorilor

public:
    void addObserver(Observer* observer) 
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) 
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const std::string& event) 
    {  //Notificam observatorii
        for (Observer* observer : observers) 
        {
            observer->notify(event);
        }
    }
};

class HealthUI : public Observer 
{
public:
    void notify(const std::string& event) override 
    {
        std::cout << "UI Update: " << event << std::endl;  //UI-ul primeste notificare
    }
};


#endif
