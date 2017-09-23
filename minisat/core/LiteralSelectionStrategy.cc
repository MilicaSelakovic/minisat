//
// Created by milica on 23.9.17..
//

#include "LiteralSelectionStrategy.h"

#include "minisat/core/Solver.h"

namespace Minisat {

    LiteralSelectionStrategy::LiteralSelectionStrategy(Solver &solver, double opt_random_var_freq,
                                                       double opt_random_seed, bool opt_rnd_init_act)
            : _solver(solver)
            , random_var_freq(opt_random_var_freq)
            , random_seed(opt_random_seed)
            , rnd_init_act(opt_rnd_init_act)
            , rnd_decisions(0)
            , order_heap         (VarOrderLt(activity))
    {
        _solver.addListener(this);
    }

    LiteralSelectionStrategy::~LiteralSelectionStrategy() {
        _solver.removeListener(this);
    }

    Var LiteralSelectionStrategy::nextLit() {
        Var next = var_Undef;

        // Random decision:
        if (drand(random_seed) < random_var_freq && !order_heap.empty()){
            next = order_heap[irand(random_seed,order_heap.size())];
            if (_solver.value(next) == l_Undef && decision[next])
                rnd_decisions++; }

        // Activity based decision:
        while (next == var_Undef || _solver.value(next) != l_Undef || !decision[next])
            if (order_heap.empty()){
                next = var_Undef;
                break;
            }else
                next = order_heap.removeMin();

        return next;
    }

    void LiteralSelectionStrategy::onAddNewVar(Var v) {
        activity.insert(v, rnd_init_act ? drand(random_seed) * 0.00001 : 0);
    }

    double LiteralSelectionStrategy::drand(double& seed) {
        seed *= 1389796;
        int q = (int)(seed / 2147483647);
        seed -= (double)q * 2147483647;
        return seed / 2147483647;
    }

    int LiteralSelectionStrategy::irand(double& seed, int size) {
        return (int)(drand(seed) * size);
    }


}