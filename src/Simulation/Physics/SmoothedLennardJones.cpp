#include "SmoothedLennardJones.h"
#include "MixingRuleLennardJones.h"
#include "../../utils/VectorDouble3.h"
#include <cmath>


VectorDouble3 SmoothedLennardJones::CalculateForces(const Particle &p1, const Particle &p2) {
        VectorDouble3 result{std::array <double,3>{0, 0, 0}};


        VectorDouble3 distance = p1.getXVector() - p2.getXVector();
        double distanceL2Norm = distance.getL2Norm();

        if (distanceL2Norm <= r_l) {
            return mixingRuleLennardJones.CalculateForces(p1, p2);
        }

        if (distanceL2Norm >= r_l && distanceL2Norm <= r_c){
            double sigma = (p1.getSigma() + p2.getSigma()) / 2;
            double eps = sqrt(p1.getEpsilon() * p2.getEpsilon());

            //Cache Repeated Computations
            double r_c_squared = r_c * r_c;
            double sigma_term = sigma / distanceL2Norm;
            double sigma_term_pow2 = sigma_term * sigma_term;
            double sigma_term_pow_6 = sigma_term_pow2 * sigma_term_pow2 * sigma_term_pow2;
            double sigma_term_pow_12 = sigma_term_pow_6 * sigma_term_pow_6;
            double distanceL2Norm_pow2 = distanceL2Norm * distanceL2Norm;
            double distanceL2Norm_pow6 = distanceL2Norm_pow2 * distanceL2Norm_pow2 * distanceL2Norm_pow2;
            double distanceL2Norm_pow7 = distanceL2Norm_pow6* distanceL2Norm;
            double distanceL2Norm_pow14 = distanceL2Norm_pow7 * distanceL2Norm_pow7;

            result = (-24 * sigma_term_pow_6 * eps) / (distanceL2Norm_pow14 * pow((r_c - r_l),3)) * (r_c - distanceL2Norm)
                    * (r_c_squared*(2*sigma_term_pow_6 - distanceL2Norm_pow6) + r_c * (3 * r_l - distanceL2Norm)*(distanceL2Norm_pow6 - 2 * sigma_term_pow_6) + 
                    distanceL2Norm * (5*r_l *sigma_term_pow_6 - 2* r_l*distanceL2Norm_pow6 - 3 * sigma_term_pow_6 * distanceL2Norm + distanceL2Norm_pow7))
                    * distance;

            return result;
        }

        else {
            return result;
        }


};