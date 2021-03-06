// Authors: Gabriel Duarte and Dakota Bold
// Project 2
// CS242: Discreet structures
// Description: we will be reading in test data and getting probabilities

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void populateFeature(const vector<string>& sonnet, const vector<string>& dictionary, vector<int>& currentFeature);
int checkWord(string word, const vector<string>& sonnet);

int main ()
{
  string inputTrainingShakespeare; // Declare the string for inputName
  string inputTrainingElizabeth; // Decalre the string for inputName
  string inputTestShakepeare; // Declare the string for inputName
  string inputTestElizabeth;
  cout << "Enter the names of the Shakespearean training file, Elizabethan training file, Shakespearean test file and Elizabethan test file (in that order): "; // Asks the user to enter a file for the data
  cin >> inputTrainingShakespeare >> inputTrainingElizabeth
      >> inputTestShakepeare >> inputTestElizabeth;// Gets the input and puts it into a string
      
  ifstream inputSTraining (inputTrainingShakespeare.c_str()); // Load the poems
  ifstream inputETraining (inputTrainingElizabeth.c_str()); // Load the class E or S
  ifstream inputSTest (inputTestShakepeare.c_str()); // Load the test data
  ifstream inputETest (inputTestElizabeth.c_str());
  ifstream dictionary ("dictionary.txt");
 
  vector < vector<string> > Strain; // Create a 2D vector for the shakspearean poems
  vector < vector<string> > Etrain; // Create a 2D vector for elizabethan poems
  vector < vector<string> > Stest; // Create 2D vector for the test data input file
  vector < vector<string> > Etest;
  vector <string> stringrow;
  vector <string> dict;
  vector <float> probability;
  vector < vector<int> > Strainwords; // Stores the Probabilities of the words turning up in a shakespeare poem
  vector<int> Etrainwords; // Stores the Probabilities of the words turning up in a Elizabethan poem
  vector<double> tempS; // Creates the temp vector for the probabilities
  vector<double> tempE; // Creates the temp vector for the probabilities

  vector<int> fIn; // Store the Sprobability that the word is in the dictionary

  vector<int> row; // Creates a vector to input rach row in the 2D vectors
  
  string line; // Used to store the line temporarily when reading in the lines from the files.
  float TotalPoems = 0; // For the total number of poems
  float f = 0; // For total words that are in the dictionary
  float fNot = 0; // For the total words that are not in the dicitonary
  float probs = 0; // Gets the Sprobability of the occurence in the poem
  float totalProbS = 0; // Gets the total Sprobability for Shakespeare poems
  float totalProbE = 1; // Gets the total Sprobability for Elizabeth poems
  unsigned rowLength = 0; // Variable to keep the length of each row

while (getline (dictionary, line))
    {
      string  d;
      stringstream lineStream(line);
      while (lineStream >> d)
	dict.push_back(d);
    }
  
  // Insert the test data into a vector
  while (getline (inputSTraining, line))
    {
      string  d;
      stringstream lineStream(line);
 
      while (lineStream >> d)
	stringrow.push_back(d);
      Strain.push_back(stringrow);
    }

  while (getline (inputETraining, line))
    {
      stringrow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	stringrow.push_back(d);
      Etrain.push_back(stringrow);
    }

  while (getline (inputSTest, line))
    {
      stringrow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	stringrow.push_back(d);
      Stest.push_back(stringrow);
    }

  while (getline (inputETest, line))
    {
      stringrow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	stringrow.push_back(d);
      Etest.push_back(stringrow);
    }

  cout << Strain.size() << endl;
  cout << Etrain.size() << endl;
  
TotalPoems = log((float)Strain.size()/(Strain.size()+Etrain.size())); // Declare the Total poems after the poems have been counted for each author
  
//TotalPoems = log((float)(Strain.size()/(Strain.size() + Etrain.size()))); // Declare the Total poems after the poems have been counted for each author

  int numWords = dict.size(); //Number of words in the dictionary
  vector<int> currentFeature(numWords); //Define a vector whose size is equal to the size of the dictionary.

  for (int i = 0; i < Strain.size(); i++)
  {
    populateFeature(Strain[i], dict, currentFeature);
    Strainwords.push_back(currentFeature);
  }

  
 
  // This loop is to go through the shakespeare poems
  for (unsigned i = 0; i < dict.size(); i++)
    {
      for (unsigned j = 0; j < Strainwords.size(); j++)
	{
	  if (Strainwords.at(j).at(i) == 1) // Checks to see if the current position has the word in it by denoting that 1 equals word is in the poem
	    f++; // Increment the variable that keeps the number of ones in the column
	}
      
      probs = ((1+f)/(Strainwords.size()+2)); // Gets the probability of ones to zeros
      probability.push_back(probs); // Adds the probability to the vector for shakespeare
      f = 0; // Reset the value

      probs = 0; // Reset the value
    }
  
  for (unsigned i = 0; i < probability.size(); i++)
    {
      if (probability.at(i) == 0)
	{
	  //	  cout << "probability " << i << ": " << probability[i];  
	  probability[i] = (1 + probability[i])/(Strain.size()+2) ; // Gets 1-probability
	  //cout << " changed to: " << probability[i] << endl;
	}
      
      totalProbS += log(probability[i]); // Multiplies all probabilities
    }
  //totalProbS = (totalProbS);

  // cout << "This is total probS before adding log(p(C)): " << totalProbS << endl;
  totalProbS += float(TotalPoems); // Multiplies it by the total probability
  cout << TotalPoems << endl;
  // cout << "This is total probS after adding log(p(C)): " << totalProbS << endl;
  //cout << Strain.size() << "/" << Strain.size() << "+" << Etrain.size() << endl;
  // cout << (log(75/(75+87))) << endl;


  //for (int i = 0; i < probability.size(); i++)
  //   cout << "Probability " << i << ": " << probability[i] << endl;



  return 0;
}


int checkWord(string word, const vector<string>& sonnet)
{
    //Linear search to check if word exists in the array sonnet
    for (int i=0; i<sonnet.size(); ++i)
    {
        if (!sonnet[i].compare(word))
            return 1;
    }

    return 0;

}

void populateFeature(const vector<string>& sonnet, const vector<string>& dictionary, vector<int>& currentFeature)
{

    //Go through each word in dictinary and check if it exists in sonnet
    for (int i=0; i<dictionary.size(); ++i)
    {
        currentFeature[i] = checkWord(dictionary[i], sonnet);
    }

}
