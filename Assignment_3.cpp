//Particle Swarm Optimization Using Rosenbrock Equation
#include <bits/stdc++.h>
using namespace std;

double rosenbrock(const vector<double>& pos) {
    double x = pos[0], y = pos[1];
    return (1.0 - x)*(1.0 - x) + 100.0*(y - x*x)*(y - x*x);
}

struct Particle {
    vector<double> position, velocity;
    vector<double> best_position;
    double fitness = numeric_limits<double>::max();
    double best_fitness = numeric_limits<double>::max();

    Particle(int dim) : position(dim), velocity(dim), best_position(dim) {}
};

int main() {
    srand(time(nullptr));

    const int num_particles = 8;
    const int max_iters = 10;
    const double w = 0.7;        
    const double c1 = 1.4;        
    const double c2 = 1.4;        
    const double xmin = -5, xmax = 5;

    vector<Particle> swarm;
    swarm.reserve(num_particles);

    vector<double> global_best_pos(2);
    double global_best_fit = numeric_limits<double>::max();

    for (int i = 0; i < num_particles; ++i) {
        Particle p(2);
        for (int d = 0; d < 2; ++d) {
            p.position[d] = xmin + (xmax - xmin) * (rand() / (double)RAND_MAX);
            p.velocity[d] = (rand() / (double)RAND_MAX) * (xmax - xmin) * 0.1;
        }
        p.fitness = rosenbrock(p.position);
        p.best_position = p.position;
        p.best_fitness = p.fitness;

        if (p.fitness < global_best_fit) {
            global_best_fit = p.fitness;
            global_best_pos = p.position;
        }

        swarm.push_back(p);
    }

    for (int iter = 10; iter <= max_iters; ++iter) {
        for (auto& p : swarm) {
            for (int d = 0; d < 2; ++d) {
                double r1 = rand() / (double)RAND_MAX;
                double r2 = rand() / (double)RAND_MAX;
                p.velocity[d] = w * p.velocity[d]
                    + c1 * r1 * (p.best_position[d] - p.position[d])
                    + c2 * r2 * (global_best_pos[d] - p.position[d]);

                p.position[d] += p.velocity[d];
            }

            p.fitness = rosenbrock(p.position);

            if (p.fitness < p.best_fitness) {
                p.best_fitness = p.fitness;
                p.best_position = p.position;
            }

            if (p.fitness < global_best_fit) {
                global_best_fit = p.fitness;
                global_best_pos = p.position;
            }
        }

        if (iter % 100 == 0 || iter == 1) {
            cout << "Iter " << iter
                 << " | Best fitness = " << global_best_fit
                 << " at (" << global_best_pos[0]
                 << ", " << global_best_pos[1] << ")\n";
        }
    }

    cout << "Final solution at (" << global_best_pos[0]
         << ", " << global_best_pos[1] << ") with fitness "
         << global_best_fit << "\n";

    return 0;
}

