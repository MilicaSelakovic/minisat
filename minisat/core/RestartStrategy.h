//
// Created by Nenad Vasic on 27.08.17.
//

#ifndef MINISAT_RESTARTSTRATEGY_H
#define MINISAT_RESTARTSTRATEGY_H

#include "minisat/core/SolverListener.h"


namespace Minisat {

class Solver;

class RestartStrategy : public SolverListener{
public:
    RestartStrategy(Solver& solver, bool luby_restart, double restart_inc, int restart_first);
    ~RestartStrategy();

    bool ShouldRestart();

    virtual void onConflict (const Clause* conflictClause);
    virtual void onRestart  ();

private:
    Solver& _solver;
    bool luby_restart;
    double restart_inc;
    int restart_first;

    int curr_restarts;
    int conflictC;
    int nof_conflicts;

    void updateNofConflicts();
};

}
#endif //MINISAT_RESTARTSTRATEGY_H
