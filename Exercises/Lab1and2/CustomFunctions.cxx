//file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>
using namespace std;

void fileLoad(const string filename, vector<double>& x, vector<double>& y){
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

void printLine(vector<double>& x, vector<double>& y){
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
}

void calcMagnitude(vector<double>& x, vector<double>& y){
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
}

void leastSq(vector<double>& x, vector<double>& y){
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

    string outFile = "Least squares test.txt";
    ofstream squareStream;
    squareStream.open(outFile);

    if (!squareStream.is_open()) {
        cout << "Error opening file " << outFile << endl;
        exit(1);
    }
    else{
        cout << "Output file " << outFile << " opened successfully!" << endl;
    }

    squareStream << "Least squares: y = " << p << "x + " << q << endl;
    vector<double> yLeastSq;
    double chiSq;
    for (int k = 0; k < nPoints; k++){
        yLeastSq.push_back(p * x[k] + q);
        chiSq += (yLeastSq[k] - y[k])*(yLeastSq[k] - y[k])/(yErr[k]*yErr[k]);
        squareStream << "x: " << x[k] << " y_O: " << yLeastSq[k] << "y_E: " << y[k] << endl;
        squareStream << "Expected error: " << yErr[k] << " ";
        squareStream << "Actual error y_O - y_E: " << (yLeastSq[k] - y[k]) << endl;
        //cout << y[k] << endl; 
        //cout << yLeastSq[k] << endl;
    }
    squareStream << "Chi squared calculated error: " << chiSq << endl;
    squareStream.close();
    cout << "Least squares analysed data saved to " << outFile << endl;

}

double recursivePower(double a, int b){
    if (b == 0){
        return a;
    }
    return recursivePower(a, b-1);
}

void xPowerY(vector<double>& x, vector<double>& y){
    string powerFile = "x^y.txt";
    ofstream powerStream;
    powerStream.open(powerFile);
    
    if (!powerStream.is_open()){
        cout << "Error opening file: " << powerFile << endl;
        exit(1);
    }
    else{
        cout << "Output file " << powerFile << " opened successfully!" << endl;
        for (int i = 0; i < x.size(); i++){
            powerStream << recursivePower(x[i], int(y[i])) << endl;
        }
        cout << "Power data successfully saved to " << powerFile << endl;
    }
    powerStream.close();

}