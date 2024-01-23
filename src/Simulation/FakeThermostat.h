//
// Created by klara on 17.12.23.
//

#ifndef PSEMOLDYN_GROUPD_FAKETHERMOSTAT_H
#define PSEMOLDYN_GROUPD_FAKETHERMOSTAT_H

#include "Thermostat.h"

class FakeThermostat : public Thermostat {

    /**
     * @brief Does not do anything. This function serves as a dummy thermostat when none is supposed to be used. Same for all of the other functions in this class.
     * @param particle
     */
    void updateTemperature(Particle& particle) override{};

    void updateState(const std::vector<Particle>& particles){};

    void updateIteration(){};

    void initializeBrownianMotion(Particle& particle) const{};

    double getCurrentTemperature() = delete;



};


#endif //PSEMOLDYN_GROUPD_FAKETHERMOSTAT_H
