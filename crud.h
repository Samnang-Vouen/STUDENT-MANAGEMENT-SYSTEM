#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "StylizedHeader.h"
using namespace std;

struct Student {
    int id;
    string name;
    string gender;
    string dob;
    string phoneNum;
    string major;
    int year;
    string email;
    bool isNew;
    Student *next;
};

class LinkedList {
    int size;
    int countMale, countFemale;
    Student *head, *tail;

    public:
        LinkedList () {
            size = 0;
            countMale = 0;
            countFemale = 0;
            head = tail = NULL;
        }

        ~LinkedList() {
            Student* current = head;
            while (current != NULL) {
                Student* temp = current;
                current = current->next;
                delete temp;
            }
        }

        void add(int id, string name, string gender, string dob, string phoneNum, string major, int year, string email) {
            Student *student = new Student{id, name, gender, dob, phoneNum, major, year, email, true, NULL};
            
            if(isEmpty()) {
                head = tail = student;
            } else {
                tail->next = student;
                tail = student;
            }
            size++;
        }

        void insertStudent() {
            string name, gender, dob, phoneNum, major, email;
            int id, year;

            while(true) {
                cout << "\n\t\t\tID (-1 to stop): ";
                cin >> id;
                cin.ignore();
                if(id == -1) {
                    break;
                }
                cout << "\n\t\t\tName: ";
                getline(cin, name);
                cout << "\n\t\t\tGender: ";
                cin >> gender;
                cout << "\n\t\t\tDate of birth (dd-mm-yyy): ";
                cin >> dob;
                cin.ignore();
                cout << "\n\t\t\tMajor: ";
                getline(cin, major);
                cout << "\n\t\t\tPhone number: ";
                cin >> phoneNum;
                cout << "\n\t\t\tYear: ";
                cin >> year;
                cout << "\n\t\t\tEmail: ";
                cin >> email;
                cout << "\t\t\t--------------------------------------------------------------\n\n";

                if (!isStudentInList(id)) {
                	add(id, name, gender, dob, phoneNum, major, year, email);
                }

            }
        }

        void create() {
            fstream file;
            string fileName;

            cout << "\n\t\t\tEnter the file name (file name + .csv): ";
            cin >> fileName;
            cin.ignore();
            cout << "\n\t\t\t"<< fileName << " successfully created" << endl;

            file.open(fileName, ios::out);
            if(!file.is_open()) {
                cout << "\n\t\t\tError: Unable to open file" << endl;
                return;
            }
            
            cout << "\n\t\t\tPlease insert students information" << endl;
            insertStudent(); 

            Student *current = head;

            while(current != NULL) {
               file << endl << current->id << (",")
                 << current->name << (",")
                 << current->gender << (",")
                 << current->dob << (",")
                 << current->phoneNum << (",")
                 << current->major << (",")
                 << current->year << (",")
                 << current->email << endl;

                current = current->next; 
            } 
            file.close();
            cout << "\n\t\t\tData saved to " << fileName << " successfully" << endl;
        }

        bool isStudentInList(int id) {
            Student* current = head;
            while (current != NULL) {
                if (current->id == id) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        void readDataFromFile(string fileName) {
            fstream file;
            file.open(fileName, ios::in);
            if(!file.is_open()) {
                cout << "\n\t\t\t\t\t\t\t\t\tError: Unable to open file" << endl;
                return;
            }
            string line;
            getline(file, line);
            while (getline(file, line)) {
                stringstream ss(line);
                string idStr, name, gender, dob, phoneNum, major, yearStr, email;

                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, gender, ',');
                getline(ss, dob, ',');
                getline(ss, phoneNum, ',');
                getline(ss, major, ',');
                getline(ss, yearStr, ',');
                getline(ss, email, ',');

                int id = stoi(idStr);
                int year = stoi(yearStr);

                if (!isStudentInList(id)) {
                	add(id, name, gender, dob, phoneNum, major, year, email);
                }
            }
            file.close();
        }

        void display() {
            string fileName;

            cout << "\n\t\t\tEnter file you want to display (file name + .csv): ";
            cin >> fileName;
            cin.ignore();
            readDataFromFile(fileName);
            if(isEmpty()) {
                cout << "\n\t\t\tThe student list is empty" << endl;
                return;
            }

            cout << left << setw(4) << "\nID" 
             << " | " << setw(17) << "Name"
             << " | " << setw(8) << "Gender" 
             << " | " << setw(13) << "Date of birth" 
             << " | " << setw(15) << "Phone number" 
             << " | " << setw(32) << "Major" 
             << " | " << setw(5) << "Year" 
             << " | " << setw(35) << "Email" << endl;
            cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            Student *current = head;
            while(current != NULL) {
                cout << left << setw(4) << current->id 
                << " | " << setw(17) << current->name 
                << " | " << setw(8) << current->gender
                << " | " << setw(13) << current->dob 
                << " | " << setw(15) << current->phoneNum
                << " | " << setw(32) << current->major
                << " | " << setw(5) << current->year
                << " | " << setw(35) << current->email << endl;

                current = current->next; 
            }
            cout << "\n\n\t\t\tTotal: " << size << " students" << endl;
            countMaleFemale();
            cout << "\n\t\t\tMale: " << countMale << " students" << endl;
            cout << "\n\t\t\tFemale: " << countFemale << " students" << endl;
        }

        void update() {
            fstream file;
            string fileName;

            cout << "\n\t\t\tEnter file you want to update (file name + .csv): ";
            cin >> fileName;
            cin.ignore();

            // Open the file in append mode to keep existing data
            file.open(fileName, ios::app);
            if (!file.is_open()) {
                cout << "\n\t\t\tError: Unable to open file" << endl;
                return;
            }

            cout << "\n\t\t\tInsert student information" << endl;
            insertStudent(); // Add new student(s) to the linked list

            Student* current = head;
            while (current != NULL) {
                if (current->isNew) { // Write only newly added records
                    file << current->id << (",")
                        << current->name << (",")
                        << current->gender << (",")
                        << current->dob << (",")
                        << current->phoneNum << (",")
                        << current->major << (",")
                        << current->year << (",")
                        << current->email << endl;
                    current->isNew = false; // Mark as written
                }
                current = current->next;
            }

            file.close();
            cout << "\n\t\t\t" << fileName << " updated successfully" << endl;
        }


        void removeById() {
            string fileName;

            cout << "\n\t\t\tEnter the file name (file name + .csv): ";
            cin >> fileName;
            cin.ignore();
            readDataFromFile(fileName); // Load data from the file into the linked list

            if (isEmpty()) {
                cout << "\n\t\t\tThe student list is empty. No record to remove." << endl;
                return;
            }

            int id;
            bool modified = false; // To track if any student was removed

            while (true) {
                cout << "\n\t\t\tEnter student ID to remove (-1 to stop): ";
                cin >> id;

                if (id == -1) { // Break the loop if -1 is entered
                    break;
                }

                Student* current = head;
                Student* prev = NULL;
                bool found = false;

                // Special case: Check if the head node matches the ID
                while (current != NULL && current->id == id) {
                    head = current->next; // Update head pointer
                    delete current;       // Free memory
                    size--;
                    current = head;       // Update current to the new head
                    found = true;
                    modified = true;
                }

                // Traverse the list to find the matching student (non-head nodes)
                while (current != NULL) {
                    if (current->id == id) {
                        prev->next = current->next; // Unlink the node
                        delete current;             // Free memory
                        size--;
                        found = true;
                        modified = true;
                        break; // Exit loop after deleting one matching node
                    }
                    prev = current;
                    current = current->next;
                }

                if (found) {
                    cout << "\n\t\t\tStudent with ID " << id << " has been removed." << endl;
                } else {
                    cout << "\n\t\t\tStudent with ID " << id << " not found." << endl;
                }
            }

            if (modified) {
                saveToFile(fileName); // Save the updated list back to the file only if changes were made
            } else {
                cout << "\n\t\t\tNo changes made to the file." << endl;
            }
        }

        void saveToFile(string fileName) {
            fstream file;
            file.open(fileName, ios::out);
            if(!file.is_open()) {
                cout << "\n\t\t\t\t\t\t\t\t\tError: Unable to open file" << endl;
                return;
            }
            Student *current = head;
            while(current != NULL) {
                file << current->id << (",")
                 << current->name << (",")
                 << current->gender << (",")
                 << current->dob << (",")
                 << current->phoneNum << (",")
                 << current->major << (",")
                 << current->year << (",")
                 << current->email << endl;

                current = current->next; 
            }
            file.close();
            cout <<"\n\t\t\t" << fileName << " updated successfully" << endl;
        }

        bool isEmpty() {
            if(head == NULL) {
                return true;
            } else {
                return false;
            }
        }

        void countMaleFemale() {
            countMale = 0; // Reset counters to avoid accumulation
            countFemale = 0;

            Student *current = head;
            while(current != NULL) {
                if(current->gender == "Male" || current->gender == "male") {
                    countMale++;
                }
                if(current->gender == "Female" || current->gender == "female") {
                    countFemale++;
                }
                current = current->next;
            }
        }

        // Search by ID
        Student* searchByID() {
            int id;
            string fileName;
            cout << "\n\t\t\t\t\tEnter file you want to display (file name + .csv): ";
            cin >> fileName;
            cin.ignore();
            readDataFromFile(fileName);
            cout << "\n\t\t\t\t\t\t\t\t\tSearch by ID: ";
            while (!(cin >> id)) {
                cin.clear();  // Clear input stream
                cout << "\n\t\t\t\t\t\t\t\t\tInvalid ID. Please enter a valid numeric ID: ";
            }
            Student* temp = head;
            while (temp) {
                if (temp->id == id) {
                    return temp;
                }
                temp = temp->next;
            }
            return nullptr;
        }

        // Search by name (substring match with multiple results)
        void searchByName() {
            string fileName;
            cout << "\n\t\t\t\t\tEnter file you want to display (file name + .csv): ";
            cin >> fileName;
            cin.ignore();
            readDataFromFile(fileName);
            string name;
            cout << "\n\t\t\t\t\t\t\t\t\tSearch by Name: ";
            cin.ignore();
            getline(cin, name);
            auto toLower = [](const string& str) {
                string lowerStr = str;
                std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
                return lowerStr;
            };

            string lowerSearch = toLower(name);  
            Student* temp = head;
            bool found = false;

            while (temp) {
                string lowerName = toLower(temp->name);  
                if (lowerName.find(lowerSearch) != string::npos) {  // Perform a case-insensitive substring search
                    found = true;
                    displayResult(temp);  // Display each match
                }
                temp = temp->next;
            }

            if (!found) {
                setConsoleColor(7, 1);
                cout << "\n\t\t======================================================== SEARCH RESULT ======================================================" << endl;
                cout << "\t\t|                                                      No matching record found                                              |" << endl;
                cout << "\t\t==============================================================================================================================" << endl;
                resetConsoleColor();
            }
        }

        // Display a single node's details
        void displayResult(Student* node) {
            static bool headerPrinted = false;  

            if (node) {
                // Print the header only once
                if (!headerPrinted) {
                    cout << "\n\t=============================================================================== SEARCH RESULT =================================================================" << endl;
                    cout << "\t| " << setw(5) << left << "ID"
                        << "| " << setw(15) << left << "Name"
                        << "| " << setw(10) << left << "Gender"
                        << "| " << setw(18) << left << "Date of Birthday"
                        << "| " << setw(18) << left << "Phone Number"
                        << "| " << setw(35) << left << "Major"
                        << "| " << setw(5) << left << "Year"
                        << "| " << setw(35) << left << "Email" << " |" << endl;
                    cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                    headerPrinted = true;  
                }
        
                cout << "\t| " << setw(5) << left << node->id
                    << "| " << setw(15) << left << node->name
                    << "| " << setw(10) << left << node->gender
                    << "| " << setw(18) << left << node->dob 
                    << "| " << setw(18) << left << node->phoneNum 
                    << "| " << setw(35) << left << node->major
                    << "| " << setw(5) << left << node->year
                    << "| " << setw(35) << left << node->email << " |" << endl;
                cout << "\t===============================================================================================================================================================" << endl;
            }
        }
};

// Display the search menu
void searchMenu(LinkedList& list) {
    char choice;
    int consoleWidth = getConsoleWidth();

    while (true) {
        system("cls");
        int consoleWidth = getConsoleWidth();
        string headerLines[] = {
            R"( _____ _____  ___  ______  _____  _   _      ___  ___ _____ _   _ _   _ )",
            R"(/  ___|  ___|/ _ \ | ___ \/  __ \| | | |     |  \/  ||  ___| \ | | | | |)",
            R"(\ `--.| |__ / /_\ \| |_/ /| /  \/| |_| |     | .  . || |__ |  \| | | | |)",
            R"( `--. \  __||  _  ||    / | |    |  _  |     | |\/| ||  __|| . ` | | | |)",
            R"(/\__/ / |___| | | || |\ \ | \__/\| | | |     | |  | || |___| |\  | |_| |)",
            R"(\____/\____/\_| |_/\_| \_| \____/\_| |_/     \_|  |_/\____/\_| \_/\___/ )",                                                              
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

        gotoxy((consoleWidth - 30) / 2, menuStartY);
        cout << "1. ID" << endl;
        gotoxy((consoleWidth) / 2, menuStartY);
        cout << "2. Name" << endl;
        gotoxy((consoleWidth) / 2, menuStartY + 2);
        cout << "0. Exit" << endl;

        cout << "\n\t\t\t\tPlease enter your choice: ";
        cin>>choice;
        system("cls");

        switch (choice) {
            case '1': {
                Student* result = list.searchByID();
                system("cls");
                gotoxy((consoleWidth - 30) / 2, menuStartY - 10);
                list.displayResult(result);
                break;
            }
            case '2': {
                system("cls");
                gotoxy((consoleWidth - 30) / 2, menuStartY - 10);
                list.searchByName();
                break;
            }
            case '0': {
                return;
            }
            default:
                gotoxy((consoleWidth - 50) / 2, menuStartY + 8);
                cout << "Invalid choice! Please press a valid option (0-3)." << endl;
        }
        cout << "\n\t\t\t\t\t\t\t\t\tPress Enter to continue...";
        _getch();  // Wait for any key to continue
    }
}
