#ifndef SOME_HEADER_H6
#define SOME_HEADER_H6

#include "Arduino.h"
#include <functional>
#include <vector>

class Event
{
private:
    using Subscribtion = std::function<void()>;
    std::vector<Subscribtion> subscribtionsList;

   

    // void Unsubscribe(Subscribtion subscribtion){
    //     subscribtionsList.(subscribtion);
    // }

public:
    void Subscribe(Subscribtion subscribtion)
    {
        subscribtionsList.push_back(subscribtion);
    }

    void RaiseEvent()
    {
        for (const auto &subscriber : subscribtionsList)
            subscriber();
    }
};
#endif