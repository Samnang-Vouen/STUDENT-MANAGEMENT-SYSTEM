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
#include "fee_exam_management.h"

using namespace std;

int main() {
    char choice;
    LinkedList *list = new LinkedList;
    FeeRecord* feeHead = nullptr;
    ExamResult* examHead = nullptr;

    system("cls");
    simulateLoading();
    printLogin();
    getUserCredentials();
    while(true) {
        menu();
        cout << "\n\t\t\t\tPlease enter your choice: ";
        cin>>choice;
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
            case '6':
                feeManagementMenu(feeHead);
                break;
            case '7':
                loadExamResults(examHead);
                examResultsMenu(examHead);
                break;
            case '5':
                searchMenu(*list);
                break;
            default :
                cout << "\n\t\t\t\t\t\t\t\t\tInvalid choice, please try again" << endl;
                break;
        }
        cout << "\n\t\t\t\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore();
    }
    simulateLoading();
}
