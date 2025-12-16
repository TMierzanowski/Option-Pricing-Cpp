#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

#include <string>

//Two types of option: Call, Put
enum class OptionType {
    Call,
    Put
};

class EuropeanOption {
public:
    //Constructor
    EuropeanOption(double spot, double strike, double rate, double vol, double time, OptionType type);

    //Two Pricing Methods: Black-Scholes, Monte Carlo
    double BlackScholes() const;              //Black-Scholes formula
    double MonteCarlo(int n) const;    //Monte Carlo with n simulations

    //Greeks
    double delta() const;
    double gamma() const;
    double vega() const;
    double theta() const;
    double rho() const;

    //Value access
    double getSpot() const { return S; }
    double getStrike() const { return K; }
    std::string getTypeString() const;

private:
    double S;     //Spot price
    double K;     //Strike price
    double r;     //Risk-free rate
    double sigma; //Volatility
    double T;     //Time to maturity
    OptionType type;

    //CDF and PDF for N(0,1)
    double stdNormalCDF(double x) const;
    double stdNormalPDF(double x) const;
};

#endif
