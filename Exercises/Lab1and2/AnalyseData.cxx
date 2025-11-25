//file operations
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;


int main () {
    string line;
    vector<double> x;
    vector<double> y;
    ifstream datafile("input2D_float.txt", ios::in);
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
    // END OF READING FUNCTION
    cout << "Please type an integer" << endl;
    int N;
    string N_input;
    cin >> N_input; // input for the number of lines
    N = stoi(N_input);
    if (N > x.size()){
        cout << "Input too large - defaulting to print 5 lines" << endl;
        N = 5;
    }
    // END OF PRINTING FUNCTION
    for (int i = 0; i < N; i++){
        cout << "x = " << x[i] << " ";
        cout << "y = " << y[i] << endl;
        cout << "Magnitude of data point = " << sqrt(x[i]*x[i] + y[i]*y[i]) << endl;
    }
    // Straight line test
    double xsum = 0;
    double ysum = 0;
    double xsq = 0;
    double xy = 0;
    for (int j = 0; j < size(x); j++){
        xsum += x[j];
        ysum += y[j];
        xsq += (x[j] * x[j]);
        xy += (x[j] * y[j]);
    }
    double p = (size(x)*xy - xsum*ysum)/(size(x)*xsq-xsum*xsum);
    double q = (xsq*ysum - xy*xsum)/(size(x)*xsq - xsum*xsum);
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;

}