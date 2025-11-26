//file operations
#include <iostream>
#include <string>
#include <vector>
#include "CustomFunctions.h"
using namespace std;

/*void fileLoad(const string filename, vector<double>& x, vector<double>& y){
    // Loads 2D array with columns x, y into respective vectors
    string line;
    ifstream datafile(filename, ios::in);
    if (!datafile.is_open()){
        cout << "Error: Unable to open file";
        exit (1);
    }
    getline(datafile, line); //skips first line to remove 'x' 'y'
    while (getline(datafile, line)){
        stringstream ss(line);
        string xs, ys;
        // separating the line string into two double values
        if (getline(ss, xs, ',') && getline(ss, ys)){
            x.push_back(stod(xs));
            y.push_back(stod(ys));
        }
    }
    datafile.close();
}
/**/

/*void printLine(vector<double>& x, vector<double>& y){
    cout << "Please enter how many lines you'd like to print" << endl;
    int N;
    string N_input;
    cin >> N_input; // input for the number of lines
    N = stoi(N_input);
    if (N > x.size()){
        cout << "Input too large - defaulting to print 5 lines" << endl;
        N = 5;
    }
    for (int i = 0; i < N; i++){
        cout << "x = " << x[i] << " ";
        cout << "y = " << y[i] << endl;
    }
}*/

/*void calcMagnitude(vector<double>& x, vector<double>& y){
    double mag;
    string outputFile = "magnitude.txt";
    ofstream outStream;
    outStream.open(outputFile);
    if (!outStream.is_open()) {
        cout << "Error opening file: " << outputFile << endl;
        exit (1);
    }
    else{
        cout << "Output file " << outputFile << " opened successfully!" << endl;
        for (int i = 0; i < x.size(); i++){
            outStream << sqrt(x[i]*x[i] + y[i] * y[i]) << endl;
        }
        cout << "Magnitudes successfully saved to " << outputFile << endl;
        outStream.close();
    }
}*/

/*void leastSq(vector<double>& x, vector<double>& y){
    // Error file loaded only within this func, otherwise unnecessary
    vector<double> xErr;
    vector<double> yErr;

    fileLoad("error2D_float.txt", xErr, yErr);

    // Straight line test
    double xsum = 0;
    double ysum = 0;
    double xsq = 0;
    double xy = 0;
    int nPoints = size(x);
    for (int j = 0; j < nPoints; j++){
        xsum += x[j];
        ysum += y[j];
        xsq += (x[j] * x[j]);
        xy += (x[j] * y[j]);
    }
    double p = (nPoints*xy - xsum*ysum)/(nPoints*xsq-xsum*xsum);
    double q = (xsq*ysum - xy*xsum)/(nPoints*xsq - xsum*xsum);
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
}*/

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