//
// Created by milica on 9.9.17..
//

#include "minisat/core/ForgetStrategy.h"

#include "minisat/core/Solver.h"

namespace Minisat {

    ForgetStrategy::ForgetStrategy(Solver &solver)
            : _solver(solver)
            , learntsize_factor((double)1/(double)3)
            , learntsize_inc(1.1)
            , learntsize_adjust_start_confl (100)
            , learntsize_adjust_inc         (1.5)
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
}