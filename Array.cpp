////////////////////////////////////////////////////////////////////////
//
//   Author:           Justin Allen
//   Creation Date:    September 8, 2023
//   Due Date:         September 14, 2023
//   Course:           CSC136 010
//   Professor Name:   Dr. Carelli
//   Assignment:       #1
//   Filename:         array.cpp
//
//   Purpose:
//      This program uses parallel arrays to store and process data, reading
//      data files, outputting an organized table of children's names, savings,
//      and star awards based on savings.
//
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define ARRAYSIZE 10

// Function Prototypes
int readDatafile(string[], int[], int[], int[], int[], int);
void calcTotAward(string[], int[], int[], int[], int[], float[], string[], int);
void outputData(string[], int[], int[], int[], int[], int);
void bubbleSort(string[], float[], string[], int);
void outputSortedResults(string[], float[], string[], int);

int main() {
  string names[ARRAYSIZE];  // child names
  int quarters[ARRAYSIZE];  // number of quarters
  int dimes[ARRAYSIZE];     // number of dimes
  int nickels[ARRAYSIZE];   // number of nickels
  int pennies[ARRAYSIZE];   // number of pennies

  float total[ARRAYSIZE];   // total amount
  string star[ARRAYSIZE];   // award

  int numChildren = readDatafile(names, quarters, dimes, nickels, pennies, ARRAYSIZE);

  // Display initial data
  outputData(names, quarters, dimes, nickels, pennies, numChildren);

  // Calculate total savings and star awards
  calcTotAward(names, quarters, dimes, nickels, pennies, total, star, numChildren);

  // Sort data in descending order of total savings
  bubbleSort(names, total, star, numChildren);

  // Display sorted results
  outputSortedResults(names, total, star, numChildren);

  return 0;
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: readDatafile
//   Description:    Reads information from a user-supplied data file
//                    into parallel arrays.
//   Parameters:     n - names (input)
//                   q - quarters (input)
//                   t - dimes (input)
//                   p - pennies (input)
//                   f - nickels (input)
//                   max - maximum number of children's data entries (input)
//   Return Value:   int - the number of entries read
//
////////////////////////////////////////////////////////////////////////
int readDatafile(string n[], int q[], int t[], int f[], int p[], int max) {
  string fname;  // file name
  ifstream ifs;  // input file stream
  int num = 0;   // number of students read

  // Prompt the user for the name of the data file
  cout << "Enter the name of the data file: ";
  cin >> fname;

  ifs.open(fname.c_str()); // Open the file

  if (!ifs.is_open()) {
    cerr << "Error: Unable to open the file." << endl;
    exit(1); // Exit the program gracefully if the file cannot be opened
  }

  // Read data from the file into arrays
  while (num < max && ifs >> n[num] >> q[num] >> t[num] >> p[num] >> f[num]) {
    num++;
  }

  ifs.close(); // Close the file

  return num; // Return the number of entries read
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: outputData
//   Description:    Displays the initial data in a tabular format.
//   Parameters:     n - names (input)
//                   q - quarters (input)
//                   t - dimes (input)
//                   f - nickels (input)
//                   p - pennies (input)
//                   num - the number of children's data entries (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void outputData(string n[], int q[], int t[], int f[], int p[], int num) {
  cout << "Child Name   Quarters  Dimes  Nickels  Pennies" << endl;
  cout << "--------------------------------------------" << endl;
  for (int i = 0; i < num; i++) {
    cout << setw(12) << left << n[i];
    cout << setw(10) << q[i];
    cout << setw(7) << t[i];
    cout << setw(9) << f[i];
    cout << setw(9) << p[i] << endl;
  }
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: calcTotAward
//   Description:    Calculates the total savings and star awards for
//                    each child based on specified rules.
//   Parameters:     n - names (input)
//                   q - quarters (input)
//                   t - dimes (input)
//                   p - pennies (input)
//                   f - nickels (input)
//                   total - total savings (output)
//                   star - star awards (output)
//                   num - the number of children's data entries (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void calcTotAward(string n[], int q[], int t[], int p[], int f[], float total[], string star[], int num) {
  for (int i = 0; i < num; i++) {
    total[i] = q[i] * 0.25 + t[i] * 0.10 + f[i] * 0.05 + p[i] * 0.01; // Calculate total savings

    if (total[i] > 10.0) {
      star[i] = "***"; // 3 stars for savings over $10
    } else if (total[i] > 7.5) {
      star[i] = "**";  // 2 stars for savings between $7.50 and $10
    } else if (total[i] >= 5.0) {
      star[i] = "*";   // 1 star for savings between $5 and $7.50
    } else {
      star[i] = "";    // No stars for savings below $5
    }
  }
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: bubbleSort
//   Description:    Sorts the data in descending order based on total
//                    savings using the bubble sort algorithm.
//   Parameters:     n - names (input/output)
//                   total - total savings (input/output)
//                   star - star awards (input/output)
//                   num - the number of children's data entries (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void bubbleSort(string n[], float total[], string star[], int num) {
  // Bubble sort implementation
  for (int i = 0; i < num - 1; i++) {
    for (int j = 0; j < num - i - 1; j++) {
      if (total[j] < total[j + 1]) {
        // Swap total savings
        float tempTotal = total[j];
        total[j] = total[j + 1];
        total[j + 1] = tempTotal;

        // Swap child names
        string tempName = n[j];
        n[j] = n[j + 1];
        n[j + 1] = tempName;

        // Swap star awards
        string tempStar = star[j];
        star[j] = star[j + 1];
        star[j + 1] = tempStar;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////
//
//   Function Name: outputSortedResults
//   Description:    Displays the sorted results in a tabular format.
//   Parameters:     n - names (input)
//                   total - total savings (input)
//                   star - star awards (input)
//                   num - the number of children's data entries (input)
//   Return Value:   None
//
////////////////////////////////////////////////////////////////////////
void outputSortedResults(string n[], float total[], string star[], int num) {
  cout << "Child Name   Total Savings   Stars" << endl;
  cout << "----------------------------------" << endl;
  for (int i = 0; i < num; i++) {
    cout << setw(12) << left << n[i];
    cout << setw(15) << fixed << setprecision(2) << total[i];
    cout << setw(6) << star[i] << endl;
  }
}
