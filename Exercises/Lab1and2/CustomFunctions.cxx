//file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>
using namespace std;


void saveData(string filename, vector<double>& data){
    // Task 2 and 4 files require only one vector to be saved
    string outFile = filename;
    ofstream outStream;

    outStream.open(filename);

    if (!outStream.is_open()){
        cout << "Error opening file: " << filename << endl;
        exit (1);
    }
    else{
        cout << "Output file " << filename << " opened successfully!" << endl;
        for (int i = 0; i < data.size(); i++){
            outStream << data[i] << endl;
        }
    }
    outStream.close();
}

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
    vector<double> mag;
    for (int i = 0; i < x.size(); i++){
        mag.push_back(sqrt(x[i]*x[i] + y[i] * y[i]));
    }
    saveData("magnitude.txt", mag);
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
        squareStream << "x: " << x[k] << " y_O: " << yLeastSq[k] << " y_E: " << y[k] << endl;
        squareStream << "Expected error: " << yErr[k] << endl;
        squareStream << "Actual error y_O - y_E: " << (yLeastSq[k] - y[k]) << endl;

    }
    squareStream << "Chi squared calculated error: " << chiSq << endl;
    squareStream.close();
    cout << "Least squares analysed data saved to " << outFile << endl;

}

double recursivePower(double aNew, double a, int b){
    if (b == 1 or b == 0){
        return aNew;
    }
    aNew = aNew*a;
    return recursivePower(aNew, a, b-1);
}

void xPowerY(vector<double>& x, vector<double>& y){

    vector<double> power;
    for (int i = 0; i < x.size(); i++){
        power.push_back(recursivePower(x[i], x[i], int(y[i])));
    }
    saveData("x^y.txt", power);
    cout << "x^y calculated successfully and saved to x^y.txt" << endl;
}