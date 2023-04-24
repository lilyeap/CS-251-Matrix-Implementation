/*mymatrix.h*/

/*  Project 3 My Matrix  
  Course: CS 251, Spring 2023
  Author: Lily Eap
  NetID: leap2
  UIN: 67697798
  File: matrix.h, code for matrix implementation 
  Description: creates a matrix data structure that is usable in cpp files when imported. it has multiple functions such as grow, numcols, numrows, etc.

*/

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

  
public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    //TODO:
    Rows = new ROW[R];  // an array with R ROW structs:
    NumRows = R;

    int desiredCols = C;
    // initialize each row to have C columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[desiredCols];  // an array with C elements of type T:
      Rows[r].NumCols = desiredCols;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }


  //
  // copy constructor:
  //
  // Called automatically by C ++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
    //allocate new space, same amount as other matrix
    Rows = new ROW[other.NumRows];
    NumRows = other.NumRows;
    int otherNumCol = 0;
    for (int r = 0; r < NumRows; ++r)
    {
      //allocate space with same amount of column spaces as other matrix
      otherNumCol = other.Rows[r].NumCols;
      Rows[r].Cols = new T[otherNumCol];  
      Rows[r].NumCols = otherNumCol;

      // initialize the elements to the other matrix's elements:
      for (int c = 0; c < otherNumCol; ++c){
        Rows[r].Cols[c] = other.Rows[r].Cols[c];  
      }
    }

  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    //access private member 
    return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    //access private member
    return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    int originalCol = 0;
    //if num cols in that row is lower than what is desired
    if (Rows[r].NumCols < C){
      //allocate new space
      T* growColumns = new T[C];

      //set the original values
      originalCol = Rows[r].NumCols;
      for(int c = 0; c < originalCol;c++){
        growColumns[c] = Rows[r].Cols[c];
      }

      //set the rest of the columns as default value
      Rows[r].NumCols = C;
      for (int c = originalCol; c < Rows[r].NumCols; ++c){
        growColumns[c] = T{};  
      }
      
      //reset the pointer of the row's cols to the newly allocated space
      Rows[r].Cols = growColumns;
    }
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");

    // for the existing rows, we grow their columns to the desired number
    for (int i = 0; i < NumRows; i++){
      if (Rows[i].NumCols < C){
        growcols(i,C);
      }
    }

    // reset the value we store for the total number of rows 
    // to the desired rows if it was greater than the original
    int origRows = NumRows;
    if (NumRows < R){
      NumRows = R;
    }

    // matrix columns will all be the same so set it to matCols 
    // so that we don't have to access that part of memory each time
    int matCols = Rows[0].NumCols;
    // create a new matrix that will hold the new rows/columns
    mymatrix<T> result(NumRows, matCols);

    for (int r = 0; r < NumRows; ++r){
      // copying the existing rows into result
      if (r < origRows){
        for (int c = 0; c < matCols; ++c){
          result(r,c) = Rows[r].Cols[c];  
        }
      // set the new rows
      } else {
        // set the columns to the default value
        for (int c = 0; c < matCols; ++c){
          result(r,c) = T{};  
        }
      }
    }
    // set our current rows to the resulting rows
    this->Rows = result.Rows;
    this->NumRows = result.NumRows;
  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    int counter = 0;
    // sum each row's number of columns
    for (int row = 0; row < NumRows; ++row)
    {
      counter += Rows[row].NumCols;
    }
    return counter;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    return Rows[r].Cols[c];
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    //access private member
    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    // create a new matrix that will hold the result
    mymatrix<T> result;
    int oldNumCol = 0;
    // rows are set to the same as the matrix's rows
    result.Rows = new ROW[NumRows];
    result.NumRows = NumRows;

    for (int r = 0; r < result.NumRows; ++r)
    {
      // columns are set to the same as the matrix's columns
      oldNumCol = Rows[r].NumCols;
      // allocate space for it
      result.Rows[r].Cols = new T[oldNumCol]; 
      result.Rows[r].NumCols = oldNumCol;

      // multiply each of the matrix's original element by the scalar 
      // and store in new matrix
      for (int c = 0; c < oldNumCol; ++c)
      {
        result.Rows[r].Cols[c] = Rows[r].Cols[c] * scalar;  
      }
    }

    return result;
  }

  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    //
    // both matrices must be rectangular for this to work:
    //

    //check if all columns are the same size
    int thisCol = numcols(0);
    int thisRow = NumRows;
    for (int r = 0; r < thisRow; r++){
      if (thisCol != numcols(r)){
        throw runtime_error("mymatrix::*: this not rectangular");
      }
    }

    //check if all columns are the same size
    int otherCol = other.numcols(0);
    int otherRow = other.NumRows;
    for (int r = 0; r < otherRow; r++){
      if (otherCol != other.numcols(r)){
        throw runtime_error("mymatrix::*: other not rectangular");
      }
    }

    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //

    //if the first matrix's columns do not match the number of rows in the other matrix, throw 
    if (thisCol != otherRow){
      throw runtime_error("mymatrix::*: size mismatch");
    }

    //
    // Okay, we can multiply:
    //
    // R1xN * NxC2 = R1xC2
    mymatrix<T> result(thisRow, otherCol);
    for (int r = 0; r < result.numrows(); ++r)
    {
      for (int c = 0; c < result.numcols(r); ++c)
      {
        for (int k = 0; k < thisCol; k++){
          //add left matrix rows by other matrix columns and store in resulting matrix
          result(r,c) += at(r,k) * other.at(k,c);
        }
      }
    }

    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};