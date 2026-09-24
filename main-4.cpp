#include <stdio.h>
#include "CrewMember.hpp"
#include "HumanCrew.hpp"
#include "file_reader.hpp"
#include "HumanCrew.hpp"
#include "AlienCrew.hpp"
#include "crew_merge.hpp"
#include <iostream>
#include "testingFunctions.hpp"
using namespace std;


int main()
{
    printMenu();
    int choice;
    while(true){
        printMenu();
        cin>>choice;
        if (choice == 7)
        {
            cout << "Exiting the testing program." << endl;
            break;
        }
    switch (choice) {
        case 1:
            runAllTests();
            break;
        case 2:
            testInsertAndSort();
            break;
        case 3:
            testSearch();
            break;
        case 4:
            deleteTest();
            break;
        case 5:
            mergeTest();
            break;
        case 6:
            qualifiedTest();
            break;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
    }
}       
    return 0;
}