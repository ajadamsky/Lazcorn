//
// Created by Xoncry on 26.11.2017.
//

#include "randomGen.h"
#include <iostream>

float randomGen::roidXpos(){
        float value;
        value = pos.operator()(mt);
        return value;
};