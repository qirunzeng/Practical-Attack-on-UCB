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

    void init(int K, double default_sigma = 1.0) {
        sigma = default_sigma;
        mean_vec.resize(K);
        for (int i = 0; i < K; ++i) {
            mean_vec[i] = static_cast<double> (K-i) / (K+1);
            // std::cout << mean_vec[i] << " ";
        }
        // std::cout << std::endl;
        distributions.reserve(K);
        for (int i = 0; i < K; ++i) {
            distributions.emplace_back(mean_vec[i], sigma);
        }
    }
    
    double generateGaussian(int arm) {
        return distributions[arm](gen);
    }
};


#endif // _ENV_H_