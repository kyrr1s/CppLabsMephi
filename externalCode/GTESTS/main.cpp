#include <gtest/gtest.h>
#include "..\dialog.h"

TEST(solver, erase_spaces) {
    std::string str = "asfa    123   gwq  werw ";
    ASSERT_NO_THROW(erase_spaces(str));
    ASSERT_EQ(str.end(), std::find(str.begin(), str.end(), ' '));
}

TEST (solver, good) {
    BigInt a("1234567"), b("123000"), c("12345"), d("51221");
    BigInt result = a+b-(c+d);
    std::string str = "1234567+  123000 -             (12345 + 51221)";
    ASSERT_NO_THROW(erase_spaces(str));
    ASSERT_EQ(false, isWrongExpression(str));
    ConvertToPN pn;
    ASSERT_NO_THROW(pn.convert(str));
    BigInt res;
    ASSERT_NO_THROW(res = solve(str, std::cout));
    ASSERT_EQ(result, res);
}

TEST(solver, noopertors) {
    std::string str = "1234512    12312";
    ASSERT_NO_THROW(erase_spaces(str));
    ASSERT_EQ(true, isNoOperators(str));
}

TEST(solver, wrongAmBrackets1) {
    std::string str = "123412 + (12313 - 123124";
    ASSERT_NO_THROW(erase_spaces(str));
    ASSERT_EQ(true, isBrackets(str));
}

TEST(solver, wrongAmBrackets2) {
    std::string str = "12314 + 12312 - 11234)";
    ASSERT_NO_THROW(erase_spaces(str));
    ASSERT_EQ(true, isBrackets(str));
}

TEST(solver, onlyops) {
    std::string str = "+ - ( )";
    ASSERT_NO_THROW(erase_spaces(str));
    ASSERT_EQ(true, isOnlyOperators(str));
}

TEST(opn, good) {
    std::string str = "8+3-9";
    ConvertToPN pn;
    ASSERT_NO_THROW(pn.convert(str));
    ASSERT_EQ("8 3 + 9 -", pn.getStrOut());
}

TEST(opn, wrongop) {
    std::string str = "8+3|9";
    ConvertToPN pn;
    ASSERT_ANY_THROW(pn.convert(str));
}

TEST(opn, wrongstart) {
    std::string str = "+3-9";
    ConvertToPN pn;
    ASSERT_ANY_THROW(pn.convert(str));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}