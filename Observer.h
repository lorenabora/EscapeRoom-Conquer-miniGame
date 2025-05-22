#pragma once

#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const std::string& event) = 0;  // functie de notificare virtuala
};

#endif
