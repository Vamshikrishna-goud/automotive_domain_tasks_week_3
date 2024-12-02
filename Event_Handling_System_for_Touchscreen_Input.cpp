/*
Task 3: Event Handling System for Touchscreen Input
Objective: Simulate an event-driven system for processing touchscreen inputs on an HMI.
Requirements:
Create an Event class to represent user interactions:
Attributes: eventType (e.g., Tap, Swipe), x and y coordinates, and timestamp.
Implement an event queue using std::queue:
Store multiple events.
Process events one by one.
Handle specific events:
Tap: Display a message showing the tapped position.
Swipe: Calculate the swipe direction (up/down/left/right) and display it.
Simulate event generation:
Populate the queue with random events.
Deliverables:
A program simulating event processing.
Example output demonstrating event handling.
*/

#include <iostream>
#include <queue>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>
using namespace std;

class Event
{
public:
    string eventType;
    int x;
    int y;
    time_t timeStamp;

    Event(const string &type, int xCoord, int yCoord)
    {
        eventType = type;
        x = xCoord;
        y = yCoord;
        timeStamp = time(0);
    }
    string getFormattedTime() const{
        return ctime(&timeStamp);
    }
};

class EventProcessing
{
public:
    queue<Event> events;

    void addEvents(const Event& event){
        events.push(event);
    }

    void display(){
        while(!events.empty()){
            auto e = events.front();
            cout << "Event: " << e.eventType << ", "
                 << "Coordinates: (" << e.x << ", " << e.y << "), "
                 << "Timestamp: " << e.getFormattedTime(); // Output formatted time

            if (e.eventType == "tap") {
                cout << "Tap detected at position (" << e.x << ", " << e.y << ")." << endl;
            } else if (e.eventType == "swipe") {
                string direction;
                if (e.x > e.y) {
                    direction = "right";
                } else if (e.x < e.y) {
                    direction = "left";
                } else {
                    direction = "unknown";
                }
                cout << "Swipe detected in direction: " << direction << "." << endl;
            }

            this_thread::sleep_for(chrono::seconds(2));
            events.pop();
        }
    }
};

int main(){
    Event event1("tap", 300, 400);
    Event event2("swipe", 782, 89);
    Event event3("swipe", 789, 1234);
    Event event4("tap", 980, 345);

    EventProcessing process;
    process.addEvents(event1);
    process.addEvents(event2);
    process.addEvents(event3);
    process.addEvents(event4);

    thread t(&EventProcessing::display, &process);
    t.join();

    return 0;
}