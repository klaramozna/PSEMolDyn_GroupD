//
// Created by RayenManai on 10.12.23.
//

#include <iostream>
#include <chrono>

class Benchmark {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

public:
    void startBenchmark();

    void stopBenchmark();

    double getElapsedTimeInSeconds() const;

    int getMoleculeUpdatesPerSecond(double elapsed_time, int iterations, int number_of_molecules) const;

    void printBenchmarkResults(double elapsed_time, int iterations, int number_of_molecules);
};