#include <bits/stdc++.h>
using namespace std;

// Rosenbrock function: f(x, y) = (1 - x)^2 + 100*(y - x^2)^2
double rosenbrock(const vector<double>& pos) {
    double x = pos[0], y = pos[1];
    return (1.0 - x)*(1.0 - x) + 100.0*(y - x*x)*(y - x*x);
}

struct Wolf {
    vector<double> position;
    double fitness;
    Wolf(int dim) : position(dim), fitness(DBL_MAX) {}
};

int main() {
    srand(time(nullptr));

    const int dim = 2;                  // (Rosenbrock is 2D)
    const int num_wolves = 10;          // population size
    const int max_iters = 100;          // iterations
    const double xmin = -5, xmax = 5;   // search space bounds

    vector<Wolf> wolves;
    wolves.reserve(num_wolves);

    // Initialize wolves randomly
    for (int i = 0; i < num_wolves; i++) {
        Wolf w(dim);
        for (int d = 0; d < dim; d++) {
            w.position[d] = xmin + (xmax - xmin) * (rand() / (double)RAND_MAX);
        }
        w.fitness = rosenbrock(w.position);
        wolves.push_back(w);
    }

    // Track alpha, beta, delta
    vector<double> alpha_pos(dim), beta_pos(dim), delta_pos(dim);
    double alpha_score = DBL_MAX, beta_score = DBL_MAX, delta_score = DBL_MAX;

    // Main loop
    for (int iter = 1; iter <= max_iters; iter++) {
        // Evaluate wolves
        for (auto &w : wolves) {
            w.fitness = rosenbrock(w.position);

            // Update alpha, beta, delta
            if (w.fitness < alpha_score) {
                delta_score = beta_score; delta_pos = beta_pos;
                beta_score = alpha_score; beta_pos = alpha_pos;
                alpha_score = w.fitness;  alpha_pos = w.position;
            } else if (w.fitness < beta_score) {
                delta_score = beta_score; delta_pos = beta_pos;
                beta_score = w.fitness;   beta_pos = w.position;
            } else if (w.fitness < delta_score) {
                delta_score = w.fitness;  delta_pos = w.position;
            }
        }

        // Linearly decreasing parameter a
        double a = 2.0 - iter * (2.0 / max_iters);

        // Update wolf positions
        for (auto &w : wolves) {
            for (int d = 0; d < dim; d++) {
                double r1 = rand() / (double)RAND_MAX;
                double r2 = rand() / (double)RAND_MAX;

                double A1 = 2 * a * r1 - a;
                double C1 = 2 * r2;
                double D_alpha = fabs(C1 * alpha_pos[d] - w.position[d]);
                double X1 = alpha_pos[d] - A1 * D_alpha;

                r1 = rand() / (double)RAND_MAX;
                r2 = rand() / (double)RAND_MAX;
                double A2 = 2 * a * r1 - a;
                double C2 = 2 * r2;
                double D_beta = fabs(C2 * beta_pos[d] - w.position[d]);
                double X2 = beta_pos[d] - A2 * D_beta;

                r1 = rand() / (double)RAND_MAX;
                r2 = rand() / (double)RAND_MAX;
                double A3 = 2 * a * r1 - a;
                double C3 = 2 * r2;
                double D_delta = fabs(C3 * delta_pos[d] - w.position[d]);
                double X3 = delta_pos[d] - A3 * D_delta;

                // Update position (average of three influences)
                w.position[d] = (X1 + X2 + X3) / 3.0;

                // Keep within bounds
                if (w.position[d] < xmin) w.position[d] = xmin;
                if (w.position[d] > xmax) w.position[d] = xmax;
            }
        }

        if (iter % 10 == 0 || iter == 1) {
            cout << "Iter " << iter
                 << " | Best fitness = " << alpha_score
                 << " at (" << alpha_pos[0]
                 << ", " << alpha_pos[1] << ")\n";
        }
    }

    cout << "\nFinal best solution: (" 
         << alpha_pos[0] << ", " << alpha_pos[1]
         << ") with fitness = " << alpha_score << "\n";

    return 0;
}
