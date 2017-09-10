//
// Created by milica on 9.9.17..
//

#include "minisat/core/ForgetStrategy.h"

#include "minisat/core/Solver.h"

namespace Minisat {

    ForgetStrategy::ForgetStrategy(Solver &solver, int opt_min_learnts_lim)
            : _solver(solver)
            , min_learnts_lim(opt_min_learnts_lim)
            , learntsize_factor((double)1/(double)3)
            , learntsize_inc(1.1)
            , learntsize_adjust_start_confl (100)
            , learntsize_adjust_inc         (1.5)
            , write (false)
    {
        _solver.addListener(this);
    }

    ForgetStrategy::~ForgetStrategy() {
        _solver.removeListener(this);
    }

    void ForgetStrategy::onLearn(const Clause* clause) {
        if (--learntsize_adjust_cnt == 0) {
            learntsize_adjust_confl *= learntsize_adjust_inc;
            learntsize_adjust_cnt = (int) learntsize_adjust_confl;
            max_learnts *= learntsize_inc;
            write = true;
        } else{
            write = false;
        }
    }

    bool ForgetStrategy::shouldForget(int learnt){
        return learnt >= max_learnts;
    }

    void ForgetStrategy::init(int num_clauses) {
        max_learnts = num_clauses * learntsize_factor;
        if (max_learnts < min_learnts_lim)
            max_learnts = min_learnts_lim;

        learntsize_adjust_confl   = learntsize_adjust_start_confl;
        learntsize_adjust_cnt     = (int)learntsize_adjust_confl;

    }

    bool ForgetStrategy::shouldWrite() {
        return write;
    }

    double ForgetStrategy::getMax_learnts() const {
        return max_learnts;
    }
}