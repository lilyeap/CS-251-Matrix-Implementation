/*  Project 3 My Matrix  
  Course: CS 251, Spring 2023
  Author: Lily Eap
  NetID: leap2
  UIN: 67697798
  File: main.cpp
  Description: consists of test cases for the matrix implementation made in mymatrix.h

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <ctype.h>

using namespace std;
#include "mymatrix.h"

// all functions take parameters: passed, failed 
// which are passed by reference and thus, reflects the total passed and failed cases

bool default_size_test1(int& passed, int& failed){ //tests basic default constructor size
  // creates 4x4 matrix
  int originalFail = failed;
  bool test = true; 
  mymatrix<int> M; 

  if (M.size() != 16){
    failed++;
  } else {
    passed++;
  }
  for (int r = 0; r < M.numrows(); ++r){
     for (int c = 0; c < M.numcols(r); ++c){
        if (M(r,c) != 0){
          test = false;
        }
     }
  }

  if (test){
    passed++;
  } else {
    failed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
} 
bool default_size_test2(int& passed, int& failed){ //tests basic default constructor size for bool, float
  // creates 4x4 matrix
  int originalFail = failed;
  bool test = true; 
  mymatrix<bool> M; 
  if (M.size() != 16){
    failed++;
  } else {
    passed++;
  }
  for (int r = 0; r < M.numrows(); ++r){
     for (int c = 0; c < M.numcols(r); ++c){
        if (M(r,c) != false){
          test = false;
        }
     }
  }

  if (test){
    passed++;
  } else {
    failed++;
  }
  test = true;

  mymatrix<float> M1; 
  if (M1.size() != 16){
    failed++;
  } else {
    passed++;
  }
  for (int r = 0; r < M1.numrows(); ++r){
     for (int c = 0; c < M1.numcols(r); ++c){
        if (M1(r,c) != 0.0f){
          test = false;
        }
     }
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
} 

bool parameterized_size_test1(int& passed, int& failed){ //tests basic param constructor size
  int originalFail = failed;
  mymatrix<int> M1(10,2); 
  if (M1.size() != 20){
    failed++;
  } else {
    passed++;
  }

  mymatrix<int> M2(4,3);
  if (M2.size() != 12){
    failed++;
  } else {
    passed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
} 
bool parameterized_size_test2(int& passed, int& failed){ //tests basic param constructor size for bool, double
  int originalFail = failed;
  mymatrix<bool> M1(10,2); 
  if (M1.size() != 20){
    failed++;
  } else {
    passed++;
  }

  mymatrix<double> M2(4,3);
  if (M2.size() != 12){
    failed++;
  } else {
    passed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
} 

bool copy_size_test1(int& passed, int& failed){ //tests copy constructor on a parameterized
  int originalFail = failed;
  mymatrix<int> M1(10,2); 
  M1.at(0, 0) = 123;
  M1.at(1, 1) = 456;

  mymatrix<int> M2 = M1;
  M2(0, 0) = 900;

  if (M1(0,0) != 123 || M2.at(0,0) != 900){
    failed++;
  } else if (M2.size() != 20){
    failed++;
  } else {
    passed++;
  }  

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
}
bool copy_size_test2(int& passed, int& failed){ //tests copy construct on a jagged
  int originalFail = failed;
  mymatrix<int> jaggedM(4,2);
  jaggedM.growcols(1,10);
  jaggedM.growcols(3,10);
  jaggedM.at(0, 0) = 123;
  jaggedM.at(1, 1) = 456;

  mymatrix<int> M2 = jaggedM;
  M2(0, 0) = 900;

  if (jaggedM(0,0) != 123 || M2.at(0,0) != 900){
    failed++;
  } else if (M2.size() != 24){
    failed++;
  } else {
    passed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
}

bool scalar_function_test1(int& passed, int& failed){ //tests basic function of scalar mult
  int originalFail = failed;
  bool test = true; 
  mymatrix<int> m(2,2);
  mymatrix<int> multi;  
  m.at(0, 0) = 1;
  m.at(0, 1) = 2;
  m.at(1, 0) = 3;
  m.at(1, 1) = 4;

  multi = m * 3;

  for (int r = 0; r < m.numrows(); ++r){
    for (int c = 0; c < m.numcols(r); ++c){
      if (multi(r,c) != 3*m(r,c)){
        test = false;
      }
    }
  }
  if (test){
    passed++;
  } else {
    failed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
}

bool matrix_mult_function_test1(int& passed, int& failed){ //tests basic matrix multiplication
  int originalFail = failed;
  mymatrix<int> m(2,3);
  m.at(0, 0) = 1;
  m.at(0, 1) = 2;
  m.at(0, 2) = 3;
  m.at(1, 0) = 3;
  m.at(1, 1) = 4;
  m.at(1, 2) = 5;
  mymatrix<int> m1(3,1);
  m1.at(0, 0) = 7;
  m1.at(1, 0) = 8;
  m1.at(2, 0) = 9;
  mymatrix<int> m2;
  m2 = m * m1;

  if ((m2(0,0) != 50) && (m2(1,0) != 122)){
    failed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
}

bool growcol_function_test1(int& passed, int& failed){ //tests basic function of growcol
  int originalFail = failed;
  bool test = true; 
  mymatrix<int> m(2,2);
  m.at(0, 0) = 1;
  m.at(0, 1) = 2;
  m.at(1, 0) = 3;
  m.at(1, 1) = 4;
  m.growcols(1,10);
  for (int c = 0; c < m.numcols(1); ++c){
    m.at(1, c) = -1;
  }
  
  if ((m(0,0)==1) && (m(0,1)==2) && (m(1,0)==-1) && (m(1,1)==-1)){
    passed++;
  } else {
    failed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
}

bool multiple_function_test1(int& passed, int& failed){ //tests grow, growcol and scalar mult
  int originalFail = failed;
  bool test = true; 
  mymatrix<int> m(2,2);
  m.at(0, 0) = 1;
  m.at(0, 1) = 1;
  m.at(1, 0) = 1;
  m.at(1, 1) = 1;
  m.grow(5,5);

  for (int r = 0; r < m.numrows(); ++r){
    for (int c = 0; c < m.numcols(r); ++c){
      if (r < 2 && c < 2){
        if (m(r,c) != 1){
          test = false;
        }
      } else if (m(r,c) != 0){
        test = false;
      }
    }
  }
  if (test){
    passed++;
  } else {
    failed++;
  }
  test = true;

  m.growcols(1,10);
  m = m * 3;
  for (int r = 0; r < m.numrows(); ++r){
    for (int c = 0; c < m.numcols(r); ++c){
      if (r == 1 && c < 2){
        if (m(r,c) != 3){
          test = false;
        }
      }
    }
  }
  
  if (test){
    passed++;
  } else {
    failed++;
  }


  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
}
bool multiple_function_test2(int& passed, int& failed){ //tests grow, growcol on matrices that won't grow
  int originalFail = failed;
  mymatrix<int>  M;
  //should not set row num to 3
  M.grow(3,5);

  if (M.numrows() == 3){
    failed++;
  } else {
    passed++;
  }

  mymatrix<int> M1(10,10);

  M1.growcols(1, 5);

  if (M1.numcols(1) != 10){
    failed++;
  } else {
    passed++;
  }

  if (originalFail < failed){
    return false;
  } else {
    return true;
  }
}

bool exception_parameterized(int& passed, int& failed){ //tests exception on basic false call on parameterized constructor
  try{
    mymatrix<int>  M1(0,1);
    cout << "matrix constructor test failed; did not throw exception on parameters" << endl;
    failed++;
    return false;
  } catch (...){
    passed++;
    return true;
  }
}
bool exception_numcol(int& passed, int& failed){ //tests exception on basic false call on numcol
  try{
    mymatrix<int>  M;
    int poop = M.numcols(5);
    cout << "numcols test failed; did not throw exception on r parameter" << endl;
    failed++;
    return false;
  } catch (...){
    passed++;
    return true;
  }
}
bool exception_MatMultMat(int& passed, int& failed){ //tests exception on false call of matrix multiply with jagged
  try {
    mymatrix<int>  M1;
    mymatrix<int>  M2;
 
    M1.growcols(3, 16);
 
    mymatrix<int> result;
 
    result = M1 * M2;  
    // matrix multiply should throw an exception
 
    // if we get here
    // no exception was thrown --- error
    cout << "matrix multiply test failed: " 
      << "jagged matrix did not throw exception" 
      << endl;
    failed++;
    return false;
  }
  catch (...) {
    passed++;  
    return true;
    // if we get here, 
    // exception was thrown --- correct
  }
}
bool exception_grow(int& passed, int& failed){ //tests exception on matrix multiply on matrix that did not reduce size with grow
  try{
    mymatrix<int>  M;
    mymatrix<int>  M1(3,5);
    mymatrix<int>  M2;
    // M matrix should be 5x4 after this grow call
    M.grow(5,3);
    
    //invalid call b/c matrix dimensions false
    M2 = M * M1;
    cout << "grow/matrix mult test failed; did not throw exception on parameters" << endl;
    failed++;
    return false;
  } catch (...){
    passed++;
    return true;
  }
}


int main(){
    int passed = 0;
    int failed = 0;

    if (!default_size_test1(passed, failed)){
      cout << "default size 1 failed" << endl;
    }
    if (!default_size_test2(passed, failed)){
      cout << "default size 2 failed" << endl;
    }
    if (!parameterized_size_test1(passed, failed)){
      cout << "parameterized size 1 failed" << endl;
    }
    if (!parameterized_size_test2(passed, failed)){
      cout << "parameterized size 2 failed" << endl;
    }
    if (!copy_size_test1(passed, failed)){
      cout << "copy parameter size failed" << endl;
    }
    if(!copy_size_test2(passed, failed)){
      cout << "copy jagged size failed" << endl;
    } 
    if(!scalar_function_test1(passed, failed)){
      cout << "basic scalar function failed" << endl;
    } 
    if(!matrix_mult_function_test1(passed, failed)){
      cout << "basic scalar function failed" << endl;
    } 
    if(!growcol_function_test1(passed, failed)){
      cout << "basic growcol function failed" << endl;
    } 
    if(!multiple_function_test1(passed, failed)){
      cout << "basic grow(col) function failed" << endl;
    } 
    if(!multiple_function_test2(passed, failed)){
      cout << "advanced grow(col) function failed" << endl;
    } 
    if(!exception_parameterized(passed, failed)){
      //already couts within the function
    } 
    if(!exception_numcol(passed, failed)){
      //already couts within the function
    } 
    if(!exception_MatMultMat(passed, failed)){
      //already couts within the function
    } 
    if(!exception_grow(passed, failed)){
      //already couts within the function
    } 

    cout << "Tests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;
  return 0;
}