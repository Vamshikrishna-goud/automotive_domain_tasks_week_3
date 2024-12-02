/*
Objective: Implement a basic menu navigation system similar to what is found in automotive HMI clusters (e.g., settings menu, media options).
Requirements:
Create a hierarchical menu structure using classes and data structures.
Example:
Main Menu
Settings
Display Settings
Audio Settings
Media
Radio
Bluetooth Audio
Use a tree structure (std::vector or custom tree data structure) to represent the hierarchy.
Implement the following functionalities:
Navigate through menu levels (up/down/enter/back).
Display the current menu options on the console.
Add keyboard-based interaction (e.g., 1 to navigate down, 2 to navigate up, 3 to enter).
Deliverables:
A C++ program that uses OOP to create the menu structure.
Console output demonstrating navigation and interactions.
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;


class MainMenu {
public:
    string name;
    vector<shared_ptr<MainMenu>> subs; 
    shared_ptr<MainMenu> parent;
    
    MainMenu(string name) {
        this->name=name;
    }


    void addSettings(shared_ptr<MainMenu> child) {
        subs.push_back(child);
    }

    void display(int level = 0) {

        for (int i = 0; i < level; ++i)
        cout << "  ";
        cout << name << endl;
        

        for (auto& child : subs) {
            child->display(level + 1);
        }
    }

    void userInputs(shared_ptr<MainMenu> mainMenu){

        vector<shared_ptr<MainMenu>>::iterator cur;
        cout<<"you are in : "<<mainMenu->name<<endl;
        cur=mainMenu->subs.begin();
        cout<<"-> "<<(*cur)->name<<endl;
        cout<<"   "<<(*(cur+1))->name<<endl;
        first:
        cout<<"choose the options "<<endl;
        cout<<"1.navigate down"<<endl;
        cout<<"2.navigate up"<<endl;
        cout<<"3.enter"<<endl;
        cout<<"4.back"<<endl;
        int n;
        cin>>n;
        switch (n)
        {
            case 1:{
                if(cur==mainMenu->subs.end()-1){
                    cout<<"   "<<(*(cur-1))->name<<endl;
                    cout<<"-> "<<(*cur)->name<<endl;
                }else{
                    cur+=1;
                    cout<<"   "<<(*(cur-1))->name<<endl;
                    cout<<"-> "<<(*cur)->name<<endl;
                }
                goto first;
            }
            case 2:{
                if(cur==mainMenu->subs.begin()){
                    cout<<"-> "<<(*cur)->name<<endl;
                    cout<<"   "<<(*(cur+1))->name<<endl;
                }else{
                    cur-=1;
                    cout<<"-> "<<(*cur)->name<<endl;
                    cout<<"   "<<(*(cur+1))->name<<endl;
                }
                goto first;
            }

        case 3:
            {
                    for(auto i:mainMenu->subs){
                        if(i->name==(*cur)->name){
                            parent=mainMenu;
                            userInputs(i);
                        }else{
                            cout<<" there are no childs...!"<<endl;
                        }
                    }
            }
            case 4:
            {
                userInputs(parent);
            }
        
        default :{
            cout<<"enter the proper option...!"<<endl;
            goto first;
        }
        }




    }
};


class Settings : public MainMenu {
public:
    Settings(string name) : MainMenu(name) {}
};


class DisplaySettings : public Settings {
public:
    DisplaySettings(string name) : Settings(name) {}
};


class AudioSettings : public Settings {
public:
    AudioSettings(string name) : Settings(name) {}
};


class Media : public MainMenu {
public:
    Media(string name) : MainMenu(name) {}
};


class Radio : public Media {
public:
    Radio(string name) : Media(name) {}
};


class BluetoothAudio : public Media {
public:
    BluetoothAudio(string name) : Media(name) {}
};

int main() {
   
    shared_ptr<MainMenu> mainMenu = make_shared<MainMenu>("MainMenu");

    shared_ptr<Settings> settings = make_shared<Settings>("Settings");
    shared_ptr<Media> media = make_shared<Media>("Media");

    shared_ptr<DisplaySettings> display = make_shared<DisplaySettings>("Display Settings");
    shared_ptr<AudioSettings> audio = make_shared<AudioSettings>("Audio Settings");

    shared_ptr<Radio> radio = make_shared<Radio>("Radio");
    shared_ptr<BluetoothAudio> bluetooth = make_shared<BluetoothAudio>("Bluetooth Audio");

    
    mainMenu->addSettings(settings);
    mainMenu->addSettings(media);

    settings->addSettings(display);
    settings->addSettings(audio);

    media->addSettings(radio);
    media->addSettings(bluetooth);

    
    cout << "Menu Hierarchy:" << endl;
    mainMenu->display();
    mainMenu->userInputs(mainMenu);

}
