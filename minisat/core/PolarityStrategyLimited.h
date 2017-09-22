//
// Created by Nenad on 9/23/2017.
//

#ifndef MINISAT_POLARITYSTRATEGYLIMITED_H
#define MINISAT_POLARITYSTRATEGYLIMITED_H

#include "minisat/core/PolarityStrategy.h"
#include "minisat/core/SolverTypes.h"


namespace Minisat {

class Solver;

class PolarityStrategyLimited : public PolarityStrategy{
public:
    PolarityStrategyLimited(Solver& solver);
    ~PolarityStrategyLimited();

    bool GetPolarity(Var v);

    virtual void onBacktrack (Lit l, bool end_of_level);
    virtual void onPropagate (Lit l, const Clause* clause);
    virtual void onDecide    (Lit l);
private:
    Solver& _solver;
    VMap<char> polarity;
    bool should_save;
};

}
#endif //MINISAT_POLARITYSTRATEGYLIMITED_H
