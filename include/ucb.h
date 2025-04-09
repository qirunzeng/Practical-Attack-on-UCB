#ifndef _UCB_H_
#define _UCB_H_

#include <vector>
#include <cmath>
#include <numeric>
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
    
    ucb(int K, double sigma) : K(K), sigma(sigma), empirical_mean_vec(K), time_slot(0) {
        while (time_slot < K) { // Warm-Up Phase
            empirical_mean_vec[time_slot] = env::generateGaussian(time_slot);
            time_slot++;
        }
    }

    int step() {
        time_slot++;
        std::vector<double> ucb_index(empirical_mean_vec);
        for (int i = 0; i < K; ++i) {
            empirical_mean_vec[i] += 3 * sigma * sqrt(log(time_slot) / pull[i]);
        }

        return arm = *max_element(ucb_index.begin(), ucb_index.end());
    }

    void update(double fdbk) {
        // pull[arm]++;
        empirical_mean_vec[arm] = (empirical_mean_vec[arm] * pull[arm] + fdbk) / (pull[arm]+1);
        pull[arm]++;
    }
};


#endif // _UCB_H_