/* File IO */
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

/* Standard IO */
#include <iostream>

/* Boost */
#include <boost/program_options.hpp>

/* Simulation Logic */
#include "Simulation.h"
#include "ParticleContainer.h"
#include "GravitationalForce.h"


void plotParticles(int iteration, Simulation simulation);

constexpr double start_time = 0;
double end_time;
double delta_t;

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
        std::cout << "Erroneous program call! " << std::endl;
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

    GravitationalForce gravForce;
    ParticleContainer container;

    Simulation simulation(delta_t, container, &gravForce);

    fileReader.readFile(simulation.getParticles(), input_path);

    int iteration = 0;
    double current_time = start_time;

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {
        simulation.runIteration();

        iteration++;
        if (iteration % 10 == 0) {
            plotParticles(iteration, simulation);
        }

        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return 0;
}

void plotParticles(int iteration, Simulation simulation) {

    std::string out_name("MD_vtk");

    //outputWriter::XYZWriter writer;
    //writer.plotParticles(particles, out_name, iteration);
    
    outputWriter::VTKWriter writer;
    writer.initializeOutput(simulation.getParticles().size());
    for (auto &p: simulation.getParticles()) {
           writer.plotParticle(p);
        }
    writer.writeFile(out_name, iteration);
}