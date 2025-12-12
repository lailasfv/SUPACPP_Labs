#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
// #include "FiniteFunctions.h"
#include "CustomFunctions.h"
#include <filesystem> //To check extensions in a nice way

using std::filesystem::path;


// Overloaded constructor for normal distribution
normFunc::normFunc(double range_min, double range_max, double mean, double stdev, std::string outfile){
    // FiniteFunction(range_min, range_max, outfile); this isn't working?
    m_RMin = range_min;
    m_RMax = range_max;
    m_mean = mean;
    m_stdev = stdev;
    this->checkPath(outfile);
}

double normFunc::normalDist(double x){
    const double inv_sqrt_2pi = 1.0/ std::sqrt(2.0 * M_PI);
    double pow = (x - m_mean) / m_stdev;  // power in exponent

    return (inv_sqrt_2pi / m_stdev) * std::exp(-0.5 * pow * pow);
}

// for normFunc to call the normal distribution function instead of invxsquared when integrating
double normFunc::callFunction(double x){return this->normalDist(x);}



// Overloaded constructor for cauchy distribution
cauchy::cauchy(double range_min, double range_max, double x0, double gamma, std::string outfile){
    // FiniteFunction(range_min, range_max, outfile); this isn't working?
    m_RMin = range_min;
    m_RMax = range_max;
    m_x0 = x0;                  // effectively the mean
    m_gamma = gamma;            // FWHM
    this->checkPath(outfile);
}

double cauchy::cauchyFunc(double x){
    double denom = (x - m_x0) * (x - m_x0) + m_gamma * m_gamma;
    return (m_gamma / (M_PI * denom));
}

// for cauchy to call correct function
double cauchy::callFunction(double x){return this->cauchyFunc(x);};


// Overloaded constructor for crystal ball distribution
crystal::crystal(double range_min, double range_max, double lowN, double alpha, double xHat, double sigma, std::string outfile){
    // FiniteFunction(range_min, range_max, outfile); this isn't working?
    m_RMin = range_min;
    m_RMax = range_max;
    m_lowN = lowN;      // power law exponent
    m_alpha = alpha;    // transition point
    m_xHat = xHat;      // gaussian peak
    m_sigma = sigma;    // gaussian width
    this->checkPath(outfile);
}

double crystal::crystalBall(double x){
    const double sqrtPiOver2 = std::sqrt(M_PI / 2.0);
    const double sqrt2 = std::sqrt(2.0);

    double t = (x - m_xHat) / m_sigma;
    double absAlpha = std::fabs(m_alpha);

    // constants
    double A = std::pow(m_lowN / absAlpha, m_lowN) * std::exp(-0.5 * absAlpha * absAlpha);
    double B = m_lowN / absAlpha - absAlpha;

    // normalisation factor
    double C = (m_lowN / absAlpha) * std::exp(-0.5 * absAlpha * absAlpha) / (m_lowN - 1.0); 
    double D = sqrtPiOver2 * (1.0 + std::erf(absAlpha / sqrt2)); 

    double N = 1.0 / (m_sigma * (C + D));  // normalisation constant

    // alpha conditions

    if (t > -absAlpha) {
        return N * std::exp(-0.5 * t * t);

    } else {
        return N * A * std::pow(B - t, -m_lowN);
    }
}

// for crystal to call correct function
double crystal::callFunction(double x){return this->crystalBall(x);};

// To load mystery data file
void fileLoad(const std::string filename, std::vector<double>& x){
    std::string line;
    std::ifstream datafile(filename);
    if (!datafile.is_open()){
        std::cout << "Error: Unable to open file";
        exit (1);
    }
    while (getline(datafile, line)){
        x.push_back(stod(line));
    }    
}

int main(){

    // NOTES TO COME BACK TO

    // load in random generated data
    // use user input for each test parameter to match to the generated data without recompiling each time
    // (THIS INPUT WILL BE REMOVED LATER)

    // implement metropolis algorithm...

    int nPoints = 1000;

    double min = -10.0;
    double max = 10.0;

    std::vector<double> x;
    fileLoad("./Outputs/data/MysteryData03420.txt", x);

    std::string inputMean;
    std::string inputStd;

    std::cout << "Choose mean for normal distribution" << std::endl;
    std::cin >> inputMean;
    double mean = stod(inputMean);

    std::cout << "Choose deviation for normal distribution" << std::endl;
    std::cin >> inputStd;
    double std = stod(inputStd);

    normFunc nTest(min, max, mean, std, "normtest");
    nTest.integral(nPoints);
    nTest.printInfo();
    nTest.plotFunction();
    nTest.plotData(x, nPoints, true);


    std::string inputX0;
    std::string inputGamma;

    std::cout << "Choose x0 for cauchy distribution" << std::endl;
    std::cin >> inputX0;
    double x0 = stod(inputX0);

    std::cout << "Choose gamma for cauchy distribution" << std::endl;
    std::cin >> inputGamma;
    double gamma = stod(inputGamma);


    cauchy cTest(min, max, x0, gamma, "cauchytest");
    cTest.integral(nPoints);
    cTest.printInfo();
    cTest.plotFunction();
    cTest.plotData(x, nPoints, true);


    std::string inputN;
    std::string inputAlpha;
    std::string inputXHat;
    std::string inputSigma;

    std::cout << "Choose n for crystal ball distribution" << std::endl;
    std::cin >> inputN;
    double n = stod(inputN);

    std::cout << "Choose alpha for crystal ball distribution" << std::endl;
    std::cin >> inputAlpha;
    double alpha = stod(inputAlpha);

    std::cout << "Choose mean for crystal ball distribution" << std::endl;
    std::cin >> inputXHat;
    double xHat = stod(inputXHat);

    std::cout << "Choose deviation for crystal ball distribution" << std::endl;
    std::cin >> inputSigma;
    double sigma = stod(inputSigma);

    crystal c2Test(min, max, n, alpha, xHat, sigma, "crystaltest");
    c2Test.integral(nPoints);
    c2Test.printInfo();
    c2Test.plotFunction();
    c2Test.plotData(x, nPoints, true);

    return 0;
}