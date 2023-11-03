#define BOOST_TEST_MODULE SimulationTests
#include <boost/test/included/unit_test.hpp>

#include "../src/Simulation.h"

static std::list<Particle> onePar;
static std::list<Particle> twoPar;
static std::list<Particle> threePar;

struct GlobalFixture {
    GlobalFixture() {
        // Initialization of onePar
        std::array<double, 3> x1_1 = {0.0, 0.0, 0.0};
        std::array<double, 3> v1_1 = {0.0, 1.0, 0.0};

        onePar.emplace_back(x1_1, v1_1, 1);

        // Initialization of twoPar
        std::array<double, 3> x2_1 = {0.0, 0.0, 0.0};
        std::array<double, 3> v2_1 = {0.0, 1.0, 0.0};

        std::array<double, 3> x2_2 = {1.0, 0.0, 0.0};
        std::array<double, 3> v2_2 = {1.0, 0.0, 0.0};

        twoPar.emplace_back(x2_1, v2_1, 1);
        twoPar.emplace_back(x2_2, v2_2, 1);

        // Initialization of threePar
        std::array<double, 3> x3_1 = {0.0, 0.0, 0.0};
        std::array<double, 3> v3_1 = {0.0, 1.0, 0.0};

        std::array<double, 3> x3_2 = {1.0, 0.0, 0.0};
        std::array<double, 3> v3_2 = {1.0, 0.0, 0.0};

        std::array<double, 3> x3_3 = {0.0, 1.0, 0.0};
        std::array<double, 3> v3_3 = {0.0, 1.0, 0.0};

        threePar.emplace_back(x3_1, v3_1, 1);
        threePar.emplace_back(x3_2, v3_2, 1);
        threePar.emplace_back(x3_2, v3_2, 1);
    }

    ~GlobalFixture() {
        onePar.clear();
        twoPar.clear();
        threePar.clear();
    }
};


BOOST_GLOBAL_FIXTURE(GlobalFixture);

BOOST_AUTO_TEST_CASE(TestCalculateX_1par)
{
    std::array<double, 3> expectedPos = {0.0, 1.0, 0.0};

    Simulation sim = Simulation(1.0, onePar);
    sim.calculateX();

    std::list<Particle>& particles = sim.getParticles();

    auto it = particles.begin();
    Particle element = *it;

    BOOST_CHECK(element.getX() == expectedPos);
}

BOOST_AUTO_TEST_CASE(TestCalculateX_2par)
{
    std::array<double, 3> expectedX = {0.0, 1.0, 0.0};

    Simulation sim = Simulation(1.0, onePar);
    sim.calculateV();

    std::list<Particle>& particles = sim.getParticles();

    auto it = particles.begin();
    Particle element = *it;

    BOOST_CHECK(element.getV() == expectedVelo);
}

BOOST_AUTO_TEST_CASE(TestCalculateX_3par)
{

}

BOOST_AUTO_TEST_CASE(TestCalculateV_1par)
{
    std::array<double, 3> expectedVelo = {0.0, 1.0, 0.0};

    Simulation sim = Simulation(1.0, onePar);
    sim.calculateV();

    std::list<Particle>& particles = sim.getParticles();

    auto it = particles.begin();
    Particle element = *it;

    BOOST_CHECK(element.getV() == expectedVelo);
}

BOOST_AUTO_TEST_CASE(TestCalculateV_2par)
{

}

BOOST_AUTO_TEST_CASE(TestCalculateV_3par)
{

}

BOOST_AUTO_TEST_CASE(TestCalculateF_1par)
{
    std::array<double, 3> expectedForce = {0.0, 0.0, 0.0};

    Simulation sim = Simulation(1.0, onePar);
    sim.calculateV();

    std::list<Particle>& particles = sim.getParticles();

    auto it = particles.begin();
    Particle element = *it;

    BOOST_CHECK(element.getF() == expectedForce);
}

BOOST_AUTO_TEST_CASE(TestCalculateF_2par)
{

}

BOOST_AUTO_TEST_CASE(TestCalculateF_3par)
{

}
