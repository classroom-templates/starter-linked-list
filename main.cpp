/**
 * @file main.cpp
 * @author Alex Katrompas
 * @assignment Linked List
 * @brief Runs and reports the stateful LinkedList test suite.
 */

#include "main.h"

/**
 * @brief Executes the complete stateful LinkedList testing framework.
 *
 * @param none
 * @return int Returns 0 when execution completes normally.
 * @exception none
 * @note Exactly one LinkedList object is created for the test suite. Every
 *       test group receives that same object by reference and continues from
 *       the state produced by the preceding group.
 */
int main() {

    LinkedList list;

    TestResult totals = {0, 0};

    std::cout << "Beginning LinkedList tests..." << std::endl;

    reportTest("initial state", testInitialState(list), totals);
    reportTest("add and retrieve", testAddAndRetrieve(list), totals);
    reportTest("rejected additions", testRejectedAdditions(list), totals);

    // The same five-Node object is used for visual traversal verification.
    runPrintDemo(list);

    // These student-completed groups continue beating up the same object.
    reportTest("deletion transitions", testDeletion(list), totals);
    reportTest("clear and reuse", testClearAndReuse(list), totals);
    reportTest("scaled stress", testStress(list), totals);

    std::cout << std::endl;
    std::cout << "Recorded test results: "
              << totals.passed << "/" << totals.total
              << " passed." << std::endl;

    std::cout << "Any test group marked INCOMPLETE must be implemented "
              << "before submission." << std::endl;

    return 0;
}
