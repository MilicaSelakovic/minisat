//
// Created by milica on 9.9.17..
//

#include "minisat/core/ForgetStrategy.h"

#include "minisat/core/Solver.h"

namespace Minisat {

    ForgetStrategy::ForgetStrategy(Solver &solver)
            : _solver(solver) {
        _solver.addListener(this);
    }

    ForgetStrategy::~ForgetStrategy() {
        _solver.removeListener(this);
    }
}