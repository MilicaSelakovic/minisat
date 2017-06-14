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

    virtual void init            ()                               {}
    virtual void onDecide        (Lit l)                          {} // 780 //
    virtual void onAssert        (Lit l)                          {}
    virtual void onPropagate     (Lit l, const Clause* clause)    {} // 515 //
    virtual void onBacktrack     (Lit l)                          {}
    virtual void onConflict      (const Clause* conflictClause)   {} // 714 //
    virtual void onExplain       (Lit l, const Clause* clause)    {}
    virtual void onLearn         (const Clause* clause)           {}
    virtual void onForget        ()                               {}
    virtual void onForgetClause  (const Clause* clause)           {}
    virtual void onRestart       ()                               {} // 708 //
};

}

#endif
