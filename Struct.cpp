////////////////////////////////////////////////////////////////////////
//
//   Author:           Justin Allen
//   Creation Date:    September 8, 2023
//   Due Date:         September 14, 2023
//   Course:           CSC136 010
//   Professor Name:   Dr. Carelli
//   Assignment:       #1
//   Filename:         struct.cpp
//
//   Purpose:
//      This program uses an array of structs
//      to store and process data, reading data
//      files, and outputting an organized table
//      of children's names, savings, and star
//      awards based on savings.
//
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define ARRAYSIZE 10

// Define a struct to store child data
struct Child {
  string name;
  int quarters;
  int dimes;
  int nickels;
  int pennies;
  float total;
  string star;
};

// Prototypes
int readDatafile(Child[], int);
void calcTotAward(Child[], int);
void outputData(Child[], int);
void bubbleSort(Child[], int);
void outputSortedResults(Child[], int);

int main() {
  Child children[ARRAYSIZE]; // Array of Child structs
  int numChildren = readDatafile(children, ARRAYSIZE);

  outputData(children, numChildren); 
  calcTotAward(children, numChildren);
  bubbleSort(children, numChildren);
  outputSortedResults(children, numChildren);

  return 0;
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: readDatafile
//   Description:    Open and read the data file.
//   Parameters:     Child children[] - an array of Child structs (output)
//                   int max - maximum number of children to read (input)
//   Return Value:   int - the number of children read
//
////////////////////////////////////////////////////////////////////////
int readDatafile(Child children[], int max) {
  string fname;  // file name
  ifstream ifs;  // input file stream
  int num = 0;   // number of children read

  // Prompt the user for the name of the data file
  cout << "Enter the name of the data file: ";
  cin >> fname;

  ifs.open(fname.c_str()); // Open the file

  if (!ifs.is_open()) {
    cerr << "Error: Unable to open the file." << endl;
    exit(1); // Exit the program if the file cannot be opened
  }

  // Read data from the file into the Child struct array
  while (num < max && ifs >> children[num].name >> children[num].quarters >> children[num].dimes >> children[num].nickels >> children[num].pennies) {
    num++;
  }

  ifs.close(); // Close the file

  return num; // Return the number of entries read
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: outputData
//   Description:    Output child data in a table format.
//   Parameters:     Child children[] - an array of Child structs (input)
//                   int num - the number of children to output (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void outputData(Child children[], int num) {
  cout << "Child Name   Quarters  Dimes  Nickels  Pennies" << endl;
  cout << "--------------------------------------------" << endl;
  for (int i = 0; i < num; i++) {
    cout << setw(12) << left << children[i].name;
    cout << setw(10) << children[i].quarters;
    cout << setw(7) << children[i].dimes;
    cout << setw(9) << children[i].nickels;
    cout << setw(9) << children[i].pennies << endl;
  }
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: calcTotAward
//   Description:    Calculate total savings and star awards for each child.
//   Parameters:     Child children[] - an array of Child structs (input/output)
//                   int num - the number of children to process (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void calcTotAward(Child children[], int num) {
  for (int i = 0; i < num; i++) {
    children[i].total = children[i].quarters * 0.25 + children[i].dimes * 0.10 + children[i].nickels * 0.05 + children[i].pennies * 0.01; // Calculate total savings

    if (children[i].total > 10.0) {
      children[i].star = "***"; // 3 stars for savings over $10
    } else if (children[i].total > 7.5) {
      children[i].star = "**";  // 2 stars for savings between $7.50 and $10
    } else if (children[i].total >= 5.0) {
      children[i].star = "*";   // 1 star for savings between $5 and $7.50
    } else {
      children[i].star = "";    // No stars for savings below $5
    }
  }
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: bubbleSort
//   Description:    Sort children based on total savings in descending order.
//   Parameters:     Child children[] - an array of Child structs (input/output)
//                   int num - the number of children to sort (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void bubbleSort(Child children[], int num) {
  // Bubble sort implementation
  for (int i = 0; i < num - 1; i++) {
    for (int j = 0; j < num - i - 1; j++) {
      if (children[j].total < children[j + 1].total) {
        // Swap total savings
        swap(children[j].total, children[j + 1].total);

        // Swap child names
        swap(children[j].name, children[j + 1].name);

        // Swap star awards
        swap(children[j].star, children[j + 1].star);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: outputSortedResults
//   Description:    Output child data after sorting by total savings.
//   Parameters:     Child children[] - an array of Child structs (input)
//                   int num - the number of children to output (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void outputSortedResults(Child children[], int num) {
  cout << "Child Name   Total Savings   Stars" << endl;
  cout << "----------------------------------" << endl;
  for (int i = 0; i < num; i++) {
    cout << setw(12) << left << children[i].name;
    cout << setw(15) << fixed << setprecision(2) << children[i].total;
    cout << setw(6) << children[i].star << endl;
  }
}
