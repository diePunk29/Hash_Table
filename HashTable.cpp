#include <iostream>
#include <cstdlib>
using namespace std;
/**
 * Author: Cristian Mosqueda
 * Class: CSE 310 SUMMER 2020 SESSION
 * Date: 6/19/20
 * Program Purpose: Implementation/Declaration of a HashTable for HW5.
 */

//table size
const int T_SIZE = 1000;
int testKey = 0; //use this to make sure keys are DISTINCT!

class HashTable {
    private:
        //hash record/node
        struct HashRecord {
            int key;
            string name;
            double gpa;
            string academicLvl;
            HashRecord* next;
        };

    public:
        //pointer to a pointer
        HashRecord** hTablePtr;
        //helper pointers
        HashRecord* curr;
        HashRecord* prev;
        //constructor
        HashTable() {
            //creating an array of hash record pointers 
            hTablePtr = new HashRecord*[T_SIZE];
            //setting all pointers to null
            for(int j = 0; j < T_SIZE; j++) {
                *(hTablePtr + j) = NULL; //sets each individual address to null
            }
        }
        ~HashTable() {
            //destructor
        }
        //function declarations
        int HashFunction(int);
        void Insert(string, double, string, int);
        void Delete(int);
        bool Search(int);  
        char menu();
};

//function definitions/implementation
int HashTable::HashFunction(int key) {
    return key % T_SIZE; //k mod m
}
// k is the key
//inserts at the front of the list
void HashTable::Insert(string name, double gpa, string acLvl, int k) {

    //checks to see if keys are distinct
    if(testKey == k) {
        cout << " ERROR: KEY ENTERED HAS BEEN USED FOR A STUDENT RECORD ALREADY." << endl;
        return;
    }

    //slot that the key maps to
    int hash_num = HashFunction(k);

    curr = NULL;
    HashRecord* slotPtr; //pointer to the slot that the key hashes to
    curr = hTablePtr[hash_num]; //curr is pointing to that hash value for the key in hash table

    //initializing the new record
    slotPtr = new HashRecord();
    slotPtr->name = name;
    slotPtr->gpa = gpa;
    slotPtr->academicLvl = acLvl;
    slotPtr->key = k;
    slotPtr->next = NULL;

    //checking if the slot has any record or is NULL
    if(curr == NULL) {
        //acts like the head pointer 
        hTablePtr[hash_num] = slotPtr; //the slot now contains the recently created record
    }
    else {
        //if there is something in that hash slot then
        //curr will point to that record
        slotPtr->next = curr; //make the new record's next attribute point to previously added record
        hTablePtr[hash_num] = slotPtr; //now newly created hash record is the first element of list
    }
    testKey = k;
}

void HashTable::Delete(int key) {
    //getting the hash value or slot index of key you want to delete
    int hash_value = HashFunction(key);
    HashRecord* deleteHRec = NULL; //will point to record that user wants to remove
    curr = hTablePtr[hash_value]; //pointing to the head the linked list in hash slot
    prev = NULL;

    //trying to find they key in the list in order to delete it
    while(curr != NULL && curr->key != key) {
        prev = curr; //prev is always one step behind curr
        curr = curr->next; //advancing curr pointer 
    } 

    //if curr == NULL there was no record in the list with the provided key
    if(curr == NULL) {
        cout << " ERROR: NO RECORD WITH THE KEY " << key << " WAS FOUND." << endl;
        delete deleteHRec; //deleting the pointer
        return; //returning to main
    }
    deleteHRec = curr;
    //if the node the user wants to remove is the head then
    if(deleteHRec == hTablePtr[hash_value]) {
        //advance head pointer to get next record in list
        hTablePtr[hash_value] = hTablePtr[hash_value]->next;
        delete deleteHRec;
    }
    else {
        curr = curr->next;
        prev->next = curr; //cutting out the node the user wants to delete
        delete deleteHRec;
    }  

    cout << " Record with key " << key << " has been removed from the hash table." << endl;
}

bool HashTable::Search(int key) {
    int hash_val = HashFunction(key); //get hash value of key
    curr = hTablePtr[hash_val]; //curr is pointing to the head of the slot linked list
    while(curr != NULL) {
        if(curr->key == key) {
            cout << "\n Student record " << endl;
            cout << " ==============" << endl;
            cout << " Key -> " << curr->key << endl;
            cout << " Name -> " << curr->name << ".\n";
            printf(" GPA -> %.2lf.\n", curr->gpa);
            cout << " Academic Level -> " << curr->academicLvl << ".\n";
            cout << " FOUND AT HASH INDEX/VALUE: " << hash_val << ".\n";
            return true;
        }
        curr = curr->next; //advance pointer until you find it
    }
    return false;
}

char HashTable::menu() {
    //interface for hash table
    char choice;
    cout << endl << " ***** Student Hash Table Menu ***** " << endl;
    cout << " =================================== " << endl;
    cout << " 1. Insert a student record (KEY MUST BE B/W 0 - 65,536)." << endl;
    cout << " 2. Search for a student record." << endl;
    cout << " 3. Delete a student record." << endl;
    cout << " 4. Exit. " << endl;
    cout << endl << " Enter your choice > ";
    cin >> choice;

    return choice;
}

