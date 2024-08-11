#pragma once

#include <vector>
#include <map>

using EventType = int32_t;

class EventData
{
public:
    EventData(EventType eventType): mEventType(eventType){};
    EventData(EventType eventType, void* data): mEventType(eventType), mData(data){};
    EventType mEventType = 0;
    void* mData = nullptr;
};

// Define a broadcaster class
class EventProcessor
{
private:
    std::vector<EventProcessor*> listeners;

public:

    // Event handler for receiving events
    virtual std::vector<EventData> onEvent(const EventData& event [[maybe_unused]]){return {};};

    // Register a listener
    void addListener(EventProcessor* listener)
    {
        listeners.push_back(listener);
    }

    // Unregister a listener
    void removeListener(EventProcessor* listener)
    {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }

    // Broadcast an event to all listeners
    void broadcast(const EventData& event)
    {
        std::map<EventProcessor*,std::vector<EventData>> returnedEvents;

        for (EventProcessor* listener : listeners)
        {
            returnedEvents.insert({listener, listener->onEvent(event)});
        }

        for (const auto& entry : returnedEvents)
        {
            EventProcessor* listener = entry.first;
            const std::vector<EventData>& eventDataList = entry.second;

            for (const EventData& eventData : eventDataList)
            {
                listener->broadcast(eventData);
            }
        }
    }
};