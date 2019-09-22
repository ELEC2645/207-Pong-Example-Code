#ifndef TESTS_H
#define TESTS_H

#include "Ball-test.h"

/**
 * @brief Run all the tests for this program
 *
 * @returns The number of tests that failed
 */
int run_all_tests()
{
    int n_tests_failed = 0; // A log of the number of tests that have failed

    // Run the Ball_test_movement test
    printf("Testing Ball_test_movement...\n");
    bool this_test_passed = Ball_test_movement();

    // Print out the result of this test
    if (this_test_passed) {
        printf("...Passed!\n");
    }
    else {
        printf("...FAILED!\n");
        ++n_tests_failed; // Increment number of failures
    }
    
    // Repeat the above for each testing function...
    // ...
    // ...

    // Finish by printing a summary of the tests
    if (n_tests_failed > 0) {
        printf("%d tests FAILED!\n", n_tests_failed);
    }
    else {
        printf("All tests passed!\n");
    }

    return n_tests_failed;
}

#endif