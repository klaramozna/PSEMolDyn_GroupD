/* File IO */
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

/* Standard IO */
#include <iostream>

/* Boost */
#include <boost/program_options.hpp>
#include <filesystem>

/* Simulation Logic */
#include "Simulation.h"
#include "ParticleContainer.h"
#include "GravitationalForce.h"



constexpr double start_time = 0;
double end_time;
double delta_t;

namespace po = boost::program_options;

 /**
     * @brief checks if a double value is positive or not (used to handle incorrect user input)
     * @param value the value to check
     * @param option_name specify which option
*/
void validate_positive(const double& value, const std::string& option_name) {
    if (value <= 0) {
        throw po::validation_error(po::validation_error::invalid_option_value,
            option_name);
    }
}

int main(int argc, char *argsv[]) {
    std::cout << "Hello from MolSim for PSE!" << std::endl;

    //declaring the supported options
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("input_path,p", po::value<std::string>(), "the path to the input file")
            ("t_end,e", po::value<double>(&end_time)->default_value(1000)->notifier(std::bind(&validate_positive, std::placeholders::_1, "t_end")), "end time of simulation")
            ("delta_t,s", po::value<double>(&delta_t)->default_value(0.014)->notifier(std::bind(&validate_positive, std::placeholders::_1, "t_end")), "step size between interations");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argsv, desc), vm);
        po::notify(vm);
    }
        //deal with any erroneous program(incorrect user input)
    catch (po::error &e) {
        std::cout << "Erroneous program call! " << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    std::string input_path;
    if (vm.count("input_path") && std::filesystem::exists(vm["input_path"].as<std::string>())) {
        input_path = vm["input_path"].as<std::string>();
        std::cout << "Input path: " << input_path << std::endl;
    } else {
        std::cout << "Input file not specified or invalid." << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

    FileReader fileReader;

    GravitationalForce gravForce;
    ParticleContainer container;

    outputWriter::VTKWriter writer;

    Simulation simulation(delta_t, container, gravForce);

    fileReader.readFile(simulation.getParticles(), input_path);

    int iteration = 0;
    double current_time = start_time;
    std::string out_name("MD_vtk");

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {
        simulation.runIteration();

        iteration++;
        if (iteration % 10 == 0) {
            writer.plotParticles(simulation.getParticles(), out_name, iteration);
        }

        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return 0;
}
