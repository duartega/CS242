//
//  sample.cpp
//
//
//  Created by Gurman Gill on 11/17/17.
//  Copyright © 2017 Gurman Gill. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

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

int main(int argc, const char * argv[]) {

    
    //Define a random dictionary. (For the project 2, you will be reading the actual dictionary from a file)
    string dictionary = "these are some words in a dictionary";
    vector<string> dictWords = split(dictionary, ' '); //Creates a vector of strings = { "these", "are", "some", "words","in", "a", "dictonary" };
    
    //Define a random sonnet. (For the project 2, you will be reading actual sonnets from some files)
    string sonnet = "a sonnet with five words";
    vector<string> sonnetWords = split(sonnet, ' '); //Creates a vector of sonnet = {"a", "sonnet", "with", "five", "words"}
    
    int numWords = dictWords.size(); //Number of words in the dictionary
    
    //Define a vector whose size is equal to the size of the dictionary.
    vector<int> currentFeature(numWords);
    
    // Populate currentFeature with 1's and 0's indicating the presence/absence of dictionary words in the sonnet
    populateFeature(sonnetWords, dictWords, currentFeature);
    
    //Print out the feature vector
    for (int i=0; i<numWords; ++i)
    {
        cout << currentFeature[i] << " ";
    }
    cout << endl;
    
        return 0;
}
