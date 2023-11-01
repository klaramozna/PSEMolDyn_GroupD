
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>
#include "VectorDouble.h"
#include <cmath>

#include <boost/program_options.hpp>

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
double end_time;
double delta_t;

// TODO: what data structure to pick?
std::list<Particle> particles;

namespace po = boost::program_options;

int main(int argc, char *argsv[]) {
    std::cout << "Hello from MolSim for PSE!" << std::endl;

    //declaring the supported options
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("input_path,p", po::value<std::string>(), "the path to the input file")
        ("t_end,e", po::value<double>(&end_time)->default_value(1000),"end time of simulation")
        ("delta_t,s", po::value<double>(&delta_t)->default_value(0.014),"step size between interations");

    po::variables_map vm;
    try{
        po::store(po::parse_command_line(argc, argsv, desc), vm);
        po::notify(vm);
    }
    //deal with any erroneous program(incorrect user input)
    catch(po::error& e) {
        std::cout << "Erroneous programm call! " << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("help")){
        std::cout << desc << std::endl;
        return 0;
    }
    std::string input_path;
    if (vm.count("input_path")){
        input_path = vm["input_path"].as<std::string>();
        std::cout << "Input path: " << input_path << std::endl;
    }
    else {
        std::cout << "Input file not specified." << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

  FileReader fileReader;
  fileReader.readFile(particles, input_path);

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

    //outputWriter::XYZWriter writer;
    //writer.plotParticles(particles, out_name, iteration);
    
    outputWriter::VTKWriter writer;
    writer.initializeOutput(particles.size());
    for (auto &p: particles) {
           writer.plotParticle(p);
        }
    writer.writeFile(out_name, iteration);
}
