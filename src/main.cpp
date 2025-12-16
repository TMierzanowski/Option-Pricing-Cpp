#include <iostream>
#include <iomanip>
#include "EuropeanOption.hpp"

int main() {
    //Parameters
    double spot = 100.0;   //S
    double strike = 100.0; //K
    double r = 0.05;       //risk-free rate
    double vol = 0.2;      //volatility
    double T = 1.0;        //maturity

    //Choosing the type of option
    char callput;
    std::cout << "Wybierz typ opcji (C = Call, P = Put): ";
    std::cin >> callput;

    OptionType optType;
    if (callput == 'C' || callput == 'c') {
        optType = OptionType::Call;
    } else if (callput == 'P' || callput == 'p') {
        optType = OptionType::Put;
    } else {
        std::cerr << "Invalid character. Assuming call option." << std::endl;
        optType = OptionType::Call;
    }

    EuropeanOption Option(spot, strike, r, vol, T, optType);

    std::cout << "Option Type: " << Option.getTypeString() << std::endl;
    std::cout << "Spot: " << spot << ", Strike: " << strike << std::endl;
    std::cout << "Maturity: " << T << " years, Vol: " << vol * 100 << "%" << std::endl;
    
    std::cout << std::endl << "[Pricing]" << std::endl;
    
    //Black-Scholes
    double bs_price = Option.BlackScholes();
    std::cout << "Black-Scholes Price: " << std::fixed << std::setprecision(5) << bs_price << std::endl;

    //Monte Carlo
    int simulations[] = {1000, 10000, 100000, 1000000};
    for (int n : simulations) {
        double mc_price = Option.MonteCarlo(n);
        double diff = std::abs(mc_price - bs_price);
        std::cout << "Monte Carlo (" << n << " sims): " 
                  << mc_price << " (Diff: " << diff << ")" << std::endl;
    }

    std::cout << std::endl << "Greeks" << std::endl;
    std::cout << "Delta: " << Option.delta() << std::endl;
    std::cout << "Gamma: " << Option.gamma() << std::endl;
    std::cout << "Vega:  " << Option.vega() << std::endl;
    std::cout << "Theta:  " << Option.theta() << std::endl;
    std::cout << "Rho:  " << Option.rho() << std::endl;

    return 0;
}
