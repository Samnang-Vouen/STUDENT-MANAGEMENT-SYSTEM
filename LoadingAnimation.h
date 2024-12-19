#ifndef LOADING_ANIMATION_H
#define LOADING_ANIMATION_H

#include <iostream>
#include <windows.h>
#include "StylizedHeader.h"
using namespace std;

// Function to clear the console
void clearConsole() {
    system("cls"); // Clear the screen
}

// Function to show the loading bar at the center
void showLoadingProgress(int percentage, int filledLength, int barWidth) {
    int consoleWidth = getConsoleWidth();
    int totalWidth = barWidth + 5; // Width including spaces, `[` `]`

    int startX = (consoleWidth - totalWidth) / 2; // Center the bar horizontally
    int centerY = 15; // Display it at Y=10 to position it nicely below the header

    // Print "Loading..." at the calculated center
    gotoxy(startX, centerY);
    setConsoleColor(14);  // Set text to yellow
    cout << "Loading...                                                          " << percentage << "%";
    // Print the bar itself
    gotoxy(startX, centerY + 1);
    cout << "[";
    for (int i = 0; i < filledLength; ++i) {
        cout << "|";
    }
    for (int i = filledLength; i < barWidth; ++i) {
        cout << " ";
    }
    cout << "]";
}

// Function to simulate loading
void simulateLoading() {
    const int barWidth = 70; // Width of the progress bar
    for (int i = 0; i <= 100; i += 2) {
        int filledLength = (i * barWidth) / 100;
        showLoadingProgress(i, filledLength, barWidth);
        Sleep(30); // Pause to simulate animation
    }
    Sleep(500); // Brief pause after loading
    clearConsole(); // Clear the console after loading completes
    setConsoleColor(7); // Default color
}

#endif // LOADING_ANIMATION_H
