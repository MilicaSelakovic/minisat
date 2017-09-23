//
// Created by Nenad on 9/23/2017.
//

#ifndef MINISAT_POLARITYSTRATEGYRANDOM_H
#define MINISAT_POLARITYSTRATEGYRANDOM_H

#include "minisat/core/PolarityStrategy.h"
#include "minisat/core/SolverTypes.h"


namespace Minisat {

    class Solver;

    class PolarityStrategyRandom : public PolarityStrategy{
    public:
        PolarityStrategyRandom(Solver& solver);
        ~PolarityStrategyRandom();

        bool GetPolarity(Var v);

    private:
        Solver& _solver;
    };
}
#endif //MINISAT_POLARITYSTRATEGYRANDOM_H
