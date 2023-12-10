//
// Created by RayenManai on 10.12.23.
//

#include "Benchmark.h"
#include "IO/Logger.h"

void Benchmark::startBenchmark() {
    Logger::init(6);
    startTime = std::chrono::high_resolution_clock::now();
}

void Benchmark::stopBenchmark() {
    endTime = std::chrono::high_resolution_clock::now();
    Logger::init(2);
}

 double Benchmark::getElapsedTimeInSeconds() const {
    std::chrono::duration<double> elapsedTime = endTime - startTime;
    return elapsedTime.count();
}   

int Benchmark::getMoleculeUpdatesPerSecond(double elapsed_time, int iterations, int number_of_molecules) const {
    double updates_per_second = static_cast<double>(number_of_molecules * iterations) / elapsed_time;
    return updates_per_second;
}

void Benchmark::printBenchmarkResults(double elapsed_time, int iterations, int number_of_molecules) {
    Logger::console->info("Time taken: {} milliseconds",  elapsed_time);
    double mups = getMoleculeUpdatesPerSecond(elapsed_time, iterations,number_of_molecules);
    double mmups = mups/ (1000000);
    Logger::console->info("MUPS = {}",  mups);
    Logger::console->info("MMUPS = {}",  mmups);
}