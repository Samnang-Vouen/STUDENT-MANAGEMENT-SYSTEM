#ifndef LOGIN_H
#define LOGIN_H

#include "StylizedHeader.h"
#include "LoadingAnimation.h"
#include <iostream>
#include <windows.h> // For gotoxy and Sleep
#include <string>
#include <fstream>
#include <conio.h> // For _getch()

using namespace std;

// Function to set the text and background color
void setConsoleColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Get the console handle
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);  // Combine background and text color
}

// Function to reset color back to normal
void resetConsoleColor() {
    setConsoleColor(7, 0);  // Reset to default (white text on black background)
}

// Function to XOR encrypt the password
string xorEncryptDecrypt(const string& data, char key) {
    string result = data;
    for (size_t i = 0; i < data.length(); ++i) {
        result[i] = data[i] ^ key;  // XOR each character with the key
    }
    return result;
}

// Function to get user credentials (username and password)
inline void getUserCredentials() {
    int consoleWidth = getConsoleWidth();
    string username, password;
    string setPassword = "admin"; 

    setConsoleColor(7, 1);
    // Input prompts for Username and Password
    string usernamePrompt = "User Name: ";
    string passwordPrompt = "Password: ";

    int inputX = consoleWidth / 4; // Align inputs to the left
    int usernameY = 10;
    int passwordY = usernameY + 2;

    gotoxy(inputX, usernameY);
    cout << usernamePrompt;
    gotoxy(inputX + usernamePrompt.length(), usernameY);
    getline(cin, username);

    gotoxy(inputX, passwordY);
    cout << passwordPrompt;
    gotoxy(inputX + passwordPrompt.length(), passwordY);

    char ch;
    while ((ch = _getch()) != 13) { // Enter key is ASCII 13
        if (ch == 8 && !password.empty()) { // Handle backspace
            password.pop_back();
            cout << "\b \b"; // Remove last character from console
        } else if (ch != 8) {
            password += ch;
            cout << '*'; // Display '*' for each character
        }
    }
    cout << endl;

    // Display the entered Username and Password immediately below input fields
    int displayY = passwordY + 3;
    gotoxy(inputX, displayY);
    cout << "Username: " << username;

    gotoxy(inputX, displayY + 1);
    cout << "Password: " << string(password.length(), '*');

    // Check if entered password matches the set password
    if (password == setPassword) {
        gotoxy(inputX, displayY + 2);
        //cout << "Login successful!" << endl;
        
        // XOR encryption key (you can change this key)
        char encryptionKey = 'K'; // Simple key for XOR encryption

        // Encrypt the password using XOR encryption
        string encryptedPassword = xorEncryptDecrypt(password, encryptionKey);

        // Save to a file for later use
        ofstream file("credentials.bin", ios::binary); // Open file in binary mode
        if (file.is_open()) {
            file << "Username: " << username << endl;
            file << "Password: " << encryptedPassword << endl;
            file.close();
            resetConsoleColor();
            system("cls");
        } else {
            cerr << "\n\t\t\t\t\t\t\t\t\tError: Unable to open file to save credentials." << endl;
        }
    } else {
        gotoxy(inputX, displayY + 2);
        cout << "\n\t\t\t\t\t\t\t\t\tInvalid password!" << endl;
    }
}

#endif // LOGIN_H