//
// Created by Nenad on 9/23/2017.
//

#ifndef MINISAT_POLARITYSTRATEGY_H
#define MINISAT_POLARITYSTRATEGY_H

#include "minisat/core/SolverListener.h"
#include "minisat/core/SolverTypes.h"


namespace Minisat {

    class Solver;

    class PolarityStrategy : public SolverListener{
    public:

        virtual bool GetPolarity(Var v) = 0;

    private:
    };

}
#endif //MINISAT_POLARITYSTRATEGY_H
