#ifndef _ENV_H_
#define _ENV_H_

#include <vector>
#include <iostream>
#include <random>
#include <cmath>

namespace env {
    std::vector<double> mean_vec;
    double sigma;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::vector<std::normal_distribution<double>> distributions;

    void init(int n, double default_sigma = 1.0) {
        sigma = default_sigma;
        mean_vec.resize(n);
        for (int i = 0; i < n; ++i) {
            mean_vec[i] = static_cast<double> (n-i) / (n+1);
        }
        distributions.reserve(n);
        for (int i = 0; i < n; ++i) {
            distributions.emplace_back(mean_vec[i], sigma);
        }
    }
    
    double generateGaussian(int arm) {
        return distributions[arm](gen);
    }
};


#endif // _ENV_H_