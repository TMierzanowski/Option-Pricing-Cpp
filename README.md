# Option-Pricing-Cpp

A pricing engine for European Call/Put options implemented in C++ using Black-Scholes formula and Monte Carlo method.

## Features
* **Black-Scholes Analytical Model:** Exact pricing using closed-form solution.
* **Monte Carlo Simulation:** Path-dependent valuation using Geometric Brownian Motion.
* **Greeks Calculation:** Computes Delta, Gamma, Vega, Theta and Rho.
* **Convergence Analysis:** Demonstrates how Monte Carlo simulation approaches the analytical price as $n \to \infty$.

## Math Background
The engine models the asset price $S_t$ dynamics under the risk-neutral measure:
$$dS_t = r S_t dt + \sigma S_t dW_t$$

## How to Build & Run
Project includes a standard Makefile.

##Prerequisites:
* C++ compiler supporting C++17
* Build system: GNU Make
* OS: Linux, macOS, Windows (WSL/MinGW)

1. Compile (in bash): make
2. Run the engine: ./pricer (Windows without WSL: pricer.exe)
