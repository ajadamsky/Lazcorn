//
// Created by Xoncry on 26.11.2017.
//

#ifndef LAZCORN_RANDOMGEN_H
#define LAZCORN_RANDOMGEN_H

#include <random>


class randomGen {
public:
    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<float> pos{20, 1180};
    std::uniform_real_distribution<float> asteroidSpacer{10, 150};

    float roidXpos();
};


#endif //LAZCORN_RANDOMGEN_H
