//
// Created by Nenad on 9/23/2017.
//

#ifndef MINISAT_POLARITYSTRATEGYFULL_H
#define MINISAT_POLARITYSTRATEGYFULL_H

#include "minisat/core/PolarityStrategy.h"
#include "minisat/core/SolverTypes.h"


namespace Minisat {

    class Solver;

    class PolarityStrategyFull : public PolarityStrategy{
    public:
        PolarityStrategyFull(Solver& solver);
        ~PolarityStrategyFull();

        bool GetPolarity(Var v);

        virtual void onBacktrack (Lit l, bool end_of_level);
    private:
        Solver& _solver;
        VMap<char> polarity;
    };

}
#endif //MINISAT_POLARITYSTRATEGYFULL_H
