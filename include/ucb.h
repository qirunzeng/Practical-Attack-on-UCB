#ifndef _UCB_H_
#define _UCB_H_

#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "env.h"

namespace bandit {
    class ucb;
}

class bandit::ucb  {
private:
public:
    std::vector<double> empirical_mean_vec;
    std::vector<int>    pull;
    int K;
    double sigma;
    int time_slot;
    int arm;
    
    ucb(int K, double sigma) : K(K), sigma(sigma), empirical_mean_vec(K), pull(K), time_slot(0) {
        while (time_slot < K) { // Warm-Up Phase
            empirical_mean_vec[time_slot] = env::generateGaussian(time_slot);
            pull[time_slot] = 1;
            time_slot++;
        }
        // std::cout << arm << std::endl;
        // for (int i = 0; i < K; ++i) {
        //     std::cout << empirical_mean_vec[i] << " " << pull[i] << " | ";
        // }
        // std::cout << std::endl;
    }

    int step() {
        time_slot++;
        std::vector<double> ucb_index(empirical_mean_vec);
        for (int i = 0; i < K; ++i) {
            ucb_index[i] += 3 * sigma * sqrt(log(time_slot) / pull[i]);
        }

        return arm = max_element(ucb_index.begin(), ucb_index.end()) - ucb_index.begin();
    }

    void update(double fdbk) {
        // pull[arm]++;
        // std::cout << arm << ": " << fdbk << " " << empirical_mean_vec[arm] << " "  << pull[arm] << " " << (empirical_mean_vec[arm] * pull[arm] + fdbk) << " ";
        empirical_mean_vec[arm] = (empirical_mean_vec[arm] * pull[arm] + fdbk) / (pull[arm]+1);
        // std::cout << empirical_mean_vec[arm] << " | ";
        pull[arm]++;
    //     std::cout << arm << std::endl;
    //     for (int i = 0; i < K; ++i) {
    //         std::cout << empirical_mean_vec[i] << " ";
    //     }
    //     std::cout << std::endl;
    }
};


#endif // _UCB_H_