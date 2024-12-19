#include <iostream>
#include "crud.h"
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
using namespace std;

int main() {
    int choice;
    LinkedList *list = new LinkedList;

    while(true) {
        system("cls");
        cout << "\t\t\tPlease enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 0:
                cout <<"\n\t\tThe program is turned off\n\n";
                exit(0);
                break;
            case 1:
                list->writeToFile();
                break;
            case 2:
                list->display();
                break;
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
    }
    
    
    return 0;
}