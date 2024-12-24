#include <iostream>
#include "StylizedHeader.h"
using namespace std;

void menu() {
    system("cls");
    int consoleWidth = getConsoleWidth();
    string headerLines[] = {
        R"( __  __  _ _  _   _  _     _   _   _   _  _   _   _  _  __  ___  _   _  ___  _  _  ___   ____ __ __  ___  ___  _   _ )",
        R"(/ _|/ _|| U |/ \ / \| |   | \_/ | / \ | \| | / \ | \| |/ _|| __|| \_/ || __|| \| ||_ _| / _\ V // _||_ _|| __|| \_/ |)",
        R"(\_ ( (_ |   ( o | o ) |_  | \_/ || o || \\ || o || \\ ( |_n| _| | \_/ || _| | \\ | | |  \_ \\ / \_ \ | | | _| | \_/ |)",
        R"(|__/\__||_n_|\_/ \_/|___| |_| |_||_n_||_|\_||_n_||_|\_|\__/|___||_| |_||___||_|\_| |_|  |__/|_| |__/ |_| |___||_| |_|)",
    };

    int headerHeight = sizeof(headerLines) / sizeof(headerLines[0]);
    int startY = 2;

    // Choose a color scheme for the header
    WORD colors[] = {9, 11, 14, 13}; // Blue, Cyan, Bright White, Magenta

    for (int i = 0; i < headerHeight; ++i) {
        string scaledLine = headerLines[i];
        int startX = (consoleWidth - scaledLine.length()) / 2; // Center horizontally

        gotoxy(startX, startY + i);
        setConsoleColor(colors[i % 4]); // Cycle through the colors
        cout << scaledLine;
    }
    
    resetColor();
    int menuStartY = startY + headerHeight + 3;
    gotoxy((consoleWidth - 70) / 2, menuStartY);
    cout << "1. Create Student List";
    gotoxy((consoleWidth) / 2, menuStartY);
    cout << "2. Display All Student\n";
    gotoxy((consoleWidth - 70) / 2, menuStartY + 2);
    cout << "3. Update Student List\n";
    gotoxy((consoleWidth) / 2, menuStartY + 2);
    cout << "4. Delete Student By ID\n";
    gotoxy((consoleWidth - 70) / 2, menuStartY + 4);
    cout << "5. Search\n";
    gotoxy((consoleWidth) / 2, menuStartY + 4);
    cout << "0. Exit\n";
}
