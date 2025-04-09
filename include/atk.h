#ifndef _ATK_H_
#define _ATK_H_

#include "env.h"
#include "ucb.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

namespace atk {
    double sigma = 0.5;
    double pi = 3.1416;
    double e = 2.71828;
    double cost = 0.00;

    void run(int K, int T, double delta, int R) {
        env::init(K, sigma);
        std::cout << "Init over" << std::endl;
        bandit::ucb bandit_alg(K, sigma);
        const int target = K-1;
        int non_target_pull = 0;

        std::vector<int> mean0(K);

        std::function<double(double)> beta = [&K, &delta](int n) -> double {
            return sqrt(2 * sigma * sigma * log(pi * K * n * n / e / delta) / n);
        };

        bool flag = true;
        while (bandit_alg.time_slot < T) {
            int arm = bandit_alg.step();

            if (bandit_alg.time_slot % (R+1) == 0) {
                flag = true;
            }

            if (arm != target) {
                // non_target_pull++;
                double b = beta(bandit_alg.pull[target]);
                // std::cout << b << std::endl;
                double fdbk0 = env::generateGaussian(arm);
                if (flag) {
                    double fdbk = (bandit_alg.empirical_mean_vec[target]-2*b-3*sigma) * (bandit_alg.pull[arm]+1) - bandit_alg.empirical_mean_vec[arm] * bandit_alg.pull[arm];
                    bandit_alg.update(fdbk);
                    cost += fdbk0 - fdbk;
                    flag = false;
                } else {
                    bandit_alg.update(fdbk0);
                }
                // std::cout << "(" << fdbk << " " << fdbk0 << ") ";
            } else {
                bandit_alg.update(env::generateGaussian(arm));
            }
        }
        std::cout << std::endl;
        std::cout << "--------------------------" << std::endl;
        for (int i = 0; i < K; ++i) {
            std::cout << bandit_alg.empirical_mean_vec[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < K; ++i) {
            std::cout << bandit_alg.pull[i] << " ";
        }
        std::cout << std::endl << cost << std::endl;
    }
}

#endif // _ATK_H_