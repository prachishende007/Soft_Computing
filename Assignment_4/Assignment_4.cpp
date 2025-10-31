#include <bits/stdc++.h>
using namespace std;

double triangular(double x, double a, double b, double c) {
    if (x <= a || x >= c) return 0.0;
    else if (x == b) return 1.0;
    else if (x < b) return (x - a) / (b - a);
    else return (c - x) / (c - b);
}

double trapz(double x, double a, double b, double c, double d) {
    if (x <= a || x >= d) return 0.0;
    else if (x >= b && x <= c) return 1.0;
    else if (x > a && x < b) return (x - a) / (b - a);
    else return (d - x) / (d - c);
}

double gaussian(double x, double c, double sigma) {
    return exp(-pow(x - c, 2) / (2 * pow(sigma, 2)));
}

int main() {
    vector<double> data = {2.3, 3.1, 4.7, 5.5, 6.2, 7.0, 8.1};

    double xmin = *min_element(data.begin(), data.end());
    double xmax = *max_element(data.begin(), data.end());
    double mean = accumulate(data.begin(), data.end(), 0.0) / data.size();

    double variance = 0.0;
    for (double v : data) variance += (v - mean) * (v - mean);
    variance /= data.size();
    double stddev = sqrt(variance);

    cout << "Min: " << xmin << "  Max: " << xmax
         << "  Mean: " << mean << "  StdDeviation: " << stddev << "\n\n";

    cout << "x\tTriangular\tTrapezoidal\tGaussian\n";
    for (double x = xmin - 1; x <= xmax + 1; x += 0.5) {
        double tri = triangular(x, xmin, mean, xmax);
        double trap = trapz(x, xmin, (xmin+mean)/2, (mean+xmax)/2, xmax);
        double gauss = gaussian(x, mean, stddev);

        cout << fixed << setprecision(2)
             << x << "\t" << tri << "\t\t" << trap << "\t\t" << gauss << "\n";
    }

    return 0;
}
