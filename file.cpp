#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void writeFile() {
    string filename, data;
    cout << "Enter file name to write: ";
    cin >> filename;
    cin.ignore();
    cout << "Enter data to write: ";
    getline(cin, data);

    ofstream outfile(filename);
    if (!outfile) {
        cout << "Error opening file!" << endl;
        return;
    }
    outfile << data << endl;
    outfile.close();
    cout << "Data written successfully!" << endl;
}

void readFile() {
    string filename, line;
    cout << "Enter file name to read: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file!" << endl;
        return;
    }
    cout << "File Contents:" << endl;
    while (getline(infile, line)) {
        cout << line << endl;
    }
    infile.close();
}

void appendFile() {
    string filename, data;
    cout << "Enter file name to append: ";
    cin >> filename;
    cin.ignore();
    cout << "Enter data to append: ";
    getline(cin, data);

    ofstream outfile(filename, ios::app);
    if (!outfile) {
        cout << "Error opening file!" << endl;
        return;
    }
    outfile << data << endl;
    outfile.close();
    cout << "Data appended successfully!" << endl;
}

int main() {
    int choice;
    do {
        cout << "\n--- File Management Tool ---\n";
        cout << "1. Write File\n2. Read File\n3. Append File\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: writeFile(); break;
            case 2: readFile(); break;
            case 3: appendFile(); break;
            case 4: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    return 0;
}
