// Authors: Gabriel Duarte and Dakota Bold
// Project 2
// CS242: Discreet structures
// Description: we will be reading in test data and getting probabilities

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main ()
{
  string inputTrainingShakespeare; // Declare the string for inputName
  string inputTrainingElizabeth; // Decalre the string for inputName
  string inputTestShakepeare; // Declare the string for inputName
  string inputTestElizabeth;
  cout << "Enter the names of the Shakespearean training file, Elizabethan training file, Shakespearean test file and Elizabethan test file (in that order): "; // Asks the user to enter a file for the data
  cin >> inputTrainingShakespeare >> inputTrainingElizabeth
      >> inputTestShakepeare >> inputTestElizabeth;// Gets the input and puts it into a string
 
  vector < vector<int> > SPoem; // Create a 2D vector for the shakspearean poems
  vector < vector<int> > EPoem; // Create a 2D vector for elizabethan poems
  vector < vector<int> > testData; // Create 2D vector for the test data input file
  vector<double> Sprobability; // Stores the Probabilities of the words turning up in a shakespeare poem
  vector<double> Eprobability; // Stores the Probabilities of the words turning up in a Elizabethan poem
  vector<double> tempS; // Creates the temp vector for the probabilities
  vector<double> tempE; // Creates the temp vector for the probabilities
  vector<int> classification; // Create 2D vector for toy.class.txt
  vector<int> fIn; // Store the Sprobability that the word is in the dictionary
  vector<int> fNotIn; // Store the Sprobability that the word is not in the dictionary
  vector<int> row; // Creates a vector to input rach row in the 2D vectors
  
  string line; // Used to store the line temporarily when reading in the lines from the files.
  double S = 0; // To store the number of Shakspearean poems
  double E = 0; // To store the number of Elizabethan poems
  double TotalPoems = 0; // For the total number of poems
  double f = 0; // For total words that are in the dictionary
  double fNot = 0; // For the total words that are not in the dicitonary
  double probs = 0; // Gets the Sprobability of the occurence in the poem
  double totalProbS = 1; // Gets the total Sprobability for Shakespeare poems
  double totalProbE = 1; // Gets the total Sprobability for Elizabeth poems
  unsigned rowLength = 0; // Variable to keep the length of each row

  ifstream inputData ("toy.data.txt"); // Load the poems
  ifstream inputClass ("toy.class.txt"); // Load the class E or S
  ifstream inputToyTest ("toytest.data.txt"); // Load the test data

  // Insert the test data into a vector
  while (getline (inputToyTest, line))
    {
      int d;
      stringstream lineStream(line);
      while (lineStream >> d)
	row.push_back(d);

      testData.push_back(row);
      row.clear();
    }
  // Insert the class into a vector
  while (getline (inputClass,line)) // Start reading in the lines from the file
    {
      int d; // Create a variable to read each character in the line
      stringstream lineStream(line); // Grab the line one by one
      while (lineStream >> d) // Grab each character one at a time
	{
	  classification.push_back(d); // Adds the integer to the string vector
	  if (d == 1) // Making sure which classification it is
	    {
	      S++; // Increment the S to add to the number of poems for shakespeare
	      getline (inputData, line); // Gets the lines from the files

	      int d; // Create a variable to read each character in the line
	      stringstream lineStream(line); // Grab the line one by one

	      while (lineStream >> d) // Grab each character one by one
		row.push_back(d); // Adds the char to the row vector
	      SPoem.push_back(row); // Adds the row to the 2D vector
	      row.clear(); // Clears the vector

	    }
	  else
	    {
	      E++; // Incremet the E to add the number of poems for elizabeth
	      getline (inputData, line); // Start reading in the lines from the file

	      int d; // Create a variable to read each character in the line
	      stringstream lineStream(line); // Grab the line one by one
	      rowLength  = 0; // Increments the variable to get the row length
	      while (lineStream >> d) // Grab each character one by one
		{
		  row.push_back(d); // Adds the char to the row vector
		  rowLength++; // Gets the number of elements in the binary vector
		}
	      EPoem.push_back(row); // Adds the row to the 2D vector
	      row.clear(); // Clears the vector
	    }
	}
    }

  TotalPoems = E + S; // Declare the Total poems after the poems have been counted for each author

  
  // This loop is to go through the shakespeare poems
  for (unsigned i = 0; i < rowLength; i++)
    {
      for (unsigned j = 0; j < SPoem.size(); j++)
	{
	  if (SPoem.at(j).at(i) == 1) // Checks to see if the current position has the word in it by denoting that 1 equals word is in the poem
	    f++; // Increment the variable that keeps the number of ones in the column
	  
	  if (SPoem.at(j).at(i) == 0)  // Checks to see if the current position has the word in it by denoting that 0 equals that the word is not in the poems
	    fNot++; // Increments the variable that keeps the number of zeros in the column
	}

      fIn.push_back(f); // Add the total amount of ones in the column to the vector
      fNotIn.push_back(fNot); // Add the total amount of zeros in the column to the vector
      probs = (f/SPoem.size()); // Gets the probability of ones to zeros
      Sprobability.push_back(probs); // Adds the probability to the vector for shakespeare
      f = 0; // Reset the value
      fNot = 0; // Reset the value
      probs = 0; // Reset the value
    }

  // This loop is to go through the elizabeth poems
  for (unsigned i = 0; i < rowLength; i++)
    {
      for (unsigned j = 0; j < EPoem.size(); j++)
	{
	  if (EPoem.at(j).at(i) == 1)  // Checks to see if the current position has the word in it by denoting that 1 equals word is in the poem
	    f++; // Increment the variable that keeps the number of ones in the column

	  if (EPoem.at(j).at(i) == 0)  // Checks to see if the current position has the word in it by denoting that 0 equals that the word is not in the poem
	    fNot++; // Increments the variable that keeps the number of zeros in the column
	}

      fIn.push_back(f); // Add the total amount of ones in the column to the vector
      fNotIn.push_back(fNot); // Add the total amount of zeros in the column to the vector
      probs = (f/EPoem.size()); // Gets the probability of ones to zeros
      Eprobability.push_back(probs); // Adds the probability to the vector for shakespeare
      f = 0; // Reset the value
      fNot = 0; // Reset the value
      probs = 0; // Reset the value
    }
      
  for (unsigned i = 0; i < testData.size(); i++)
    {
      tempS = Sprobability; // Create a temp vector so that we dont change the original probabilities 
      tempE = Eprobability; // Create a temp vector so that we dont change the original probabilities
      for (unsigned j = 0; j < rowLength; j++)
	{
	  if (testData.at(i).at(j) == 0)
	    {
		  
	      tempS[j] = 1 - tempS[j] ; // Gets 1-probability
	      tempE[j] = 1 - tempE[j]; // Gets 1-probability
	    }
	  totalProbS *= tempS[j]; // Multiplies all probabilities
	  totalProbE *= tempE[j]; // Multiplies all probabilities
	}
      totalProbS *= (S/TotalPoems); // Multiplies it by the total probability
      totalProbE *= (E/TotalPoems); // Multiplies it by the total probability

      cout << "Test case " << i+1 << endl; // Prints outs the test case number
      cout << "\tp(S|b) = " << totalProbS << endl; // Prints out the probability
      cout << "\tp(E|b) = " << totalProbE << endl; // Prints out the probability

      tempE.clear(); // Clear the temp so that we can get the original probabilities again when the loop loops
      tempS.clear(); // Clear the temp so that we can get the original probabilities again when the loop loops
      totalProbS = 1; // Reset the total probability
      totalProbE = 1; // Reset the total probability
    }

    return 0;
}
