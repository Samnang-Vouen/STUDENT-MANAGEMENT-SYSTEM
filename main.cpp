#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include "StylizedHeader.h"
#include "LoadingAnimation.h"
#include "login.h"
#include "menu.h"
#include "crud.h"
using namespace std;

int main() {
    int choice;
    LinkedList *list = new LinkedList;

    system("cls");
    simulateLoading();
    printLogin();
    getUserCredentials();
    system("cls");
    printStylizedHeader();
    simulateLoading();

    while(true) {
        system("cls");
        menu();
        cout << "\t\t\t\tPlease enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
        switch(choice) {
            case 0:
                cout <<"\n\t\t\tThe program is turned off\n\n";
                exit(0);
                break;
            case 1:
                list->create();
                break;
            case 2:
                list->display();
                break;
            case 3:
                list->update();
                break;
            case 4:
                list->removeById();
                break;
            default :
                cout << "\n\t\t\tInvalid choice, please try again" << endl;
                break;
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
    }
}
