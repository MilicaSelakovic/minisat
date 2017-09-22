//
// Created by Nenad on 9/23/2017.
//

#include "minisat/core/PolarityStrategyFull.h"
#include "minisat/core/Solver.h"
namespace Minisat {
    PolarityStrategyFull::PolarityStrategyFull(Solver &solver)
            : _solver(solver) {
        _solver.addListener(this);
    }

    PolarityStrategyFull::~PolarityStrategyFull() {
        _solver.removeListener(this);
    }

    bool PolarityStrategyFull::GetPolarity(Var v){
        if(polarity.has(v)){
            return polarity[v];
        }
        return true;
    }

    void PolarityStrategyFull::onBacktrack (Lit l, bool end_of_level){
        if(polarity.has(var(l))) {
            polarity[var(l)] = sign(l);
        } else {
            polarity.insert(var(l), sign(l));
        }
    }
}