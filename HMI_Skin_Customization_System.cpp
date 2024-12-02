/*

Task 4: HMI Skin Customization System
Objective: Implement a system to manage different themes or skins for an HMI display.
Requirements:
Create a Theme class:
Attributes: backgroundColor, fontColor, fontSize, and iconStyle.
Implement methods to apply and display the theme.
Store multiple themes using std::map:
Example themes: Classic, Sport, and Eco.
Create a simple user interface to switch between themes:
Use console input to select a theme.
Display a preview of the selected theme on the console (e.g., "Sport Theme: Red Background, White Font").
Deliverables:
A C++ program that demonstrates theme switching.
Output displaying applied themes.

*/
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Theme
{
    static Theme *instance;
    string theme;
    string backgroundColor;
    string fontColor;
    int fontSize;
    string iconStyle;
    Theme()
    {
        this->theme = "Classic";
        this->backgroundColor = "white";
        this->fontColor = "black";
        this->iconStyle = "flat";
        this->fontSize = 12;
    }

public:
    static Theme *getInstance()
    {
        if (instance == nullptr)
            instance = new Theme();
        return instance;
    }

    std::string getTheme() const
    {
        return theme;
    }
    void setTheme(const std::string &newTheme)
    {
        theme = newTheme;
    }

    std::string getBackgroundColor() const
    {
        return backgroundColor;
    }
    void setBackgroundColor(const std::string &newBackgroundColor)
    {
        backgroundColor = newBackgroundColor;
    }

    std::string getFontColor() const
    {
        return fontColor;
    }
    void setFontColor(const std::string &newFontColor)
    {
        fontColor = newFontColor;
    }

    int getFontSize() const
    {
        return fontSize;
    }
    void setFontSize(int newFontSize)
    {
        fontSize = newFontSize;
    }

    std::string getIconStyle() const
    {
        return iconStyle;
    }
    void setIconStyle(const std::string &newIconStyle)
    {
        iconStyle = newIconStyle;
    }
};
Theme *Theme::instance = nullptr;

class Settings
{
    map<int, string> themes = {{1, "Classic"}, {2, "Sport"}, {3, "Eco"}};
    Theme *themeInstance;

public:
    Settings()
    {
        themeInstance = Theme::getInstance();
    }
    void changeTheme()
    {
    first:
        cout << "choose the below mentions options to change theme " << endl;
        for (auto i : themes)
        {
            cout << "id : " << i.first << "-> ";
            cout << i.second << " theme " << endl;
        }
        cout << "id : " << 0 << "-> " << "exit" << endl;

        int n;
        cout << "enter the id to change the theme " << endl;
        cin >> n;
        if (n == 0)
        {
            exit(1);
        }
        else
        {
            auto it = themes.find(n);
            if (it != themes.end())
            {
                themeInstance->setTheme(it->second);
                cout << "theme changed to : " << it->second << endl;
                if (it->second == "Sport")
                {
                    themeInstance->setBackgroundColor("Black");
                    themeInstance->setFontColor("White");
                    themeInstance->setIconStyle("outline");
                    themeInstance->setFontSize(20);
                }
                else if (it->second == "Eco")
                {
                    themeInstance->setBackgroundColor("Blue");
                    themeInstance->setFontColor("Red");
                    themeInstance->setIconStyle("3d");
                    themeInstance->setFontSize(18);
                }
                else
                {
                    themeInstance->setBackgroundColor("White");
                    themeInstance->setFontColor("Black");
                    themeInstance->setIconStyle("Flat");
                    themeInstance->setFontSize(12);
                }
                displayTheme();
            }
            else
            {
                cout << "theme not fount in the specified themes choose proper option...!" << endl;
                goto first;
            }
        }
    }

    void displayTheme()
    {
        cout << themeInstance->getTheme() << " Theme: " << themeInstance->getBackgroundColor() << " Background: " << themeInstance->getFontColor() << " Font: ";
        cout << themeInstance->getIconStyle() << " Iconstyle: " << themeInstance->getFontSize() << " Fontsize" << endl;
    }
};
int main()
{
    Settings s;
    s.displayTheme();
    s.changeTheme();
}