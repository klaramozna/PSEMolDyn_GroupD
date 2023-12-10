//
// Created by klara on 10.12.23.
//

#include "SimpleThermostatTest.h"
#include <gtest/gtest.h>

void SimpleThermostatTest::SetUp() {
    std::vector<Particle> particles{p1, p2, p3, p4};
    container.addParticles(particles);
}

TEST_F(SimpleThermostatTest, TemperatureCalculation){
    thermostat.updateState(container.getParticleVector());
    EXPECT_DOUBLE_EQ(thermostat.getCurrentTemperature(), 1);
}

TEST_F(SimpleThermostatTest, updateTemperature){
    std::vector<double> correctTemperatures{4, 1, 1, 4, 1, 1, 4, 1, 1};
    for(auto correctTemp : correctTemperatures){
        container.applyToAll([](Particle& p){p.setV(1, 1, 1);});
        thermostat.updateState(container.getParticleVector());
        container.applyToAll([this](Particle& p){thermostat.updateTemperature(p);});
        thermostat.updateState(container.getParticleVector());
        EXPECT_DOUBLE_EQ(correctTemp, thermostat.getCurrentTemperature());
        thermostat.updateIteration();
    }
}