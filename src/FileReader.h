/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "Particle.h"

#include <list>

class FileReader {

public:
    FileReader();

<<<<<<< HEAD
  void readFile(std::list<Particle> &particles, std::string &filename);
=======
    virtual ~FileReader();

    void readFile(std::list<Particle> &particles, char *filename);
>>>>>>> task1.2
};
