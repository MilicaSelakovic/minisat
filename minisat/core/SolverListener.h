//
// Created by Nenad on 6/11/2017.
//

#ifndef Minisat_SolverListener_h
#define Minisat_SolverListener_h

#include "minisat/core/SolverTypes.h"

namespace Minisat {


class SolverListener {
public:
    virtual ~SolverListener() {}

    virtual void init            ()                               {} // Not sure if the start of the solve method is late for calling init so its not called anywhere for now
    virtual void onDecide        (Lit l)                          {}
    virtual void onAssert        (Lit l)                          {}
    virtual void onPropagate     (Lit l, const Clause* clause)    {}
    virtual void onBacktrack     (Lit l, bool end_of_level)       {}
    virtual void onConflict      (const Clause* conflictClause)   {}
    virtual void onExplain       (Lit l, const Clause* clause)    {} // Event never fires
    virtual void onLearn         (const Clause* clause)           {} // Event never fires
    virtual void onForget        ()                               {} // Event never fires
    virtual void onForgetClause  (const Clause* clause)           {} // Event never fires
    virtual void onRestart       ()                               {}
    virtual void onAddNewVar     (Var v)                          {}
};

}

#endif
