// Authors: Gabriel Duarte and Dakota Bold
// Project 2
// CS242: Discreet structures
// Description: we will be reading in test data and getting probabilities

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void getFiles () ;
void inputData ();
void probabilities(vector<int> currentFeature);
void inornotin (vector<int> currentFeature);
void print();
void populateFeature (const vector<string>& sonnet, const vector<string>& dictionary, vector<int>& currentFeature);

string inputTrainingShakespeare; // Declare the string for inputName
string inputTrainingElizabeth; // Decalre the string for inputName
string inputTestShakepeare; // Declare the string for inputName
string inputTestElizabeth;
vector < vector<int> > SPoem; // Create a 2D vector for the shakspearean poems
vector < vector<int> > EPoem; // Create a 2D vector for elizabethan poems
vector < vector<int> > testDataS; // Create 2D vector for the test data input file
vector < vector<int> > testDataE;
vector<int> row; // Creates a vector to input rach row in the 2D vectors

vector <string> srow;
vector < vector <string> > sp;
vector < vector <string> > ep;
vector < vector <string> > ts;
vector < vector <string> > te;

vector <string> dict;
  double S = 0; // To store the number of Shakspearean poems
  double E = 0; // To store the number of Elizabethan poems
  double TotalPoems = 0; // For the total number of poems
  double f = 0; // For total words that are in the dictionary
  double fNot = 0; // For the total words that are not in the dicitonary
  double probs = 0; // Gets the Sprobability of the occurence in the poem
  double totalProbS = 1; // Gets the total Sprobability for Shakespeare poems
  double totalProbE = 1; // Gets the total Sprobability for Elizabeth poems
  unsigned rowLength = 0; // Variable to keep the length of each row
  vector<double> Sprobability; // Stores the Probabilities of the words turning up in a shakespeare poem
  vector<double> Eprobability; // Stores the Probabilities of the words turning up in a Elizabethan poem
  vector<int> tempS; // Creates the temp vector for the probabilities
  vector<double> tempE; // Creates the temp vector for the probabilities
  vector<int> classification; // Create 2D vector for toy.class.txt
int count = 0;

int main ()
{
  getFiles();
  inputData ();
  print();

  
  int numWords = dict.size(); //Number of words in the dictionary
  vector<int> currentFeature(numWords); //Define a vector whose size is equal to the size of the dictionary.


  for (int i = 0; i < ts.size(); i++){
    populateFeature(ts.at(i), dict, currentFeature);
    //    probabilities(currentFeature);
  }
  //    inornotin(currentFeature);

  for (int i = 0; i < ts.size(); i++)
    for (int j = 0; j < ts.size(); j++)
      cout << ts.at(i).at(j) << endl;
  /*  
 for (int i = 0; i < te.size(); i++)
   populateFeature(te.at(i), dict, currentFeature);
 
 for (int i = 0; i < sp.size(); i++)
   populateFeature(sp.at(i), dict, currentFeature);

 for (int i = 0; i < ep.size(); i++)
   populateFeature(ep.at(i), dict, currentFeature);
  inornotin();
  */
  // string line; // Used to store the line temporarily when reading in the lines from the files.
  //TotalPoems = E + S; // Declare the Total poems after the poems have been counted for each author

  /*     
  */
    return 0;
}
void getFiles ()
{
  
  cout << "Enter the names of the Shakespearean training file, Elizabethan training file, Shakespearean test file and Elizabethan test file (in that order): "; // Asks the user to enter a file for the data
  cin >> inputTrainingShakespeare >> inputTrainingElizabeth
      >> inputTestShakepeare >> inputTestElizabeth;// Gets the input and puts it into a string
}

void inputData ()
{
  string line;
  
  ifstream inputSTraining (inputTrainingShakespeare.c_str()); // Load the poems
  ifstream inputETraining (inputTrainingElizabeth.c_str()); // Load the class E or S
  ifstream inputSTest (inputTestShakepeare.c_str()); // Load the test data
  ifstream inputETest (inputTestElizabeth.c_str());
  ifstream dictionary ("dictionary.txt");

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
      count++;
      while (lineStream >> d)
	srow.push_back(d);
      ts.push_back(srow);
    }

  while (getline (inputETraining, line))
    {
      srow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	srow.push_back(d);
      te.push_back(srow);
    }

  while (getline (inputSTest, line))
    {
      srow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	srow.push_back(d);
      sp.push_back(srow);
    }

  while (getline (inputETest, line))
    {
      srow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	srow.push_back(d);
      ep.push_back(srow);
    }

}


vector<string> split(const string& s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
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

void probabilities(vector<int> currentFeature)
{
    for (unsigned i = 0; i < currentFeature.size(); i++)
    {
      tempS = currentFeature; // Create a temp vector so that we dont change the original probabilities 
	  if (tempS.at(i) == 0)
	    {
	      tempS[i] = 1 - tempS[i] ; // Gets 1-probability
	    }
	  totalProbS *= tempS[i]; // Multiplies all probabilities
    }

    totalProbS = (totalProbS+1)/(currentFeature.size()+2); // Multiplies it by the total probability
    //cout << "Here is the total probs: " << totalProbS;
    tempS.clear(); // Clear the temp so that we can get the original probabilities again when the loop loops
    totalProbS = 1; // Reset the total probability
}


void inornotin(vector<int> currentFeature)
{
    
  // This loop is to go through the shakespeare poems
  for (unsigned i = 0; i < currentFeature.size(); i++)
    {

	  if (currentFeature.at(i) == 1) // Checks to see if the current position has the word in it by denoting that 1 equals word is in the poem
	    f++; // Increment the variable that keeps the number of ones in the column
	  
    }
      cout << "This is f: " << f;
      probs = (f/SPoem.size()); // Gets the probability of ones to zeros
      Sprobability.push_back(probs); // Adds the probability to the vector for shakespeare
      f = 0; // Reset the value
      fNot = 0; // Reset the value
      probs = 0; // Reset the value
    

}

void print()
{
   cout << endl << endl << "Total number of words in dictionary: " << dict.size() << endl;
   cout << "Total sonnet in " << inputTrainingShakespeare << " are: " << ts.size() << endl;
  cout << "Total sonnet in " << inputTrainingElizabeth << " are: " << te.size() << endl;
  cout << endl << endl << "Total sonnet in " << inputTestShakepeare << " are: " << sp.size() << endl;
  cout << "Classification accuracy (/" << sp.size() << ")= " << endl;
  cout << "Total sonnet in " << inputTestElizabeth << " are: " << ep.size() << endl;
  cout << "Classification accuracy (/" << ep.size() << ")= " << endl;
  cout <<  endl << endl << "Combined Classification accuracy (/" << sp.size() + ep.size() << ")= " << endl;
}
