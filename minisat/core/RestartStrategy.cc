//
// Created by Nenad Vasic on 27.08.17.
//

#include <math.h>

#include "minisat/core/RestartStrategy.h"
#include "minisat/core/Solver.h"

namespace Minisat {

    static double luby(double y, int x){

        // Find the finite subsequence that contains index 'x', and the
        // size of that subsequence:
        int size, seq;
        for (size = 1, seq = 0; size < x+1; seq++, size = 2*size+1);

        while (size-1 != x){
            size = (size-1)>>1;
            seq--;
            x = x % size;
        }

        return pow(y, seq);
    }

    RestartStrategy::RestartStrategy(Solver &solver, bool luby_restart, double restart_inc, int restart_first)
        :_solver(solver)
        ,luby_restart(luby_restart)
        ,restart_inc(restart_inc)
        ,restart_first(restart_first)
        ,curr_restarts(-1)
        ,conflictC(0) {
        _solver.addListener(this);
        updateNofConflicts();
    }

    RestartStrategy::~RestartStrategy() {
        _solver.removeListener(this);
    }

    bool RestartStrategy::ShouldRestart(){
        return nof_conflicts >= 0 && conflictC >= nof_conflicts;
    }

    void RestartStrategy::onConflict(const Clause *conflictClause){
        conflictC++;
    }

    void RestartStrategy::onRestart(){
        curr_restarts++;
        updateNofConflicts();
    }

    void RestartStrategy::updateNofConflicts(){
        double rest_base = luby_restart ? luby(restart_inc, curr_restarts) : pow(restart_inc, curr_restarts);
        nof_conflicts = rest_base * restart_first;
    }
}