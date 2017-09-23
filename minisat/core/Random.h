//
// Created by milica on 23.9.17..
//

#ifndef MINISAT_RANDOM_H
#define MINISAT_RANDOM_H


class Random {
public:
    static Random* getInstance();

    double drand();
    int irand(int size);
    void setSeed(double seed);

private:
    Random() {};
    Random(const Random&) {};
    Random& operator=(Random const&){};
    static Random* _instance;
    double random_seed;
};


#endif //MINISAT_RANDOM_H
