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
        LiteralSelectionStrategy(Solver& solver, double opt_random_var_freq, double opt_random_seed,
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
        double    random_var_freq; // i ovo ide iz solvera
        double    random_seed;
        uint64_t rnd_decisions; //ide iz solvera pokazuje samo koliko puta je na random izabrao
        uint64_t dec_vars;
        bool      rnd_init_act;       // Initialize variable activities with a small random value. ide van solvera
        VMap<double>        activity;      // A heuristic measurement of the activity of a variable.
        Heap<Var,VarOrderLt>order_heap;  // i ovo ide iz solvera
        VMap<char>          decision;         // Declares if a variable is eligible for selection in the decision heuristic. i ovo

        double              var_inc;          // Amount to bump next variable with.
        double    var_decay;

        double drand(double& seed);
        int irand(double& seed, int size);

        void setDecisionVar(Var v, bool b);
    };

}


#endif //MINISAT_LITERALSELECTIONSTRATEGY_H
