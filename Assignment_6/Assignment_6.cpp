#include <bits/stdc++.h>
using namespace std;

const int NUM_CITIES = 4;
const int NUM_ANTS = 3;
const int MAX_ITERS = 10;

const double alpha = 1.0;
const double beta = 1.0;
const double rho = 0.5;
const double Q = 100.0;

double distMat[NUM_CITIES][NUM_CITIES] = {
    {0, 1, 4, 4},
    {1, 0, 8, 15},
    {4, 8, 0, 5},
    {4, 15, 5, 0}
};

double pheromone[NUM_CITIES][NUM_CITIES];

int selectNextCity(int currentCity, vector<int> &visited) {
    vector<double> prob(NUM_CITIES, 0.0);
    double sum = 0.0;

    for (int j = 0; j < NUM_CITIES; j++) {
        if (!visited[j]) {
            prob[j] = pow(pheromone[currentCity][j], alpha) * pow(1.0 / distMat[currentCity][j], beta);
            sum += prob[j];
        }
    }

    double r = ((double) rand() / RAND_MAX) * sum;
    double cumSum = 0.0;
    for (int j = 0; j < NUM_CITIES; j++) {
        if (!visited[j]) {
            cumSum += prob[j];
            if (r <= cumSum) return j;
        }
    }
    return -1;
}

void runACO(const string &filename) {
    srand(time(0));

    for (int i = 0; i < NUM_CITIES; i++)
        for (int j = 0; j < NUM_CITIES; j++)
            pheromone[i][j] = 1.0;

    double bestCost = DBL_MAX;
    vector<int> bestTour;
    ofstream fout(filename);

    for (int iter = 1; iter <= MAX_ITERS; iter++) {
        vector<vector<int>> antTours(NUM_ANTS);
        vector<double> antCosts(NUM_ANTS, 0.0);

        for (int k = 0; k < NUM_ANTS; k++) {
            vector<int> visited(NUM_CITIES, 0);
            int startCity = rand() % NUM_CITIES;
            int currentCity = startCity;
            visited[currentCity] = 1;
            antTours[k].push_back(currentCity);

            for (int step = 1; step < NUM_CITIES; step++) {
                int nextCity = selectNextCity(currentCity, visited);
                antTours[k].push_back(nextCity);
                antCosts[k] += distMat[currentCity][nextCity];
                visited[nextCity] = 1;
                currentCity = nextCity;
            }

            antCosts[k] += distMat[currentCity][startCity];
            antTours[k].push_back(startCity);

            if (antCosts[k] < bestCost) {
                bestCost = antCosts[k];
                bestTour = antTours[k];
            }

            // Save data in structured format
            fout << iter << "," << k+1 << ",";
            for (size_t c = 0; c < antTours[k].size(); c++) {
                fout << antTours[k][c];
                if (c != antTours[k].size()-1) fout << "-";
            }
            fout << "," << antCosts[k] << "," << bestCost << "\n";
        }

        // Evaporation
        for (int i = 0; i < NUM_CITIES; i++)
            for (int j = 0; j < NUM_CITIES; j++)
                pheromone[i][j] *= (1 - rho);

        // Deposit pheromone
        for (int k = 0; k < NUM_ANTS; k++) {
            double contribution = Q / antCosts[k];
            for (int i = 0; i < NUM_CITIES; i++) {
                int from = antTours[k][i];
                int to = antTours[k][i + 1];
                pheromone[from][to] += contribution;
                pheromone[to][from] += contribution;
            }
        }
    }

    fout.close();

    cout << "\nFinal Best Tour: ";
    for (int city : bestTour) cout << city << " ";
    cout << "| Cost = " << bestCost << "\n";
}

int main() {
    runACO("aco_ants_all_iters.txt");
    return 0;
}
