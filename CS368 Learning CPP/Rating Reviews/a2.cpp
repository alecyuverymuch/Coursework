////////////////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Alec Yu
// CS email:       ayu@cs.wisc.edu
//
// Description:    The source file for a2.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A2.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions/methods.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
////////////////////////////////////////////////////////////////////////////////

#include "a2.hpp"
#include "trim.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/**
 * cleans the given file
 * @param inFile input file
 * @param outFile output file
 * @param stopwords list of stopwords to remove
 */
void cleanData(std::ifstream &inFile, std::ofstream &outFile,
               std::unordered_set<std::string> &stopwords) {
    // # of lines of code in Gerald's implementation: 13
    // Do the following operations on each review before
    // storing it to the output file:
    //   1. Replace hyphens with spaces.
    //   2. Split the line of text into individual words.
    //   3. Remove the punctuation marks from the words.
    //   4. Remove the trailing and the leading whitespaces in each word.
    //   5. Remove the empty words.
    //   6. Remove words with just one character in them. You should NOT remove
    //      numbers in this step because if you do so, you'll lose the ratings.
    //   7. Remove stopwords.
	std::string line;
	//goes through every line
	while (std::getline(inFile,line))
	{
		std::vector<std::string> rawWords , cleanWords;
		replaceHyphensWithSpaces(line);
		splitLine(line,rawWords);
		removePunctuation(rawWords,cleanWords);
		removeWhiteSpaces(cleanWords);
		removeEmptyWords(cleanWords);
		removeSingleLetterWords(cleanWords);
		removeStopWords(cleanWords,stopwords);
		for(int i = 0 ; i < cleanWords.size() ; i++)
		{
			outFile << cleanWords[i] << " ";
		}
		outFile<<std::endl;
	}
	outFile.close();
}

/**
 * fills the dictionary
 * @param newInFile
 * @param dict
 */
void fillDictionary(std::ifstream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
	std::string line , word;
	std::pair<std::string, std::pair<long, long>> pair;
	std::pair<long, long> currPair;
	int rating = 0;
	bool ratingCheck;
	std::vector<std::string> check;
	//go through every line in the file
	while (std::getline(newInFile, line))
	{
		rating = 0;
		check.clear();
		std::stringstream str(line);
		//go through every word in the line
		for (int i = 0; str >> word; i++)
		{
			//the the rating from the first word
			if (i == 0)
			{
				rating = std::stoi(word);
			}
			//if the word is not in the dictionary, add it
			if (dict.find(word) == dict.end()) {
				currPair = std::make_pair<long, long>((long) rating, 1);
				dict.insert({word, currPair});
			}
			//if the word is in the dictionary, update the information
			else
			{
				currPair = dict.find(word)->second;
				currPair.second = currPair.second + 1;
				if (std::find(check.begin(), check.end(), word) == check.end())
				{
					currPair.first += (long)rating;
				}
				dict[word] = currPair;
			}
		}
	}
	newInFile.close();
}

/**
 * fills up a set with the stopwords
 * @param inFile - file of stopwords
 * @param stopwords - set of stopwords to fill
 */
void fillStopWords(std::ifstream &inFile,
                   std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
	//go through every line and add the line to the set
	std::string line;
	while (std::getline(inFile, line))
	{
		stopwords.insert(line);
	}
}

/**
 * get the ratings from the file and output a file of the average ratings
 * @param testFile - file to read from
 * @param dict - dictionary
 * @param ratingsFile - file to output to
 */
void rateReviews(std::ifstream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ofstream &ratingsFile) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
	//go through every line
	std::string line;
	while(std::getline(testFile,line))
	{
		int count = 0;
		double rating = 0;
		std::string word;
		std::stringstream str(line);
		//go through every word in the line
		for (int i = 0 ; str>>word ; i++)
		{
			count++;
			//if the current word is not in the dictionary, add 2 to the rating;
			if (dict.find(word) == dict.end())
			{
				rating+=2;
			}
			//get the rating for the word and add it to the total rating
			else
			{
				std::pair<long,long> pair;
				pair = dict.find(word)->second;
				rating += ((double)pair.first/(double)pair.second);
			}
		}
        //get the average rating and output it
		rating /= count;
		ratingsFile << rating << std::endl;
	}
	ratingsFile.close();
}

/**
 * removes strings of length 0
 * @param tokens vector of strings
 */
void removeEmptyWords(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
	for(int i = 0; i < tokens.size() ; i++)
	{
        //remove elements withs size 0
		if (tokens[i].size() == 0)
		{
			tokens.erase(tokens.begin()+i);
			i--;
		}
	}
}

/**
 * removes punctiation from strings in a vector
 * @param inTokens input vector
 * @param outTokens output vector
 */
void removePunctuation(std::vector<std::string> &inTokens,
                       std::vector<std::string> &outTokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
	for(int i = 0; i < inTokens.size() ; i++)
	{
        //remove all punctuation from every string
		std::string output;
		std::remove_copy_if(inTokens[i].begin(), inTokens[i].end(), std::back_inserter(output),
							std::ptr_fun<int, int>(&std::ispunct));
		inTokens[i] = output;
    	outTokens = inTokens;
    }
}

/**
 * removes non numberic strings of length 1
 * @param tokens vector of strings
 */
void removeSingleLetterWords(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5

	for(int i = 0; i < tokens.size() ; i++)
	{
        //if size is one and its not a number remove it
		if (tokens[i].size() == 1 )
		{
			if (!isdigit(tokens[i][0]))
			{
				tokens.erase(tokens.begin() + i);
				i--;
			}
		}
	}
}

/**
 * remove all the stopwords from the vector
 * @param tokens vector of strings
 * @param stopwords set of stopwords
 */
void removeStopWords(std::vector<std::string> &tokens,
                     std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
	for (int i = 0 ; i < tokens.size() ; i++)
	{
        //if the current word is in the set of stopwords, remove it from the vector
		if (stopwords.find(tokens[i]) != stopwords.end())
		{
			tokens.erase(tokens.begin()+i);
			i--;
		}
	}
}

/**
 * removes all white spaces
 * @param tokens vector if strings
 */
void removeWhiteSpaces(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    // You may want to use the trim() method from the trim.*pp files in a2.
    //use trim to remove all the whitespace
	for(int i = 0; i < tokens.size() ; i++)
	{
		tokens[i] = trim(tokens[i]);
	}
}

/**
 * replaces all hyphens with spaces
 * @param line line to edit
 */
void replaceHyphensWithSpaces(std::string &line) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
	std::replace( line.begin() , line.end() , '-' , ' ' );
}

/**
 * turns a line of words into a vector
 * @param line
 * @param words
 */
void splitLine(std::string &line, std::vector<std::string> &words) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
	std::stringstream str(line);
	std::string word;
    //split the line by spaces and add every word to the vector
	while (getline(str, word, ' '))
	{
		words.push_back(word);
	}
}

