/*
 * Alec Yu
 * CS 368
 * Assignment 0
 *
 * Hello program that takes in the user's name
 * If no name is given, print genaaric Hello message.
 *
 */

#include <iostream>
#include <string>
using namespace std;

/*
 * Prints out a number of * symbols required to make a nice boarder
 */
int printStars ( int length ) 
{
	//loops through and prints a string of * symbols until it has the same 
	//length as the hello message
	for ( int i = 0 ; i < length + 39 ; i = i + 1 )
	{
		cout << "*";
	}

	cout << "\n";

	return 0;

}

/*
 * Prints a star at the front and a star at the end to make a nice boarder
 */
int printSpaces ( int length )
{
	//prints a series of blank spaces to match the length of the hello 
	//message
	cout << "*";

	for ( int j = 0 ; j < length + 37 ; j = j + 1 )
	{
		cout << " ";
	}

	cout << "*\n";

	return 0;

}

/*
 * Main Method:
 * Prompts the user for the name and prints a hello message accordingly
 */
int main ()
{
	//declare and initialize a string for the users name
	string name = "";
	//prompt the user for their name
	cout << "Enter your name: ";	
	//gets their name from the standard input
	getline (cin, name);

	//print a hello message with the name. If no name is provided then 
	//print a genaric hello message
	if ( name.size() > 0)
	{

		cout << "\n";
		printStars ( name.size() );
		printSpaces ( name.size() );
		cout << "* Hello " << name << "! Welcome to CS 368 (C++)! :) *\n";
		printSpaces ( name.size() );
		printStars ( name.size() );
		cout << "\n";

	}

	if ( name.size() == 0 )
	{

		cout << "\n";
		printStars ( -1 );
		printSpaces ( -1 );
		cout << "* Hello! Welcome to CS 368 (C++)! :) *\n";
		printSpaces ( -1 );
		printStars ( -1 );
		cout << "\n";

	}		 

	return 0;	

}
