//
// Created by Nenad on 9/23/2017.
//

#include "minisat/core/PolarityStrategyLimited.h"
#include "minisat/core/Solver.h"
namespace Minisat {
    PolarityStrategyLimited::PolarityStrategyLimited(Solver &solver)
            : _solver(solver),
              should_save(false) {
        _solver.addListener(this);
    }

    PolarityStrategyLimited::~PolarityStrategyLimited() {
        _solver.removeListener(this);
    }

    bool PolarityStrategyLimited::GetPolarity(Var v){
        if(polarity.has(v)){
            return polarity[v];
        }
        return true;
    }

    void PolarityStrategyLimited::onPropagate(Lit, const Clause*){
        should_save = true;
    }
    void PolarityStrategyLimited::onDecide(Lit){
        should_save = true;
    }

    void PolarityStrategyLimited::onBacktrack (Lit l, bool end_of_level){
        if(end_of_level){
            should_save = false;
        }

        if (should_save){
            if(polarity.has(var(l))) {
                polarity[var(l)] = sign(l);
            } else {
                polarity.insert(var(l), sign(l));
            }
        }
    }
}