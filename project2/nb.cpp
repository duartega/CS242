// Authors: Gabriel Duarte and Dakota Bold
// Project 2
// Professor: Gurman Gill
// CS242: Discreet structures
// Description: We will be reading in test data and getting probabilities as well as implementing the naiveBayes theorem

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void getFiles (); // Get the file names
void inputData (); // Input the file data into vectors
void GetColSumProbabilities (vector < vector<int>  > currentFeature, vector<float> &probability); // Counts the words in the column to get the probability
void print(); // Print out the statements
void populateFeature (const vector<string>& sonnet, const vector<string>& dictionary, vector<int>& currentFeature); // Calls checkWord to populate 1's and 0's
int checkWord(string word, const vector<string>& sonnet); // Uses popoulate Feature to see if the word is in the dictionary
void bayes(vector < vector<int> > &shakeTest, vector < vector<int> > &elizTest); // Does the final calculations

string inputTrainingShakespeare; // Declare the string for inputName
string inputTrainingElizabeth; // Decalre the string for inputName
string inputTestShakepeare; // Declare the string for input test for Shakespeare
string inputTestElizabeth; // Declare the string for the input test for elizabeth

vector < vector<int> > SSonnet; // Create a 2D vector for the shakspearean sonnets
vector < vector<int> > ESonnet; // Create a 2D vector for elizabethan sonnets
vector < vector<int> > testDataS;  // Create 2D vector for the shake test data
vector < vector<int> > testDataE;// Create 2D vector for the eliz test data

vector <string> srow; // Vector strinig to push into a 2d array
vector < vector <string> > sp; // Create 2D vector for the input test data
vector < vector <string> > ep; // Create 2D vector for the input test data
vector < vector <string> > ts;// Create 2D vector for the input training data
vector < vector <string> > te;// Create 2D vector for the input training data
vector <string> dict; // Ceate a vector for the dictionary

  
  float TotalSonnetsS = 0; // For the total number of Shakespeare sonnets
  float TotalSonnetsE = 0; // For the total number is Elizabeth Sonnets

  float in = 0; // For total words that are in the dictionary
  float probs = 0; // Gets the Sprobability of the occurence in the sonnet
  float totalProbabilityS = 0; // Gets the total Sprobability for Shakespeare sonnets
  float totalProbabilityE = 0; // Gets the total Sprobability for Elizabeth sonnets
  float likelihood = 0; // To ge the prior likelihood

  vector<float> Sprobability; // Stores the Probabilities of the words turning up in a shakespeare sonnet
  vector<float> Eprobability; // Stores the Probabilities of the words turning up in a Elizabethan sonnet

  int ShakeCounter = 0; // To get Shakespeare classification accuracy counter
  int ElizCounter = 0; // To get Elizabeth classification accuracy counter

int main ()
{
  getFiles(); // ask use for files
  inputData (); // read in the files int vectors of strings
    
  int numWords = dict.size(); //Number of words in the dictionary
  vector<int> currentFeature(numWords); //Define a vector whose size is equal to the size of the dictionary.


  for (int i = 0; i < ts.size(); i++) // Passing the shake training
  {
    populateFeature(ts.at(i), dict, currentFeature); // returning vector of 354 saying words are in or not
    SSonnet.push_back(currentFeature); // Add the current feature vector int another vector
  }
 
  GetColSumProbabilities(SSonnet, Sprobability); // Calls the function to count words that occur

  
  for (int i = 0; i < te.size(); i++){ // Passing the Eliz training
    populateFeature(te.at(i), dict, currentFeature); // Populate the current feature vector
    ESonnet.push_back(currentFeature); // Add the current feature vector int another vector
  }
  
  GetColSumProbabilities(ESonnet, Eprobability); // Calls the function to count words that occur
    
  for (int i = 0; i < sp.size(); i++){ // Passing the Shake Test
   populateFeature(sp.at(i), dict, currentFeature); // Populate the current feature vector
   testDataS.push_back(currentFeature); // Add the current feature vector int another vector
  }
  for (int i = 0; i < ep.size(); i++){ // Passing the Eliz test
    populateFeature(ep.at(i), dict, currentFeature); // Populate the current feature vector
    testDataE.push_back(currentFeature); // Add the current feature vector int another vector
  }

  bayes(testDataS, testDataE); // Make the call to compute the final calculations to naiveBayes theorem
  print(); // Print out the cout statements such as totals and accuracies

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

int checkWord(string word, const vector<string>& sonnet)
{
    //Linear search to check if word exists in the vector sonnet
    for (int i=0; i<sonnet.size(); ++i)
    {
        if (!sonnet[i].compare(word))
            return 1;
    }
    return 0;
}

void GetColSumProbabilities(vector < vector<int> > Sonnet, vector<float> &probability)
{
  // This loop is to go through the shakespeare sonnets
  for (int i = 0; i < dict.size(); i++)
    {
      for (int j = 0; j < Sonnet.size(); j++)

	if (Sonnet.at(j).at(i) == 1) // Checks to see if the current position has the word in it by denoting that 1 equals word is in the sonnet
	   in++; // Increment the variable that keeps the number of ones in the column

      likelihood =(in+1)/(Sonnet.size()+2); // Gets the probability of ones or the probability that the word occurs
      probability.push_back(likelihood); // Adds the probability to the vector for which ever Probability vector us passed in such as shake or eliz
      in = 0; // Reset the value
      likelihood = 0; // Reset the value
    }
}

void bayes(vector < vector<int> > &shakeTest, vector < vector<int> > &elizTest)
{
  TotalSonnetsS = log((float)ts.size()/(ts.size()+te.size())); // Set the total probability for shake
  TotalSonnetsE = log((float)te.size()/(ts.size()+te.size())); // Set the total probability for eliz
  totalProbabilityE = 0; // Reset the value
  totalProbabilityS = 0; // Reset the value

  for (int i = 0; i < shakeTest.size(); i++)
    {
      for (int j = 0; j < dict.size(); j++)
	{
	  if (shakeTest[i][j] == 1) // Compare for the first row
	    {
	      totalProbabilityS += log(Sprobability[j]);
	      totalProbabilityE += log(Eprobability[j]);
	    }
	  else
	    {
	      totalProbabilityS += log(1 - Sprobability[j]); // Saying that the probability is 0
	      totalProbabilityE += log(1 - Eprobability[j]); // Saying that the probability is 0
	    }
	}
      totalProbabilityS += TotalSonnetsS; // Add the total to the probabilities
      totalProbabilityE += TotalSonnetsE; // Add the total to the probabilities

      if (totalProbabilityS > totalProbabilityE) // Compare to see if Shake Probability is bigger
     	ShakeCounter++; // Increment the shake counter

      totalProbabilityS = 0; // Reset the varibale to 0
      totalProbabilityE = 0; // Reset the varibale to 0
    }


  for (int i = 0; i < elizTest.size(); i++)
    {
      for (int j = 0; j < dict.size(); j++)
	{
	  if (elizTest[i][j] == 1) // Compare for the first row
	    {
	      totalProbabilityE += log(Eprobability[j]);
	      totalProbabilityS += log(Sprobability[j]);
	    }
	  if (elizTest[i][j] == 0)
	    {
	      totalProbabilityE += log(1 - Eprobability[j]); // Saying that the probability is 0
	      totalProbabilityS += log(1 - Sprobability[j]); // Saying that the probability is 0
	    }
	 
	}
      
      totalProbabilityE += TotalSonnetsE; // Add the total to the probabilities
      totalProbabilityS += TotalSonnetsS; // Add the total to the probabilities

      if (totalProbabilityE > totalProbabilityS) // Compare to see if Shake Probability is bigger
	ElizCounter++; // Increment the Eliz counter
      totalProbabilityS = 0; // Reset the value
      totalProbabilityE = 0; // Reset the value
    }
}

void getFiles ()
{

  cout << "Enter the names of the Shakespearean training file, Elizabethan training file, Shakespearean test file and Elizabethan test file (in that order): "; // Asks the user to enter a file for the data
  cin >> inputTrainingShakespeare >> inputTrainingElizabeth
      >> inputTestShakepeare >> inputTestElizabeth; // Gets the input and puts it into a string
}

void inputData ()
{
  string line;

  ifstream inputSTraining (inputTrainingShakespeare.c_str()); // Load the training sonnet for Shake
  ifstream inputETraining (inputTrainingElizabeth.c_str()); // Load the training sonnet for Eliz
  ifstream inputSTest (inputTestShakepeare.c_str()); // Load the test data for Shake
  ifstream inputETest (inputTestElizabeth.c_str()); // Load the test data for Eliz
  ifstream dictionary ("dictionary.txt"); // Load the dictionary

  while (getline (dictionary, line)) // Read in the dicitonary
    {
      string  d;
      stringstream lineStream(line);
      while (lineStream >> d)
	dict.push_back(d);
    }

  while (getline (inputSTraining, line))  // Insert the training data into a vector
    {
      srow.clear();
      string  d;
      stringstream lineStream(line);
      while (lineStream >> d)
	srow.push_back(d);
      ts.push_back(srow);
    }

  while (getline (inputETraining, line))  // Insert the training data into a vector
    {
      srow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	srow.push_back(d);
      te.push_back(srow);
    }

  while (getline (inputSTest, line))  // Insert the test data into a vector
    {
      srow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	srow.push_back(d);
      sp.push_back(srow);
    }

  while (getline (inputETest, line))  // Insert the test data into a vector
    {
      srow.clear();
      string d;
      stringstream lineStream(line);
      while (lineStream >> d)
	srow.push_back(d);
      ep.push_back(srow);
    }
}

void print()
{
  // Output the values
  cout << endl << endl << "Total number of words in dictionary: " << dict.size() << endl;
  cout << "Total sonnet in " << inputTrainingShakespeare << " are: " << ts.size() << endl;
  cout << "Total sonnet in " << inputTrainingElizabeth << " are: " << te.size() << endl;

  cout << endl << endl << "Total sonnet in " << inputTestShakepeare << " are: " << sp.size() << endl;
  cout << "Classification accuracy (" << ShakeCounter << "/" << sp.size() << ")= " << (float)(ShakeCounter)/(sp.size())*100 << endl;
  cout << "Total sonnet in " << inputTestElizabeth << " are: " << ep.size() << endl;
  cout << "Classification accuracy (" << ElizCounter << "/" << ep.size() << ")= " << (float)(ElizCounter)/(ep.size())*100 << endl;

  cout << endl << endl << "Combined Classification accuracy (" << ShakeCounter+ElizCounter << "/" << sp.size() + ep.size() << ")= " << (float)(ShakeCounter+ElizCounter)/(sp.size()+ep.size())*100 << endl;
}
