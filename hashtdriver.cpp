#include <iostream>
#include <cstdlib>
#include "HashTable.cpp"
using namespace std;
/**
 * Author: Cristian Mosqueda
 * Class: CSE 310 SUMMER 2020 SESSION
 * Date: 06/19/20
 * Program Purpose: Main/Driver for that Hash Table Implemented in HashTable.cpp.
 */

//KEY VALIDITY FUNCTION
bool isKeyValid(int key) {
    return (key >= 0 && key <= 65536); 
}

int main() {
    //instance of HashTable
    HashTable hashy;

    //var dec
    string studName = " ";
    string acadLvl = " ";
    int key;
    double gradPAvg;
    char choice;
    key = 0;
    gradPAvg = 0.0;

    while(true) {
        choice = hashy.menu();
        switch (choice)
        {
        case '1':
                cin.ignore();
                cout << " Enter the student's name > ";
                getline(cin, studName);
                cout << " Enter student's GPA > ";
                cin >> gradPAvg;
                cout << " Enter the student's academic level > ";
                cin >> acadLvl;
                cout << " Enter the key value > ";
                cin >> key;
                //if the key isn't valid
                if(!isKeyValid(key)) {
                    cout << " ERROR: KEY IS NOT IN THE SPECIFIED RANGE." << endl;
                    break;
                }
                hashy.Insert(studName, gradPAvg, acadLvl, key);
                break;
        case '2':
                cout << " Enter the key value for the student record you want to search up > " << endl;
                cin >> key;
                if(hashy.Search(key) == false) {
                    cout << " ERROR: NO STUDENT RECORD WITH KEY: " << key << "." << endl;
                }
                break;
        case '3':
                cout << " Enter the key value for the record you would like to delete > ";
                cin >> key;
                hashy.Delete(key);
                break;
        case '4':
                cout << " ***** SYSTEM EXIT ***** " << endl;
                exit(0);
                break;
        default:
            cout << " ERROR: INVALID CHOICE. " << endl;
        }
    }
}

