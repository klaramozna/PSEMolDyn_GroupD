//
// Created by klara on 12.12.23.
//

#ifndef PSEMOLDYN_GROUPD_PARTICLETYPE_H
#define PSEMOLDYN_GROUPD_PARTICLETYPE_H


class ParticleType {
public:

    /**
     * @brief Creates a particleType object with the given parameters.
     * @param mass Mass of the particles of this type.
     * @param epsilon Epsilon for Lennard-Jones force calculation.
     * @param sigma Sigma for Lennard-Jones force calculation.
     */
    ParticleType(double mass, double epsilon, double sigma): mass{mass}, epsilon{epsilon}, sigma{sigma}{};

    /**
     * @brief Returns the mass of the type.
     * @return The mass of the type.
     */
    double getMass() const {return mass;}

    /**
     * @brief Returns the epsilon of the type.
     * @return The epsilon of the type.
     */
    double getEpsilon() const {return epsilon;}

    /**
     * @brief Returns the sigma of the type.
     * @return The sigma of the type.
     */
    double getSigma() const {return sigma;}

private:

    /**
     * @brief Mass of the particles of this type.
     */
    double mass;

    /**
     * @brief Epsilon for Lennard-Jones force calculation.
     */
    double epsilon;

    /**
     * @brief Sigma for Lennard-Jones force calculation.
     */
    double sigma;
};


#endif //PSEMOLDYN_GROUPD_PARTICLETYPE_H
