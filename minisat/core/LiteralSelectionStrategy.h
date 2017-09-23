//
// Created by milica on 23.9.17..
//

#ifndef MINISAT_LITERALSELECTIONSTRATEGY_H
#define MINISAT_LITERALSELECTIONSTRATEGY_H


#include "minisat/core/SolverListener.h"
#include "minisat/mtl/Heap.h"
#include "minisat/mtl/IntMap.h"


namespace Minisat {

    class Solver;



    class LiteralSelectionStrategy: public SolverListener{
    public:
        LiteralSelectionStrategy(Solver& solver, double opt_random_var_freq,
                                 bool opt_rnd_init_act, double opt_var_decay);
        ~LiteralSelectionStrategy();

        Var nextLit();

        void onAddNewVar(Var v, bool dvar);
        void onLearn(const Clause* clause);

        void onExplain(Var v);

        void onBacktrack(Lit l, bool end_of_level);

        void rebuildHeap();

        uint64_t  decVars();
        uint64_t  rndDecisions();

        void insertVarOrder(Var x);


    protected:
        struct VarOrderLt {
            const VMap<double>&  activity;
            bool operator () (Var x, Var y) const { return activity[x] > activity[y]; }
            VarOrderLt(const VMap<double>&  act) : activity(act) { }
        };

    private:
        Solver&   _solver;
        double    random_var_freq;
        uint64_t rnd_decisions;
        uint64_t dec_vars;
        bool      rnd_init_act;
        VMap<double>        activity;
        Heap<Var,VarOrderLt>order_heap;
        VMap<char>          decision;

        double              var_inc;
        double    var_decay;

        void setDecisionVar(Var v, bool b);
    };

}


#endif //MINISAT_LITERALSELECTIONSTRATEGY_H
