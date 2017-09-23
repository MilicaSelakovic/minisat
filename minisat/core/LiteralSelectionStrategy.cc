//
// Created by milica on 23.9.17..
//

#include "LiteralSelectionStrategy.h"

#include "minisat/core/Solver.h"

namespace Minisat {

    LiteralSelectionStrategy::LiteralSelectionStrategy(Solver &solver, double opt_random_var_freq,
                                                       double opt_random_seed, bool opt_rnd_init_act,
                                                       double opt_var_decay)
            : _solver(solver)
            , random_var_freq(opt_random_var_freq)
            , random_seed(opt_random_seed)
            , rnd_init_act(opt_rnd_init_act)
            , rnd_decisions(0)
            , var_decay(opt_var_decay)
            , var_inc(1)
            , dec_vars(0)
            , order_heap(VarOrderLt(activity))
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

    void LiteralSelectionStrategy::onAddNewVar(Var v, bool dvar) {
        activity.insert(v, rnd_init_act ? drand(random_seed) * 0.00001 : 0);
        decision.reserve(v);
        setDecisionVar(v, dvar);
    }

    void LiteralSelectionStrategy::onLearn(const Clause* clause) {
        var_inc *= (1 / var_decay);
    }

    void LiteralSelectionStrategy::onExplain(Var v) {
        if ( (activity[v] += var_inc) > 1e100 ) {
            // Rescale:
            for (int i = 0; i < _solver.nVars(); i++)
                activity[i] *= 1e-100;
            var_inc *= 1e-100; }

        // Update order_heap with respect to new activity:
        if (order_heap.inHeap(v))
            order_heap.decrease(v);
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

    void LiteralSelectionStrategy::rebuildHeap(){
        vec<Var> vs;
        for (Var v = 0; v < _solver.nVars(); v++)
            if (decision[v] && _solver.value(v) == l_Undef)
                vs.push(v);
        order_heap.build(vs);
    }

    void LiteralSelectionStrategy::setDecisionVar(Var v, bool b)
    {
        if      ( b && !decision[v]) dec_vars++;
        else if (!b &&  decision[v]) dec_vars--;

        decision[v] = b;
        insertVarOrder(v);
    }


    uint64_t  LiteralSelectionStrategy::decVars(){
        return dec_vars;
    }
    uint64_t  LiteralSelectionStrategy::rndDecisions(){
        return rnd_decisions;
    }

    void LiteralSelectionStrategy::insertVarOrder(Var x) {
        if (!order_heap.inHeap(x) && decision[x]) order_heap.insert(x);
    }

}