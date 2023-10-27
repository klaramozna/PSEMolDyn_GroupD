
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>
#include "VectorDouble.h"
#include <cmath>

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

constexpr double start_time = 0;
constexpr double end_time = 1000;
constexpr double delta_t = 0.014;

// TODO: what data structure to pick?
std::list<Particle> particles;

int main(int argc, char *argsv[]) {

    std::cout << "Hello from MolSim for PSE!" << std::endl;
    if (argc != 2) {
        std::cout << "Erroneous programme call! " << std::endl;
        std::cout << "./molsym filename" << std::endl;
    }

    FileReader fileReader;
    fileReader.readFile(particles, argsv[1]);

    double current_time = start_time;

    int iteration = 0;

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {
        // calculate new x
        calculateX();
        // calculate new f
        calculateF();
        // calculate new v
        calculateV();

        iteration++;
        if (iteration % 10 == 0) {
            plotParticles(iteration);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return 0;
}

void calculateF() {
    std::list<Particle>::iterator iterator;
    iterator = particles.begin();

    for (auto &p1: particles) {
        p1.setOldF(p1.getFVector());
        VectorDouble f_i(3);
        for (auto &p2: particles) {
            if(!(p2 == p1)){
                f_i += ((p1.getM() * p2.getM()) / pow((p1.getXVector() - p2.getXVector()).getL2Norm(), 3)) * (p2.getXVector() - p1.getXVector());
            }
        }
        p1.setF(f_i);
    }
}

void calculateX() {
    for (auto &p: particles) {
        VectorDouble x_i = p.getXVector() + delta_t * p.getVVector()
                + ((delta_t * delta_t) / (2. * p.getM())) * p.getOldFVector();
        p.setX(x_i);
    }
}

void calculateV() {
    for (auto &p: particles) {
        VectorDouble v_i = p.getVVector() + (delta_t / (2. * p.getM()) * (p.getOldFVector() + p.getFVector()));
        p.setV(v_i);
    }
}

void plotParticles(int iteration) {

    std::string out_name("MD_vtk");

    outputWriter::XYZWriter writer;
    writer.plotParticles(particles, out_name, iteration);
}
