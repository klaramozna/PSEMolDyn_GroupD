/*
 * VTKWriter.cpp
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#include "VTKWriter.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "./../../Logger.h"

namespace outputWriter {

    VTKWriter::VTKWriter() = default;
    VTKWriter::~VTKWriter() = default;

    namespace fs = std::filesystem;

    void VTKWriter::initializeOutput(int numParticles) {

        vtkFile = new VTKFile_t("UnstructuredGrid");

        // per point, we add type, position, velocity and force
        PointData pointData;
        DataArray_t mass(type::Float32, "mass", 1);
        DataArray_t velocity(type::Float32, "velocity", 3);
        DataArray_t forces(type::Float32, "force", 3);
        DataArray_t type(type::Int32, "type", 1);
        pointData.DataArray().push_back(mass);
        pointData.DataArray().push_back(velocity);
        pointData.DataArray().push_back(forces);
        pointData.DataArray().push_back(type);

        CellData cellData; // we don't have cell data => leave it empty

        // 3 coordinates
        Points points;
        DataArray_t pointCoordinates(type::Float32, "points", 3);
        points.DataArray().push_back(pointCoordinates);

        Cells cells; // we don't have cells, => leave it empty
        // for some reasons, we have to add a dummy entry for paraview
        DataArray_t cells_data(type::Float32, "types", 0);
        cells.DataArray().push_back(cells_data);

        PieceUnstructuredGrid_t piece(pointData, cellData, points, cells,
                                      numParticles, 0);
        UnstructuredGrid_t unstructuredGrid(piece);
        vtkFile->UnstructuredGrid(unstructuredGrid);
    }

    void VTKWriter::writeFile(const std::string &filename, int iteration) {
        std::stringstream strstr;
        strstr << filename << "_" << std::setfill('0') << std::setw(4) << iteration << ".vtu";

        std::string filename_str = strstr.str();
        fs::path fullPath = directory / filename_str;

        std::ofstream file(fullPath);
        VTKFile(file, *vtkFile);
        delete vtkFile;
    }

    void VTKWriter::plotParticle(Particle &p) {
        if (vtkFile->UnstructuredGrid().present()) {
           Logger::console->trace("UnstructuredGrid is present");
        } else {
            Logger::err_logger->error("ERROR: No UnstructuredGrid present");
        }

        PointData::DataArray_sequence &pointDataSequence =
                vtkFile->UnstructuredGrid()->Piece().PointData().DataArray();
        PointData::DataArray_iterator dataIterator = pointDataSequence.begin();

        dataIterator->push_back(p.getM());
        // cout << "Appended mass data in: " << dataIterator->Name();

        dataIterator++;
        dataIterator->push_back(p.getV()[0]);
        dataIterator->push_back(p.getV()[1]);
        dataIterator->push_back(p.getV()[2]);
        // cout << "Appended velocity data in: " << dataIterator->Name();

        dataIterator++;
        dataIterator->push_back(p.getOldF()[0]);
        dataIterator->push_back(p.getOldF()[1]);
        dataIterator->push_back(p.getOldF()[2]);
        // cout << "Appended force data in: " << dataIterator->Name();

        dataIterator++;
        dataIterator->push_back(p.getType());

        Points::DataArray_sequence &pointsSequence =
                vtkFile->UnstructuredGrid()->Piece().Points().DataArray();
        Points::DataArray_iterator pointsIterator = pointsSequence.begin();
        pointsIterator->push_back(p.getX()[0]);
        pointsIterator->push_back(p.getX()[1]);
        pointsIterator->push_back(p.getX()[2]);
    }

    void VTKWriter::plotParticles(const std::vector<Particle>& particles, const std::string &filename, int iteration) {
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            Logger::err_logger->error("Directory \"" + directory.string() + "\" wasn't created");
            exit(-1);
        }
        initializeOutput(particles.size());
        for (auto p: particles) {
            plotParticle(p);
        }

        writeFile(filename, iteration);
    }


    void VTKWriter::createMarkedDirectory() {
        // Get the current time
        std::time_t currentTime = std::time(nullptr);

        // Convert the current time to a struct tm
        std::tm* localTime = std::localtime(&currentTime);

        // Format the date and time
        std::ostringstream oss;
        oss << std::put_time(localTime, "%d.%m.%Y:%H:%M");

        std::string resultString = "Simulation_" + oss.str();

        directory = fs::path(resultString);

        try {
            // Use create_directory() to create the directory
            fs::create_directory(directory);
            Logger::console->info( "Directory created successfully: " + directory.string());
        } catch (const std::filesystem::filesystem_error& e) {
            Logger::err_logger->error("Error creating directory: " + std::string(e.what()));
            exit(-1);
        }
    }


} // namespace outputWriter
