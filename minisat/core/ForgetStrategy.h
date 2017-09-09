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

    private:
        Solver& _solver;
    };

}



#endif //MINISAT_FORGETSTRATEGY_H
