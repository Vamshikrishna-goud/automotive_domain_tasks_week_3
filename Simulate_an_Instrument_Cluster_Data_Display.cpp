/*
Objective: Create a simplified data display system to simulate speed, fuel level, and engine temperature.
Requirements:
Implement a class-based design:
Create a VehicleData class to store parameters like speed, fuel level, and engine temperature.
Create a Display class to show these parameters on the console.
Simulate real-time updates:
Use a random number generator to update speed, fuel level, and temperature every second.
Display the updated data in a formatted manner (e.g., speed: 80 km/h, fuel: 50%, temperature: 90°C).
Add constraints:
Display warnings when parameters exceed thresholds (e.g., temperature > 100°C or fuel < 10%).
Deliverables:
A C++ program using multithreading (std::thread) to update and display data.
Output showcasing real-time updates and warnings.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>
using namespace std;
mutex m;
condition_variable cv;

class VehicleData
{
    static VehicleData *instance;
    VehicleData()
    {
        this->speed = 0;
        this->fuel_level = 100;
        this->temperature = 20;
    }

public:
    int speed, fuel_level, temperature;
    static VehicleData *getInstance()
    {
        if (instance == nullptr)
            instance = new VehicleData();
        return instance;
    }

    void setData()
    {
        while (true)
        {
            unique_lock<mutex> ul(m);
            this->speed = rand() % 201;
            this->fuel_level = rand() % 101;
            this->temperature = rand() % 151;
            this_thread::sleep_for(chrono::seconds(2));
            cv.notify_one();
            cv.wait(ul);
        }
    }
};
VehicleData *VehicleData::instance = nullptr;

class Display
{
public:
    void display(VehicleData *vd)
    {
        while (true)
        {
            unique_lock<mutex> ul(m);
            cout << "speed : " << vd->speed << " km/h" << endl;
            cout << "fuel : " << vd->fuel_level << " %" << endl;
            cout << "temperature : " << vd->temperature << " C" << endl;

            if (vd->temperature > 100)
                cout << "temperature is high....!" << endl;
            else if (vd->fuel_level < 10)
                cout << "fuel is insufficient...!" << endl;

            cout << "==================================" << endl;
            if(vd->fuel_level==0){
                exit(1);
            }

            this_thread::sleep_for(chrono::seconds(2));
            cv.notify_one();
            cv.wait(ul);
        }
    }
};

int main()
{
    srand(time(0));     //optional 
    VehicleData *vd = VehicleData::getInstance();
    Display d;
    thread t1(&VehicleData::setData, vd);
    thread t2(&Display::display, &d, vd);

    t1.join();
    t2.join();
}
