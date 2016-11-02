
#define DIMENSION_OF(a) ( sizeof(a)/sizeof(a[0]) )

#include "unity.h"
#include "Fib.h"
#include <limits.h>

/* NOTES:
 * Choose your names to describe requirements,
 * not stuff that is obvious from the code.
 */
void test_element0_should_return1(void)
{
    TEST_ASSERT_EQUAL_INT(1, Fibonacci_GetElement(0));
}

void test_element1_should_return1(void)
{
    int retval = Fibonacci_GetElement(1);
    TEST_ASSERT_EQUAL_INT(1, retval);
}

void test_element2_should_return2(void)
{
    TEST_ASSERT_EQUAL_INT(2, Fibonacci_GetElement(2));
}

void test_part_of_the_sequence(void)
{
    int expected[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
    int i;
    
    for (i=0; i < DIMENSION_OF(expected); i++) {
        TEST_ASSERT_EQUAL_INT(expected[i], Fibonacci_GetElement(i));
    }
}

/*
 * NOTES:
 * 0 is our magic number to return on erroneous input.
 */
void test_that_negative_values_return0(void)
{
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(-1));
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(-3));
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(-555));
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(INT_MIN));
}

void test_that_overrun_values_return0(void)
{
    const int first_bad_element = 46;
    const int last_good_element = first_bad_element - 1;
    int last_good_value = Fibonacci_GetElement(last_good_element);
    
    /* NOTES:
     * The code in this function is not portable:
     * We assume that integers are 32-bits, such that
     * integer overflow occurs at the 46th element in the
     * Fibonacci sequence.
     * To compensate for this, our first assertion should
     * validate our assumption.
     */
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, sizeof(int),
      "Constants first_bad_element and FIB_MAX_ELEMENT Must Be Changed.");
    
    TEST_ASSERT_MESSAGE(last_good_value > 1, "This value should not have been a rollover.");
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(first_bad_element));
    // boundary check
    TEST_ASSERT_EQUAL_INT(0, Fibonacci_GetElement(INT_MAX));
    
}

/* SECTION for Fibonacci_IsInSequence */

void test_that_1_is_in_sequence(void)
{
    TEST_ASSERT_TRUE(Fibonacci_IsInSequence(1)); 
}

void test_that_8_is_in_sequence(void)
{
    TEST_ASSERT_TRUE(Fibonacci_IsInSequence(8));
}

void test_several_elements_in_sequence(void)
{
    int elements[] = {3, 5, 8, 13, 21, 34, 55, 89, 144};
    int i;
    
    for (i=0; i < DIMENSION_OF(elements); i++) {
        TEST_ASSERT_TRUE(Fibonacci_IsInSequence(elements[i]));
    }
}

void test_that_large_numbers_do_not_overflow(void)
{
    const int last_good_sum = 1836311903;
    const int first_overflow_not_in_sequence = last_good_sum + 1;
    
    // Verify our architectural assumptions.
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, sizeof(int),
      "Constant last_good_sum must be changed.");
    TEST_ASSERT_TRUE_MESSAGE(last_good_sum > 1,
      "Constant last_good_sum cannot be stored on this machine.");
    TEST_ASSERT_TRUE_MESSAGE(first_overflow_not_in_sequence > 1,
      "Constant first_overflow_not_in_sequence cannot be stored on this machine.");
    
    // Complete the intended test.
    TEST_ASSERT_TRUE(Fibonacci_IsInSequence(last_good_sum));
    TEST_ASSERT_FALSE(Fibonacci_IsInSequence(last_good_sum+1));
}

void test_that_0_not_in_sequence(void)
{
    TEST_ASSERT_FALSE(Fibonacci_IsInSequence(0));
}

void test_that_negative_numbers_not_in_sequence(void)
{
    TEST_ASSERT_FALSE(1);
    
    int nonElements[] = {-1, -10, -1007, INT_MIN};
    int i;
    
    for (i = 0; i < DIMENSION_OF(nonElements); i++) {
        TEST_ASSERT_FALSE(Fibonacci_IsInSequence(nonElements[i]));
    }
}

int main(void) {
    UNITY_BEGIN();
    // It's nice that we have the first few elements tested.
    RUN_TEST(test_element0_should_return1);
    RUN_TEST(test_element1_should_return1);
    // It's also nice that we have the first addition-element
    // tested.
    RUN_TEST(test_element2_should_return2);
    // Now we can start a summary test.
    // We could also do this sooner; depends on code style.
    RUN_TEST(test_part_of_the_sequence);
    RUN_TEST(test_that_negative_values_return0);
    RUN_TEST(test_that_overrun_values_return0);
    
    // Lecture 9 challenge tests.
    RUN_TEST(test_that_1_is_in_sequence);
    RUN_TEST(test_that_8_is_in_sequence);
    RUN_TEST(test_several_elements_in_sequence);
    RUN_TEST(test_that_0_not_in_sequence);
    RUN_TEST(test_that_negative_numbers_not_in_sequence);
    RUN_TEST(test_that_large_numbers_do_not_overflow);
    return UNITY_END();
}
