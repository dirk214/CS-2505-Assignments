#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Rational.h"
#include "TestRational.h"
extern bool profMode;

int main(int argc, char** argv) {

   unsigned int Seed;
   FILE* Summary;
   
   if ( argc > 1 ) {
      Seed = (unsigned int) time(NULL);
      FILE* fp = fopen("Seed.txt", "w");
      fprintf(fp, "%u\n", Seed);
      fclose(fp);
      profMode = true;
      Summary = fopen("profSummary.txt", "w");
   }
   else {
      FILE* fp = fopen("Seed.txt", "r");
      fscanf(fp, "%u", &Seed);
      fclose(fp);
      profMode = false;
      Summary = fopen("Summary.txt", "w");
   }
   unsigned int seedStep = Seed % 10000;
   srand(Seed);

   writePoints(Summary, 0);
   if ( testConstruct() ) {
      fprintf(Summary, "Passed test of Rational_Construct().\n");
   }
   else {
      fprintf(Summary, "Failed test of Rational_Construct().\n");
      writePoints(Summary, 0);
      fprintf(Summary, "Aborting remaining tests.\n");
      fclose(Summary);
      return 0;
   }

   srand(Seed + seedStep);
   writePoints(Summary, 0);
   if ( testNegate() ) {
      fprintf(Summary, "Passed test of Rational_Negate().\n");
   }
   else {
      fprintf(Summary, "Failed test of Rational_Negate().\n");
   }

   srand(Seed + seedStep);
   writePoints(Summary, 0);
   if ( testFloor() ) {
      fprintf(Summary, "Passed test of Rational_Floor().\n");
   }
   else {
      fprintf(Summary, "Failed test of Rational_Floor().\n");
   }

   srand(Seed + seedStep);
   writePoints(Summary, 0);
   if ( testAdd() ) {
      fprintf(Summary, "Passed test of Rational_Add().\n");
   }
   else {
      fprintf(Summary, "Failed test of Rational_Add().\n");
   }

   srand(Seed + seedStep);
   writePoints(Summary, 0);
   if ( testMultiply() ) {
      fprintf(Summary, "Passed test of Rational_Multiply().\n");
   }
   else {
      fprintf(Summary, "Failed test of Rational_Multiply().\n");
   }

   srand(Seed + seedStep);
   writePoints(Summary, 0);
   if ( testEQ() ) {
      fprintf(Summary, "Passed test of Rational_Equals().\n");
   }
   else {
      fprintf(Summary, "Failed test of Rational_Equals().\n");
   }

   srand(Seed + seedStep);
   writePoints(Summary, 0);
   if ( testLT() ) {
      fprintf(Summary, "Passed test of Rational_LessThan().\n");
   }
   else {
      fprintf(Summary, "Failed test of Rational_LessThan().\n");
   }
   
   fclose(Summary);
   return 0;
}

