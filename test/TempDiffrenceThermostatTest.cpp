//
// Created by klara on 29.01.24.
//

#include "TempDiffrenceThermostatTest.h"

void TempDiffrenceThermostatTest::SetUp() {
    std::vector<Particle> particles{p1, p2, p3, p4};
    container.addParticles(particles);
}

TEST_F(TempDiffrenceThermostatTest, updateTemperature){
    std::vector<double> correctTemperatures{4, 4, 4};
    for(auto correctTemp : correctTemperatures){
        thermostat.updateState(container.getParticleVector());
        container.applyToAll([this](Particle& p){thermostat.updateTemperature(p);});
        thermostat.updateState(container.getParticleVector());
        EXPECT_DOUBLE_EQ(correctTemp, thermostat.getCurrentTemperature());
        thermostat.updateIteration();
    }
}