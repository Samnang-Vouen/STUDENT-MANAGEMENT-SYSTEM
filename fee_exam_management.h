#ifndef FEE_EXAM_MANAGEMENT_H
#define FEE_EXAM_MANAGEMENT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "StylizedHeader.h"

using namespace std;


struct FeeRecord {
    int studentID;               
    string studentName;          
    string studentGender;        
    string phoneNumber;          
    string paymentStatus;        
    double amountPaid;           
    int year;                    
    FeeRecord* next;             
};


struct ExamResult {
    int studentID;               
    string studentName;          
    string studentGender;        
    int year;                    
    string subject;              
    string grade;                
    ExamResult* next;            
};

// Function declarations for fee management
void feeManagementMenu(FeeRecord*& feeHead);
void recordFeePayment(FeeRecord*& feeHead);
void checkFeeStatus(FeeRecord*& feeHead);
void displayAllPayments(FeeRecord* feeHead);
void saveFeeRecordsToCSV(FeeRecord* feeHead);
void loadFeeRecords(FeeRecord*& feeHead);


void examResultsMenu(ExamResult*& examHead);
void addExamResult(ExamResult*& examHead);
void viewAllResults(ExamResult* examHead);
void checkStudentPerformanceByID(ExamResult* examHead);
void checkStudentPerformanceByName(ExamResult* examHead);
void findHighestAndLowestGrade(ExamResult* examHead);
void saveExamResultsToCSV(ExamResult* examHead);
void loadExamResults(ExamResult*& examHead);


// Function to display the fee management menu
void feeManagementMenu(FeeRecord*& feeHead) {
    int choice;
    do {
        system("cls");
        int consoleWidth = getConsoleWidth();
        string headerLines[] = {
            R"( ______ _____ _____      ___  ___  ___   _   _ _   _ )",
            R"(|  ___|  ___|  ___|     |  \/  | / _ \ | \ | | | | |)",
            R"(| |_  | |__ | |__       | .  . |/ /_\ \|  \| | | | |)",
            R"(|  _| |  __||  __|      | |\/| ||  _  || . ` | | | |)",
            R"(| |   | |___| |___      | |  | || | | || |\  | |_| |)",
            R"(\_|   \____/\____/      \_|  |_/\_| |_/\_| \_/\___/ )",                                                                                     
                                                          
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
        loadFeeRecords(feeHead);
        gotoxy((consoleWidth - 50) / 2, menuStartY);
        cout << "1. Record Fee Payment\n";
        gotoxy((consoleWidth) / 2, menuStartY);
        cout << "2. Check Fee Status\n";
        gotoxy((consoleWidth - 50) / 2, menuStartY + 2);
        cout << "3. Display All Payments\n";
        gotoxy((consoleWidth) / 2, menuStartY + 2);
        cout << "0. Exit\n";

        cout << "\n\t\t\t\tEnter your choice: ";
        cin >> choice;
        system("cls");
        switch (choice) {
            case 1:  
                recordFeePayment(feeHead); 
                break;
            case 2: 
                checkFeeStatus(feeHead); 
                break;
            case 3: 
                displayAllPayments(feeHead); 
                break;
            case 0: 
                return;
            default: cout << "\n\t\t\t\t\t\t\t\t\tInvalid choice. Please try again.\n"; break;
        }
        cout << "\n\t\t\t\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore();  
        cin.get();     
        system("cls");
    } while (choice != 0);
}

// Function to record a fee payment
void recordFeePayment(FeeRecord*& feeHead) {
    FeeRecord* newRecord = new FeeRecord;
    cout << "\n\t\t\t\tEnter Student ID: ";
    cin >> newRecord->studentID;
    cout << "\n\t\t\t\tEnter Student Name: ";
    cin.ignore();
    getline(cin,  newRecord->studentName);
    cout << "\n\t\t\t\tEnter Gender: ";
    cin >> newRecord->studentGender;
    cout << "\n\t\t\t\tEnter Phone Number: ";
    cin >> newRecord->phoneNumber;
    cout << "\n\t\t\t\tEnter Payment Status: ";
    cin.ignore();
    getline(cin,newRecord->paymentStatus);
    cout << "\n\t\t\t\tEnter Amount Paid:$ ";
    cin >> newRecord->amountPaid;
    cout << "\n\t\t\t\tEnter Payment Year: ";
    cin >> newRecord->year;

    newRecord->next = feeHead;
    feeHead = newRecord;

    saveFeeRecordsToCSV(feeHead);
    cout << "\n\t\t\t\t\t\t\t\t\tFee payment recorded successfully.\n";
}

// Function to check fee status
void checkFeeStatus(FeeRecord*& feeHead) {
    int studentID;
    bool recordFound = false;

    cout << "\n\t\t\t\tEnter Student ID to check payment status: ";
    cin >> studentID;

    FeeRecord* temp = feeHead;
    while (temp) {
        if (temp->studentID == studentID) {
            cout << "\n\t\t\t\t\t\t\t\t\tStudent " << temp->studentName << " (" << temp->studentGender << ") has " << temp->paymentStatus << " the school fees.\n";
            recordFound = true;
            break;
        }
        temp = temp->next;
    }

    if (!recordFound) {
        cout << "\n\t\t\t\t\t\t\t\t\tNo record found for Student ID " << studentID << ".\n";
    }
}

// Function to display all fee payments
void displayAllPayments(FeeRecord* feeHead) {
    if (!feeHead) {
        cout << "No fee records to display.\n";
        return;
    }

    cout << "\t\t\t\t\tStudent ID" << setw(20) << "Student Name" << setw(20) << "Gender" << setw(20) << "Phone Number" << setw(20) << "Payment Status" << endl;
    cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    FeeRecord* temp = feeHead;
    while (temp) {
        cout <<"\t\t\t\t\t"<< setw(10) << temp->studentID
            << setw(20) << temp->studentName 
            << setw(20) << temp->studentGender 
            << setw(20) << temp->phoneNumber
            << setw(20) << temp-> paymentStatus << endl;
        temp = temp->next;
    }
}

// Function to save fee records to a CSV file
void saveFeeRecordsToCSV(FeeRecord* feeHead) {
    ofstream outFile("fee_records.csv");
    FeeRecord* temp = feeHead;
    while (temp) {
        outFile << temp->studentID << "," << temp->studentName << "," << temp->studentGender << ","
                << temp->phoneNumber << "," << temp->paymentStatus << "," << temp->amountPaid << ","
                << temp->year << "\n";
        temp = temp->next;
    }
    cout << "\n\t\t\t\t\t\t\t\t\tFee records saved to CSV.\n";
}

// Function to load fee records from a CSV file
void loadFeeRecords(FeeRecord*& feeHead) {
    ifstream inFile("fee_records.csv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        FeeRecord* newRecord = new FeeRecord;
        getline(ss, line, ',');
        newRecord->studentID = stoi(line);
        getline(ss, newRecord->studentName, ',');
        getline(ss, newRecord->studentGender, ',');
        getline(ss, newRecord->phoneNumber, ',');
        getline(ss, newRecord->paymentStatus, ',');
        getline(ss, line, ',');
        newRecord->amountPaid = stod(line);
        getline(ss, line);
        newRecord->year = stoi(line);

        newRecord->next = feeHead;
        feeHead = newRecord;
    }
}

// Function to display the exam result management menu
void examResultsMenu(ExamResult*& examHead) {
    int choice;
    do {
        system("cls");
        int consoleWidth = getConsoleWidth();
        string headerLines[] = {
            R"( _______   __  ___  ___  ___    ______ _____ _____ _   _ _    _____ _____     ___  ___ _____ _   _ _   _  )",
            R"(|  ___\ \ / / / _ \ |  \/  |    | ___ \  ___/  ___| | | | |  |_   _/  ___|    |  \/  ||  ___| \ | | | | |)",
            R"(| |__  \ V / / /_\ \| .  . |    | |_/ / |__ \ `--.| | | | |    | | \ `--.     | .  . || |__ |  \| | | | |)",
            R"(|  __| /   \ |  _  || |\/| |    |    /|  __| `--. \ | | | |    | |  `--. \    | |\/| ||  __|| . ` | | | |)",
            R"(| |___/ /^\ \| | | || |  | |    | |\ \| |___/\__/ / |_| | |____| | /\__/ /    | |  | || |___| |\  | |_| |)",
            R"(\____/\/   \/\_| |_/\_|  |_/    \_| \_\____/\____/ \___/\_____/\_/ \____/     \_|  |_/\____/\_| \_/\___/ )",      

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
        gotoxy((consoleWidth - 50) / 2, menuStartY);
        cout << "1. Add Exam Result\n";
        gotoxy((consoleWidth) / 2, menuStartY);
        cout << "2. View All Results\n";
        gotoxy((consoleWidth - 50) / 2, menuStartY + 2);
        cout << "3. Check Student Performance by ID\n";
        gotoxy((consoleWidth - 50) / 2, menuStartY + 4);
        cout << "4. Check Student Performance by Name\n";
        gotoxy((consoleWidth - 50) / 2, menuStartY  + 6);
        cout << "5. Find Highest and Lowest Grade\n";
        gotoxy((consoleWidth - 50) / 2, menuStartY + 8);
        cout << "0. Exit\n";

        cout << "\n\t\t\t\tEnter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1: 
                addExamResult(examHead); 
                break;
            case 2: 
                
                viewAllResults(examHead); 
                break;
            case 3: 
                checkStudentPerformanceByID(examHead); 
                break;
            case 4: 
                checkStudentPerformanceByName(examHead);
                cin.ignore(); 
                break;
            case 5: 
                findHighestAndLowestGrade(examHead); 
                break;
            case 0: 
                return;
            default: 
                cout << "\n\t\t\t\t\t\t\t\t\tInvalid choice. Please try again.\n"; break;
        }
        cout << "\n\t\t\t\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore();  
        cin.get();     
        system("cls");
    } while (choice != 0);
    
}

// Function to add exam results
void addExamResult(ExamResult*& examHead) {
    ExamResult* newRecord = new ExamResult;
    cout << "\n\t\t\t\tEnter Student ID: ";
    cin >> newRecord->studentID;
    cout << "\n\t\t\t\tEnter Student Name: ";
    cin.ignore();
    getline(cin, newRecord->studentName);
    cout << "\n\t\t\t\tEnter Gender: ";
    cin >> newRecord->studentGender;
    cout << "\n\t\t\t\tEnter Year of Study: ";
    cin >> newRecord->year;
    cout << "\n\t\t\t\tEnter Subject: ";
    cin >> newRecord->subject;
    cout << "\n\t\t\t\tEnter Grade: ";
    cin >> newRecord->grade;

    newRecord->next = examHead;
    examHead = newRecord;
    saveExamResultsToCSV(examHead);
    cout << "\n\t\t\t\t\t\t\t\t\tExam result added successfully.\n";
}

// Function to view all exam results
void viewAllResults(ExamResult* examHead) {
    if (!examHead) {
        cout << "No exam results to display.\n";
        return;
    }

    cout << "\t\t\t\t\tStudent ID" 
    << setw(20)  << "Student Name" 
    << setw(20) << "Gender" 
    << setw(10) << "Year" 
    << setw(15) << "Subject" 
    << setw(10) << "Grade" 
    << endl;
    cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    ExamResult* temp = examHead;
    while (temp) {
        cout <<"\t\t\t\t\t"<< setw(10) << temp->studentID << setw(20) << temp->studentName << setw(20) 
             << temp->studentGender << setw(10) << temp->year << setw(15) << temp->subject << setw(10) << temp->grade << endl;
        temp = temp->next;
    }
}

// Function to check performance by student ID
void checkStudentPerformanceByID(ExamResult* examHead) {
    int studentID;
    cout << "\n\t\t\t\tEnter Student ID: ";
    cin >> studentID;

    ExamResult* temp = examHead;
    while (temp) {
        if (temp->studentID == studentID) {
            cout << "\n\t\t\t\tStudent Name: " << temp->studentName << "\n";
            cout << "\n\t\t\t\tYear: " << temp->year << "\n";
            cout << "\n\t\t\t\tSubject: " << temp->subject << "\n";
            cout << "\n\t\t\t\tGrade: " << temp->grade << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "\n\t\t\t\t\t\t\t\t\tRecord not found for Student ID " << studentID << endl;
}

// Function to check performance by student name
void checkStudentPerformanceByName(ExamResult* examHead) {
    string studentName;
    cout << "\n\t\t\t\tEnter Student Name: ";
    cin.ignore();
    getline(cin, studentName);

    ExamResult* temp = examHead;
    while (temp) {
        if (temp->studentName == studentName) {
            cout << "\n\t\t\t\tStudent ID: " << temp->studentID << "\n";
            cout << "\n\t\t\t\tYear: " << temp->year << "\n";
            cout << "\n\t\t\t\tSubject: " << temp->subject << "\n";
            cout << "\n\t\t\t\tGrade: " << temp->grade << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "\n\t\t\t\t\t\t\t\t\tRecord not found for Student Name " << studentName << endl;
}

// Function to find highest and lowest grades
void findHighestAndLowestGrade(ExamResult* examHead) {
    if (!examHead) {
        cout << "\n\t\t\t\t\t\t\t\t\tNo exam records available.\n";
        return;
    }

    string highestGrade = examHead->grade;
    string lowestGrade = examHead->grade;
    ExamResult* temp = examHead;

    while (temp) {
        if (temp->grade > highestGrade) {
            highestGrade = temp->grade;
        }
        if (temp->grade < lowestGrade) {
            lowestGrade = temp->grade;
        }
        temp = temp->next;
    }

    cout << "\n\t\t\t\tHighest Grade: " << highestGrade << "\n";
    cout << "\n\t\t\t\tLowest Grade: " << lowestGrade << "\n";
}

// Function to save exam results to a CSV file
void saveExamResultsToCSV(ExamResult* examHead) {
    ofstream outFile("exam_results.csv");
    ExamResult* temp = examHead;
    while (temp) {
        outFile << temp->studentID << "," << temp->studentName << "," << temp->studentGender << ","
                << temp->year << "," << temp->subject << "," << temp->grade << "\n";
        temp = temp->next;
    }
    cout << "\n\t\t\t\t\t\t\t\t\tExam results saved to CSV.\n";
}

// Function to load exam results from a CSV file
void loadExamResults(ExamResult*& examHead) {
    ifstream inFile("exam_results.csv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        ExamResult* newRecord = new ExamResult;
        string grade;
        getline(ss, line, ',');
        newRecord->studentID = stoi(line);
        getline(ss, newRecord->studentName, ',');
        getline(ss, newRecord->studentGender, ',');
        getline(ss, line, ',');
        newRecord->year = stoi(line);
        getline(ss, newRecord->subject, ',');
        getline(ss, newRecord->grade);

        newRecord->next = examHead;
        examHead = newRecord;
    }
    cout << "\n\t\t\t\t\t\t\t\t\tExam results loaded from CSV.\n";
}

#endif
