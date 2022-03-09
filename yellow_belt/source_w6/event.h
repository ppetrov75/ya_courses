#ifndef YELLOW_BELT_EVENT_H
#define YELLOW_BELT_EVENT_H

#include <string>

class Event {
public:
    Event(const std::string &evt);

    const std::string event_;
};

std::string ParseEvent(std::istream &is);

#endif //YELLOW_BELT_EVENT_H
