#include <windows.h>
#include "colors.h"

void set_color(color choosed_color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (choosed_color) {
        case blue:
            // Set text color to blue
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            break;
        case red:
            // Set text color to red
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            break;
        case green:
            // Set text color to green
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;
        case reset:
            // Reset text color
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
    }
}