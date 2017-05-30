#include "gtest/gtest.h"
#include "minisat/core/Solver.h"
#include <fstream>
#include <zlib.h>
#include "minisat/core/Dimacs.h"

using namespace Minisat;


TEST(fix, test1) {
    Solver S;
    gzFile in = gzopen("../minisat/test/tests/unif-r4.25-v400-c1700-05-S1956245623.used-as.sat04-35.cnf", "rb");
    std::ifstream answers("../minisat/test/tests/asd.txt");
    uint64_t expected_starts, expected_conflicts, expected_decisions, expected_propagations, expected_tot_literals;
    answers >> expected_starts >> expected_conflicts >> expected_decisions >> expected_propagations >> expected_tot_literals;
    if(in == NULL){
        FAIL() << "Error reading file";
    }
    parse_DIMACS(in, S);

    if (S.simplify()){
        vec<Lit> dummy;
        lbool ret = S.solveLimited(dummy);
    }

    ASSERT_EQ(expected_starts, S.starts);
    ASSERT_EQ(expected_conflicts, S.conflicts);
    ASSERT_EQ(expected_decisions, S.decisions);
    ASSERT_EQ(expected_propagations, S.propagations);
    ASSERT_EQ(expected_tot_literals, S.tot_literals);
}

TEST(fix, test2) {
}
