//
// Created by Nenad Vasic on 27.08.17.
//

#ifndef MINISAT_RESTARTSTRATEGY_H
#define MINISAT_RESTARTSTRATEGY_H

#include "minisat/core/SolverListener.h"

class Solver;

namespace Minisat {


class RestartStrategy : public SolverListener{
public:
    RestartStrategy(Solver& solver, bool luby_restart, double restart_inc, int restart_first);

    bool ShouldRestart();

    virtual void onConflict(const Clause* conflictClause);
    virtual void onRestart();

private:
    Solver& _solver;
    bool luby_restart;
    double restart_inc;
    int restart_first;
};

}
#endif //MINISAT_RESTARTSTRATEGY_H
