//
// Created by Nenad on 9/23/2017.
//

#include "minisat/core/PolarityStrategyNone.h"
#include "minisat/core/Solver.h"

namespace Minisat {
    PolarityStrategyNone::PolarityStrategyNone(Solver &solver)
            : _solver(solver) {
        _solver.addListener(this);
    }

    PolarityStrategyNone::~PolarityStrategyNone() {
        _solver.removeListener(this);
    }

    bool PolarityStrategyNone::GetPolarity(Var v){
        return true;
    }
}