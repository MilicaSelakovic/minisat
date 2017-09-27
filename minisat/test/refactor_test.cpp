#include "gtest/gtest.h"
#include "minisat/core/Solver.h"
#include <fstream>
#include <zlib.h>
#include "minisat/core/Dimacs.h"
#include <string>

using namespace Minisat;
using std::string;

const string samplesPath = "../minisat/test/samples/";
const string answersExtension = ".answers.txt";

//#define  UPDATE_ANSWERS

class RefactorTest : public ::testing::Test{
protected:
    void testFromFile(string fileName){
        Solver S;
        gzFile in = gzopen((samplesPath + fileName).c_str(), "rb");
        if(in == NULL){
            FAIL() << "Error reading cnf file" + (samplesPath + fileName);
        }
        parse_DIMACS(in, S);

#ifdef UPDATE_ANSWERS
        std::ofstream answers((samplesPath + fileName + answersExtension).c_str());
        if(!answers.is_open()){
            FAIL() << "Error creating answers file";
        }
#else
            std::ifstream answers((samplesPath + fileName + answersExtension).c_str());
        if(!answers.is_open()){
            FAIL() << "Error reading answers file";
        }
        uint64_t expected_starts, expected_conflicts, expected_decisions, expected_propagations, expected_tot_literals;
        answers >> expected_starts >> expected_conflicts >> expected_decisions >> expected_propagations >> expected_tot_literals;
#endif

        if (S.simplify()){
            vec<Lit> dummy;
            lbool ret = S.solveLimited(dummy);
        }

#ifdef UPDATE_ANSWERS
        answers << S.starts << std::endl;
        answers << S.conflicts << std::endl;
        answers << S.decisions << std::endl;
        answers << S.propagations << std::endl;
        answers << S.tot_literals << std::endl;
#else
        ASSERT_EQ(expected_starts, S.starts);
        ASSERT_EQ(expected_conflicts, S.conflicts);
        ASSERT_EQ(expected_decisions, S.decisions);
        ASSERT_EQ(expected_propagations, S.propagations);
        ASSERT_EQ(expected_tot_literals, S.tot_literals);
#endif
    }
};

TEST_F(RefactorTest, test1) {
    testFromFile("test1.cnf");
}

TEST_F(RefactorTest, test2) {
    testFromFile("test2.cnf");
}

TEST_F(RefactorTest, test3) {
    testFromFile("test3.cnf");
}

TEST_F(RefactorTest, test4) {
    testFromFile("test4.cnf");
}

TEST_F(RefactorTest, test5) {
    testFromFile("test5.cnf");
}

TEST_F(RefactorTest, test6) {
    testFromFile("test6.cnf");
}

TEST_F(RefactorTest, test7) {
    testFromFile("test7.cnf");
}

TEST_F(RefactorTest, test8) {
    testFromFile("test8.cnf");
}

