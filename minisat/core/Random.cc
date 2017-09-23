#include <stddef.h>
#include "Random.h"

Random* Random::_instance = NULL;

Random* Random::getInstance() {
    if(!_instance){
        _instance = new Random();
    }

    return _instance;
}


double Random::drand() {
    random_seed *= 1389796;
    int q = (int)(random_seed / 2147483647);
    random_seed -= (double)q * 2147483647;
    return random_seed / 2147483647;
}

int Random::irand(int size) {
    return (int)(drand() * size);
}


void Random::setSeed(double seed) {
    random_seed = seed;
}