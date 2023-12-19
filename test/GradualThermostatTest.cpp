//
// Created by klara on 10.12.23.
//

#include "GradualThermostatTest.h"

void GradualThermostatTest::SetUp() {
    std::vector<Particle> particles1{p1, p2, p3, p4};
    containerWarming.addParticles(particles1);

    std::vector<Particle> particles2{p5, p6, p7, p8};
    containerCooling.addParticles(particles2);
}

TEST_F(GradualThermostatTest, warming){
    std::vector<double> correctTemperatures{2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4};
    for(auto correctTemp : correctTemperatures){
        thermostatWarming.updateState(containerWarming.getParticleVector());
        containerWarming.applyToAll([this](Particle& p){thermostatWarming.updateTemperature(p);});
        thermostatWarming.updateStateTest(containerWarming.getParticleVector());
        EXPECT_DOUBLE_EQ(correctTemp, thermostatWarming.getCurrentTemperature());
        thermostatWarming.updateIteration();
    }
}

TEST_F(GradualThermostatTest, cooling){
    std::vector<double> correctTemperatures{3, 3, 3, 2, 2, 2, 1, 1, 1};
    for(auto correctTemp : correctTemperatures){
        thermostatCooling.updateState(containerCooling.getParticleVector());
        containerCooling.applyToAll([this](Particle& p){thermostatCooling.updateTemperature(p);});
        thermostatCooling.updateStateTest(containerCooling.getParticleVector());
        EXPECT_DOUBLE_EQ(correctTemp, thermostatCooling.getCurrentTemperature());
        thermostatCooling.updateIteration();
    }
}
