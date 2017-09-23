//
// Created by Nenad on 9/23/2017.
//

#include "minisat/core/PolarityStrategyRandom.h"
#include "minisat/core/Solver.h"
#include "Random.h"

namespace Minisat {
    PolarityStrategyRandom::PolarityStrategyRandom(Solver &solver)
            : _solver(solver) {
        _solver.addListener(this);
    }

    PolarityStrategyRandom::~PolarityStrategyRandom() {
        _solver.removeListener(this);
    }

    bool PolarityStrategyRandom::GetPolarity(Var v){
        return Random::getInstance()->drand() < 0.5;
    }
}