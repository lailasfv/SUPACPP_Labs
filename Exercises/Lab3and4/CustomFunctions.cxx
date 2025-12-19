#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
// #include "FiniteFunctions.h"
#include "CustomFunctions.h"
#include <random>
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

double normFunc::evaluate(double x) const{
    const double inv_sqrt_2pi = 1.0/ std::sqrt(2.0 * M_PI);
    double pow = (x - m_mean) / m_stdev;  // power in exponent

    return (inv_sqrt_2pi / m_stdev) * std::exp(-0.5 * pow * pow);
}

// for normFunc to call the normal distribution function instead of invxsquared when integrating
double normFunc::callFunction(double x){return this->evaluate(x);}



// Overloaded constructor for cauchy distribution
cauchy::cauchy(double range_min, double range_max, double x0, double gamma, std::string outfile){
    // FiniteFunction(range_min, range_max, outfile); this isn't working?
    m_RMin = range_min;
    m_RMax = range_max;
    m_x0 = x0;                  // effectively the mean
    m_gamma = gamma;            // FWHM
    this->checkPath(outfile);
}

double cauchy::evaluate(double x) const{
    double denom = (x - m_x0) * (x - m_x0) + m_gamma * m_gamma;
    return (m_gamma / (M_PI * denom));
}

// for cauchy to call correct function
double cauchy::callFunction(double x){return this->evaluate(x);};


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

double crystal::evaluate(double x) const{
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
double crystal::callFunction(double x){return this->evaluate(x);};

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
    // with tests below, the mystery data file appears to be either norm or crystal ball distribution

    // parameters for function fitting
    int nPoints = 1000;
    double min = -10.0;
    double max = 10.0;

    // parameters for sample generation
    double sample_x0 = 1.0;
    double sampleStd = 5.0;
    int seed = 32045;  // changes random seed for any metropolis algorithm called

    // loading in mystery data file to vector x
    std::vector<double> x;
    fileLoad("./Outputs/data/MysteryData03420.txt", x);

    // -------------------------------------
    // testing normal distribution
    double mean = 1.0;
    double std = 3.0;
    normFunc nTest(min, max, mean, std, "normtest");
    auto samples = nTest.metropolis(sample_x0, nPoints, sampleStd, seed);
    
    nTest.integral(nPoints);
    nTest.plotFunction();
    nTest.plotData(x, nPoints, true);
    nTest.plotData(samples, nPoints, false);

    // -------------------------------------
    // testing cauchy distribution
    // mystery data file
    double x0 = 1.0;
    double gamma = 3;

    cauchy cTest(min, max, x0, gamma, "cauchytest");
    auto samplesC = cTest.metropolis(sample_x0, nPoints, sampleStd, seed);
    cTest.integral(nPoints);
    cTest.plotFunction();
    cTest.plotData(x, nPoints, true);
    cTest.plotData(samplesC, nPoints, false);

    // -------------------------------------
    // testing crystal ball distribution
    //mystery data file
    double n = 3.0;
    double alpha = 3.0;
    double xHat = 1.0;
    double sigma = 3.0;

    crystal c2Test(min, max, n, alpha, xHat, sigma, "crystaltest");
    auto samplesC2 = c2Test.metropolis(sample_x0, nPoints, sampleStd, seed);
    c2Test.integral(nPoints);
    c2Test.plotFunction();
    c2Test.plotData(x, nPoints, true);
    c2Test.plotData(samplesC2, nPoints, false);

    return 0;
}