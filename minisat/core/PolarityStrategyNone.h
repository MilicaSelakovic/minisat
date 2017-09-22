//
// Created by Nenad on 9/23/2017.
//

#ifndef MINISAT_POLARITYSTRATEGYNONE_H
#define MINISAT_POLARITYSTRATEGYNONE_H

#include "minisat/core/PolarityStrategy.h"
#include "minisat/core/SolverTypes.h"


namespace Minisat {

    class Solver;

    class PolarityStrategyNone : public PolarityStrategy{
    public:
        PolarityStrategyNone(Solver& solver);
        ~PolarityStrategyNone();

        bool GetPolarity(Var v);

    private:
        Solver& _solver;
    };

}
#endif //MINISAT_POLARITYSTRATEGYNONE_H
