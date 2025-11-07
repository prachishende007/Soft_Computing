#include <iostream>
#include <vector>
#include <numeric>  
#include <random>   

using namespace std;

int can_Selection(const vector<double>& fitness, mt19937& rng) {
    double totalFitness = accumulate(fitness.begin(), fitness.end(), 0.0);

    
    if (totalFitness == 0.0) {
        uniform_int_distribution<int> dist(0, fitness.size() - 1);
        return dist(rng);
    }

    vector<double> probabilities;
    probabilities.reserve(fitness.size());
    for (double f : fitness) {
        probabilities.push_back(f / totalFitness);
    }

    vector<double> cumulative(probabilities.size());
    partial_sum(probabilities.begin(), probabilities.end(), cumulative.begin());

    uniform_real_distribution<double> dist(0.0, 1.0);
    double r = dist(rng);

    for (size_t i = 0; i < cumulative.size(); ++i) {
        if (r <= cumulative[i])
            return static_cast<int>(i);
    }

    return static_cast<int>(fitness.size() - 1);
}

int main() {
    vector<double> fitness = {10.0, 5.0, 1.0, 2.0};

    random_device rd;
    mt19937 rng(rd());

    vector<int> selectionCount(fitness.size(), 0);
    int trials = 10;

    for (int i = 0; i < trials; ++i) {
        int selected = can_Selection(fitness, rng);
        selectionCount[selected]++;
    }

    cout << "Selection frequencies after " << trials << " selections:\n";
    for (size_t i = 0; i < selectionCount.size(); ++i) {
        cout << "Individual " << i << " (fitness=" << fitness[i] << "): "
             << selectionCount[i] << " times\n";
    }
    
    return 0;
}
