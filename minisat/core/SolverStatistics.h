//
// Created by Nenad on 6/11/2017.
//

#ifndef MINISAT_SOLVERSTATISTICS_H
#define MINISAT_SOLVERSTATISTICS_H

#include "minisat/core/SolverListener.h"

namespace Minisat {

class Solver;

class SolverStatistics : public SolverListener{
public:
    SolverStatistics(Solver& solver);
    ~SolverStatistics();

    virtual void onDecide(Lit l) {
        _numberOfDecisions++;
    }

    virtual void onConflict(const Clause* conflictClause) {
        _numberOfConflicts++;
    }

    virtual void onRestart() {
        _numberOfRestarts++;
//        printStatistics();
    }

    virtual void onPropagate(Lit l, const Clause* clause) {
        _numberOfPropagations++;
    }

    int getNumberOfDecisions() const {
        return _numberOfDecisions;
    }

    int getNumberOfConflicts() const {
        return _numberOfConflicts;
    }

    int getNumberOfPropagations() const {
        return _numberOfPropagations;
    }

    int getNumberOfRestarts() const {
        return _numberOfRestarts;
    }
private:
    Solver& _solver;
    int _numberOfDecisions;
    int _numberOfConflicts;
    int _numberOfPropagations;
    int _numberOfRestarts;
};

}

#endif //MINISAT_SOLVERSTATISTICS_H
