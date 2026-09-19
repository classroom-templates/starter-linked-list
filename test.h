/**
 * @file test.h
 * @author Alex Katrompas
 * @assignment Linked List
 * @brief Declares the stateful LinkedList testing framework.
 */

#ifndef TEST_H
#define TEST_H

#include <string>
#include "linkedlist.h"

/**
 * @struct TestResult
 * @brief Stores the number of passed and executed tests for one test group.
 */
struct TestResult {
    int passed;
    int total;
};

// Testing helpers
void reportTest(const std::string&, const TestResult&, TestResult&);
void runPrintDemo(LinkedList&);
void recordTest(bool, TestResult&);
bool matchesRecord(LinkedList&, int, const std::string&);

// Complete instructor-provided test groups
TestResult testInitialState(LinkedList&);
TestResult testAddAndRetrieve(LinkedList&);
TestResult testRejectedAdditions(LinkedList&);

// Student-completed test groups
TestResult testDeletion(LinkedList&);
TestResult testClearAndReuse(LinkedList&);
TestResult testStress(LinkedList&);

#endif // TEST_H
