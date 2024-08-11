#include "gtest/gtest.h"
#include "Events.hpp"  // Adjust the path to where your header is located

class TestEventProcessor : public EventProcessor {
public:
    std::vector<EventData> onEvent(const EventData& event) override {
        receivedEvents.push_back(event);
        return {};  // No additional events to broadcast
    }

    std::vector<EventData> receivedEvents;
};

// Test to check if a listener can be added and called
TEST(EventProcessorTests, AddListenerAndBroadcastEvent) {
    TestEventProcessor processor;
    TestEventProcessor listener;

    processor.addListener(&listener);

    EventData event(1);
    processor.broadcast(event);

    ASSERT_EQ(listener.receivedEvents.size(), 1);
    EXPECT_EQ(listener.receivedEvents[0].mEventType, 1);
}

// Test to check if a listener can be removed
TEST(EventProcessorTests, RemoveListener) {
    TestEventProcessor processor;
    TestEventProcessor listener;

    processor.addListener(&listener);
    processor.removeListener(&listener);

    EventData event(1);
    processor.broadcast(event);

    ASSERT_EQ(listener.receivedEvents.size(), 0);  // Listener should not receive the event
}

// Test to check if multiple listeners can be added and receive events
TEST(EventProcessorTests, BroadcastToMultipleListeners) {
    TestEventProcessor processor;
    TestEventProcessor listener1;
    TestEventProcessor listener2;

    processor.addListener(&listener1);
    processor.addListener(&listener2);

    EventData event(1);
    processor.broadcast(event);

    ASSERT_EQ(listener1.receivedEvents.size(), 1);
    EXPECT_EQ(listener1.receivedEvents[0].mEventType, 1);

    ASSERT_EQ(listener2.receivedEvents.size(), 1);
    EXPECT_EQ(listener2.receivedEvents[0].mEventType, 1);
}

// Test to check if the same listener can be added multiple times (should be avoided)
TEST(EventProcessorTests, AddSameListenerMultipleTimes) {
    TestEventProcessor processor;
    TestEventProcessor listener;

    processor.addListener(&listener);
    processor.addListener(&listener);  // Adding the same listener again

    EventData event(1);
    processor.broadcast(event);

    ASSERT_EQ(listener.receivedEvents.size(), 2);  // Listener receives the event twice
}

// Test to check recursive broadcasting of events
TEST(EventProcessorTests, RecursiveBroadcasting) {
    class RecursiveEventProcessor : public EventProcessor {
    public:
        std::vector<EventData> onEvent(const EventData& event) override {
            receivedEvents.push_back(event);
            if (event.mEventType == 1) {
                return {EventData(2)};  // Trigger another event
            }
            return {};
        }

        std::vector<EventData> receivedEvents;
    };

    RecursiveEventProcessor processor;
    processor.addListener(&processor);  // Processor listens to itself

    EventData event(1);
    processor.broadcast(event);

    ASSERT_EQ(processor.receivedEvents.size(), 2);
    EXPECT_EQ(processor.receivedEvents[0].mEventType, 1);
    EXPECT_EQ(processor.receivedEvents[1].mEventType, 2);
}

// Test to check if EventData carries data correctly
TEST(EventProcessorTests, EventDataCarriesDataCorrectly) {
    TestEventProcessor processor;
    TestEventProcessor listener;

    processor.addListener(&listener);

    int testData = 42;
    EventData event(1, &testData);
    processor.broadcast(event);

    ASSERT_EQ(listener.receivedEvents.size(), 1);
    EXPECT_EQ(listener.receivedEvents[0].mEventType, 1);
    EXPECT_EQ(*static_cast<int*>(listener.receivedEvents[0].mData), 42);
}

// Test to check if no listeners exist
TEST(EventProcessorTests, NoListeners) {
    TestEventProcessor processor;

    EventData event(1);
    processor.broadcast(event);

    // Nothing to assert, just making sure no exceptions or errors occur
}

// Test to check if listeners are handled correctly after being removed
TEST(EventProcessorTests, AddAndRemoveListenersMultipleTimes) {
    TestEventProcessor processor;
    TestEventProcessor listener1;
    TestEventProcessor listener2;

    processor.addListener(&listener1);
    processor.addListener(&listener2);
    processor.removeListener(&listener1);
    processor.removeListener(&listener2);

    EventData event(1);
    processor.broadcast(event);

    ASSERT_EQ(listener1.receivedEvents.size(), 0);
    ASSERT_EQ(listener2.receivedEvents.size(), 0);
}

// Test to check if broadcasting an event with no listeners doesn't cause issues
TEST(EventProcessorTests, BroadcastEventWithNoListeners) {
    TestEventProcessor processor;

    EventData event(1);
    EXPECT_NO_THROW(processor.broadcast(event));  // Should not throw any exceptions
}

