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
    char choice;
    LinkedList *list = new LinkedList;


    system("cls");
    simulateLoading();
    printLogin();
    getUserCredentials();
    while(true) {
        menu();
        cout << "\n\t\t\t\tPlease enter your choice: ";
        choice = _getch();
        system("cls");
        switch(choice) {
            case '0':
                exit(0);
                break;
            case '1':
                list->create();
                break;
            case '2':
                list->display();
                break;
            case '3':
                list->update();
                break;
            case '4':
                list->removeById();
                break;
            case '5':
                searchMenu(*list);
                break;
            default :
                cout << "\n\t\t\t\t\t\t\t\t\tInvalid choice, please try again" << endl;
                break;
        }
        cout << "\n\t\t\t\t\t\t\t\t\tPress Enter to continue...";
        _getch();
    }
    simulateLoading();
}
