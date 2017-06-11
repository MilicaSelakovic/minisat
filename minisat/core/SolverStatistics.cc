//
// Created by Nenad on 6/11/2017.
//

#include "minisat/core/SolverStatistics.h"
#include "minisat/core/Solver.h"

namespace Minisat{
    SolverStatistics::SolverStatistics(Solver& solver)
            : _solver(solver),
              _numberOfDecisions(0),
              _numberOfConflicts(0),
              _numberOfPropagations(0),
              _numberOfRestarts(0) {
        _solver.addListener(this);
    }

    SolverStatistics::~SolverStatistics() {
        _solver.removeListener(this);
    }
}