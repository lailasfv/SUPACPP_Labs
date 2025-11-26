//file operations
#include <iostream>
#include <string>
#include <vector>
#include "CustomFunctions.h"
using namespace std;


int main () {
    vector<double> x;
    vector<double> y;
    // Input file will need to be loaded regardless of choice
    fileLoad("input2D_float.txt", x, y);
    cout << "Data file loaded successfully!" << endl;

    int choice;
    bool go = true;

    while(go){
        cout << "Please select one of the following options:" << endl;
        cout << "1: Print N lines of data file" << endl;
        cout << "2: Calculate magnitude of data points" << endl;
        cout << "3: Assess least squares fitting" << endl;
        cout << "4: Calculate x^y for each data point" << endl;
        cout << "5: Exit the program" << endl;
        cin >> choice;

        switch (choice) {
            case 1:{
                cout << "You have chosen option 1" << endl;
                printLine(x, y);
                break;
            }
            case 2:{
                cout << "You have chosen option 2" << endl;
                calcMagnitude(x, y);
                break;
            }
            case 3:{
                cout << "You have chosen option 3" << endl;
                leastSq(x, y);
                break;
            }
            case 4:{
                cout << "You have chosen option 4" << endl;
                xPowerY(x, y);
                break;
            }
            case 5:{
                cout << "Exiting the program" << endl;
                exit(1);
            }
            default:{
                cout << "Invalid input" << endl;
                go = false;
                break;
            }
        }
    }

}