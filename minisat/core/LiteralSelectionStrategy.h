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

    struct VarOrderLt {
        const IntMap<Var, double>&  activity;
        bool operator () (Var x, Var y) const { return activity[x] > activity[y]; }
        VarOrderLt(const IntMap<Var, double>&  act) : activity(act) { }
    };

    class LiteralSelectionStrategy: public SolverListener{
    public:
        LiteralSelectionStrategy(Solver& solver, double opt_random_var_freq, double opt_random_seed, bool opt_rnd_init_act);
        ~LiteralSelectionStrategy();

        Var nextLit();

        void onAddNewVar(Var v){

        }

    private:
        Solver&   _solver;
        double    random_var_freq; // i ovo ide iz solvera
        double    random_seed;
        uint64_t rnd_decisions; //ide iz solvera pokazuje samo koliko puta je na random izabrao
        bool      rnd_init_act;       // Initialize variable activities with a small random value. ide van solvera
        VMap<double>        activity;      // A heuristic measurement of the activity of a variable.
        Heap<Var,VarOrderLt>order_heap;  // i ovo ide iz solvera
        VMap<char>          decision;         // Declares if a variable is eligible for selection in the decision heuristic. i ovo

        double drand(double& seed);
        int irand(double& seed, int size);
    };

}


#endif //MINISAT_LITERALSELECTIONSTRATEGY_H
