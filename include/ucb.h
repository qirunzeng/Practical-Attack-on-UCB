#ifndef _UCB_H_
#define _UCB_H_

#include <vector>
#include "env.h"

namespace bandit {
    class ucb;
}

class bandit::ucb  {
private:
    std::vector<double> empirical_mean_vec;
    int time_slot;
public:
    ucb(int n) : empirical_mean_vec(n), time_slot(0) {
        env::init(n);
        while (time_slot < n) { // Warm-Up Phase
            empirical_mean_vec[time_slot] = env::generateGaussian(time_slot);
            time_slot++;
        }
    }

    int step() {
        time_slot++;

    }
};


#endif // _UCB_H_