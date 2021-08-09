#ifndef TEST_RATIONAL_H
#define TEST_RATIONAL_H
#include <stdbool.h>
#include <stdio.h>

bool testConstruct();

bool testNegate();
bool testFloor();

bool testAdd();
bool testMultiply();

bool testEQ();
bool testLT();

void writePoints(FILE* fp, int Pts);

#endif

