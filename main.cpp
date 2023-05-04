#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    FILE *pipe = _popen(R"(C:\gnuplot\bin\gnuplot -persist)", "w");
    fprintf(pipe, "%s\n", "set terminal qt 0");
    fprintf(pipe, "%s\n", "plot '-' title 'victims' with lines, '-' title 'killers' with lines");

    double V0, K0, a1, b1, a2, b2;
    int t, n;
    cin >> V0 >> K0 >> a1 >> b1 >> a2 >> b2 >> t >> n;
    double v0 = V0 - a2 / b2;
    double k0 = K0 - a1 / b1;
    vector<double> times;
    vector<double> victims;
    vector<double> killers;
    times.push_back(0);
    victims.push_back(v0 + a2 / b2);
    killers.push_back(k0 + a1 / b1);
    for (double t_i = (double) t / (double) n; t_i <= t; t_i += (double) t / (double) n) {
        times.push_back(t_i);
        double temp =
                v0 * cos(sqrt(a1 * a2) * t_i) - k0 * ((sqrt(a2) * b1) / (b2 * sqrt(a1))) * sin(sqrt(a1 * a2) * t_i) +
                a2 / b2;
        victims.push_back(temp);
        double temp2 =
                v0 * ((sqrt(a1) * b2) / (b1 * sqrt(a2))) * sin(sqrt(a1 * a2) * t_i) + k0 * cos(sqrt(a1 * a2) * t_i) +
                a1 / b1;
        killers.push_back(temp2);
    }

    for (double t_i = 0.0; t_i <= t; t_i += double(t) / n) {
        fprintf(pipe, "%f\t%f\n", t_i, victims[t_i / 0.25]);
    }
    fprintf(pipe, "%s\n", "e");
    for (double t_i = 0.0; t_i <= t; t_i += double(t) / n) {
        fprintf(pipe, "%f\t%f\n", t_i, killers[t_i / 0.25]);
    }
    fprintf(pipe, "%s\n", "e");

    fprintf(pipe, "%s\n", "set terminal qt 1");
    fprintf(pipe, "%s\n", "plot '-' title 'relation' with lines");

    for (double t_i = 0.0; t_i <= t; t_i += double(t) / n) {
        fprintf(pipe, "%f\t%f\n", killers[t_i / 0.25], victims[t_i / 0.25]);
    }

    fflush(pipe);
    _pclose(pipe);
    return 0;
}
