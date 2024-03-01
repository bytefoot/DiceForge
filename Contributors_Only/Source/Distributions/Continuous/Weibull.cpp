#include <cmath>
#include "Weibull.h"

namespace DiceForge{            
    Weibull::Weibull(real_t lambda, real_t k, real_t shift)
            : lambda(lambda), k(k), shift(shift){
        if (lambda < std::numeric_limits<real_t>().epsilon()){
            std::cerr << "Error :"
                        "\n\tDiceForge::Weibull::Weibull(real_t lambda = 1, real_t k = 1, real_t shift = 0) : "
                        "\n\t\tValue of lambda(scale factor) must be positive\n" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (k < std::numeric_limits<real_t>().epsilon()){
            std::cerr << "Error :"
                        "\n\tDiceForge::Weibull::Weibull(real_t lambda = 1, real_t k = 1, real_t shift = 0) : "
                        "\n\t\tValue of k(shape factor) must be positive\n" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    real_t Weibull::next(real_t r) {
        return lambda * std::pow(-std::log(1 - r), 1/k) + shift;
    }

    real_t Weibull::variance() const{
        return pow(lambda, 2) * (std::tgamma(1 + 2/k) - pow(std::tgamma(1 + 1/k), 2));
    }

    real_t Weibull::expectation() const {
        return lambda * std::tgamma(1 + 1/k);
    }

    real_t Weibull::minValue() const{
        return shift;
    }

    real_t Weibull::maxValue() const{
        return std::numeric_limits<real_t>().max();
    }

    real_t Weibull::pdf(real_t x) const {
        if(x < shift)
            return 0;
        x = (x - shift) / lambda;
        return (k/lambda) * std::pow(x, k-1) * exp( - std::pow(x, k));
    }

    real_t Weibull::cdf(real_t x) const{        
        if(x < shift)
            return 0;
        x = (x - shift) / lambda;
        return 1 - exp( - std::pow(x, k));
    }
} 