#include "EuropeanOption.hpp"
#include <cmath>
#include <random>
#include <vector>
#include <iostream>

//Cumulative Distribution Function for the normal distribution N(0,1)
double EuropeanOption::stdNormalCDF(double x) const {
    return 0.5 * std::erfc(-x * M_SQRT1_2);
}

//Probability Density Function for N(0,1)
double EuropeanOption::stdNormalPDF(double x) const {
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
}

EuropeanOption::EuropeanOption(double spot, double strike, double rate, double vol, double time, OptionType optType)
    : S(spot), K(strike), r(rate), sigma(vol), T(time), type(optType) {}

double EuropeanOption::BlackScholes() const {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (type == OptionType::Call) {
        return S * stdNormalCDF(d1) - K * std::exp(-r * T) * stdNormalCDF(d2);
    } else {
        return K * std::exp(-r * T) * stdNormalCDF(-d2) - S * stdNormalCDF(-d1);
    }
}

double EuropeanOption::MonteCarlo(int n) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0.0, 1.0);

    double payoff_sum = 0.0; //sum of payoffs in all simulations
    double drift = (r - 0.5 * sigma * sigma) * T;
    double vol_sqrt_T = sigma * std::sqrt(T);

    for (int i = 0; i < n; i++) {
        double Z = d(gen);
        double S_T = S * std::exp(drift + vol_sqrt_T * Z);

        double payoff = 0.0;
        if (type == OptionType::Call) {
            payoff = std::max(S_T - K, 0.0);
        } else {
            payoff = std::max(K - S_T, 0.0);
        }
        payoff_sum += payoff;
    }

    return (payoff_sum / static_cast<double>(n)) * std::exp(-r * T); //discounted mean of sum of all payoffs
}

//Greeks

double EuropeanOption::delta() const {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    if (type == OptionType::Call) {
        return stdNormalCDF(d1);
    } else {
        return stdNormalCDF(d1) - 1.0;
    }
}

double EuropeanOption::gamma() const {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return stdNormalPDF(d1) / (S * sigma * std::sqrt(T));
}

double EuropeanOption::vega() const {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return S * stdNormalPDF(d1) * std::sqrt(T);
}

double EuropeanOption::theta() const {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (type == OptionType::Call) {
        return -(S * stdNormalPDF(d1) * sigma) / (2.0 * std::sqrt(T))
               - r * K * std::exp(-r * T) * stdNormalCDF(d2);
    } else {
        return -(S * stdNormalPDF(d1) * sigma) / (2.0 * std::sqrt(T))
               + r * K * std::exp(-r * T) * stdNormalCDF(-d2);
    }
}

double EuropeanOption::rho() const {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (type == OptionType::Call) {
        return K * T * std::exp(-r * T) * stdNormalCDF(d2);
    } else {
        return -K * T * std::exp(-r * T) * stdNormalCDF(-d2);
    }
}

std::string EuropeanOption::getTypeString() const {
    return (type == OptionType::Call) ? "Call" : "Put";
}
