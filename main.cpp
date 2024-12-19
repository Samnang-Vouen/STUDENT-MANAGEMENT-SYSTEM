#include <iostream>
#include "StylizedHeader.h"
#include "LoadingAnimation.h"
#include "login.h"

#include <cstdlib> // For system("cls")

int main() {
    simulateLoading();
    printLogin();
    getUserCredentials();
    system("cls");
    printStylizedHeader();
    simulateLoading();
    return 0;
}