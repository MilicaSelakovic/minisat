//
// Created by milica on 9.9.17..
//

#ifndef MINISAT_FORGETSTRATEGY_H
#define MINISAT_FORGETSTRATEGY_H


#include "minisat/core/SolverListener.h"


namespace Minisat {

    class Solver;

    class ForgetStrategy : public SolverListener{
    public:
        ForgetStrategy(Solver& solver);
        ~ForgetStrategy();

        virtual void onLearn(const Clause* clause);

        bool shouldForget(int learnt);

        void init(int num_clauses);

    private:
        Solver& _solver;
        int       min_learnts_lim;    // Minimum number to set the learnts limit to.

        double    learntsize_factor;  // The intitial limit for learnt clauses is a factor of the original clauses.                (default 1 / 3)
        double    learntsize_inc;     // The limit for learnt clauses is multiplied with this factor each restart.                 (default 1.1)

        int       learntsize_adjust_start_confl;
        double    learntsize_adjust_inc;

        // states
        double              max_learnts;
        double              learntsize_adjust_confl;
        int                 learntsize_adjust_cnt;

    };

}



#endif //MINISAT_FORGETSTRATEGY_H
