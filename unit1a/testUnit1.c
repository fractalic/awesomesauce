
#include "unity.h"

void test_TheFirst(void)
{
    //TEST_ASSERT_MESSAGE(1==3, "1 did not equal 2");
    TEST_ASSERT_EQUAL(3,4);
}

void test_TheSecond(void)
{
    TEST_ASSERT_EQUAL(1,2);
}

void test_TheThird(void)
{
    TEST_ASSERT_EQUAL(1.1, 1.2);
    // == TEST_ASSERT_EQUAL_INT(1.1, 1.2);
    // so does this instead
    TEST_ASSERT_EQUAL_FLOAT(1.1, 1.2);
}

void test_TheFourth(void)
{
    TEST_ASSERT_TRUE(1);
    TEST_ASSERT_TRUE_MESSAGE(8 > 7.9, "C comparison failed.");
    TEST_ASSERT_FALSE_MESSAGE(0, "Yay for 0!");
    TEST_ASSERT_FALSE(-1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_TheFirst);
    RUN_TEST(test_TheSecond);
    RUN_TEST(test_TheThird);
    RUN_TEST(test_TheFourth);
    return UNITY_END();
}
