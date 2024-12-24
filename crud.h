#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
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
                cout << "\n\t\t\tError: Unable to open file" << endl;
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
                cout << "\n\t\t\tFile updated successfully." << endl;
            } else {
                cout << "\n\t\t\tNo changes made to the file." << endl;
            }
        }

        void saveToFile(string fileName) {
            fstream file;
            file.open(fileName, ios::out);
            if(!file.is_open()) {
                cout << "\n\t\t\tError: Unable to open file" << endl;
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
};