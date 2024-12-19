#ifndef STYLIZED_HEADER_H
#define STYLIZED_HEADER_H

#include <iostream>
#include <windows.h> // For gotoxy and Sleep
#include <string>
using namespace std;

// Function to move the cursor to a specific position
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to calculate the width of the console
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Function to set text color using Windows console attributes
void setConsoleColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to reset the color back to default
void resetColor() {
    setConsoleColor(7); // Default color
}

// Function to print a stylized header centered on the console
void printStylizedHeader() {
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
}

void printLogin() {
    int consoleWidth = getConsoleWidth();
    string headerLines[] = {
        R"( _     _____ _____ _____ _   _ )",
        R"(| |   |  _  |  __ \_   _| \ | |)",
        R"(| |   | | | | |  \/ | | |  \| |)",
        R"(| |   | | | | | __  | | | . ` |)",
        R"(| |___\ \_/ / |_\ \_| |_| |\  |)",
        R"(\_____/\___/ \____/\___/\_| \_/)",
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
}

#endif // STYLIZED_HEADER_H
