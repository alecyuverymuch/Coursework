////////////////////////////////////////////////////////////////////////
// File Name:      a1.cpp
//
// Author:         Alec Yu
// CS email:       ayu@cs.wisc.edu
// 
// Course:         CS 368 (C++)
// Section:        1
// Instructor:     Gerald         
//
// Description:    Reads in 2 data files of names and gets a list of the 
//                 intersection between them and a list of the union. Then
//                 it prints out a series of information regarding the 
//                 information. Then it outputs the intersection and union
//                 in a .txt file
//         
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief outputs a .txt file of a given vector of names
 * 
 * @param list - list of names to output
 * 
 * @param filename - name of the file to output to
 */
void outlist ( vector<string> list , string filename )
{
    ofstream output;
    output.open( filename.c_str() );
    for ( int i = 0 ; i < list.size() ; i ++ )
    {
        output << list[i] << endl;
    }
    output.close();
}

/**
 * @brief prints out the contents of a vector to the console
 * 
 * @param list - list to be printed out
 */
void printlist ( vector<string> list )
{
    for ( int i = 0 ; i < list.size() ; i ++ )
    {
        cout << list[i] << endl;
    }
    cout << endl;
}

/**
 * @brief main method runs the program. First reads in file contents into 
 * vectors then prints the number of items in the two files, then prints the 
 * contents of the intersection, outputs the data to .txt files and then prints 
 * a message regarding the information in the .txt files.
 * 
 * @return 0 
 */
int main () 
{
    //declare varaibles
    string filename1 , filename2 , str , f1, f2;
    vector<string> names1 , names2 , names_intersection , names_union;
    ifstream file;
    
    //get the information from 2 lists given by the user
    for ( int i = 0 ; i < 2 ; i++ )
    {
        do 
        {
            //open the first file
            if ( i == 0 )
            {
                cout << "Enter the name of the first file: ";
                getline ( cin , filename1 );
                f1 = filename1 + ".txt";
                file.open ( f1.c_str() );
            }
            //open the second file
            if ( i == 1 )
            {
                cout << "Enter the name of the second file: ";
                getline ( cin , filename2 );
                f2 = filename2 + ".txt";
                file.open ( f2.c_str() );
            }
            //read through the current file and insert the information into
            //a vector
            if ( file.is_open() )
            {
                while ( getline ( file , str ) )
                {
                    if ( i == 0 )
                        names1.push_back( str );
                    if ( i == 1 )
                        names2.push_back( str );
                }
            }
            //if the given filename is invalid, print an error message
            else 
            {
                if ( i == 0)
                    cout << "Input file " << filename1 << " is NOT found. " <<
                            "Please try again." << endl;
                if ( i == 1)
                    cout << "Input file " << filename2 << " is NOT found. " <<
                            "Please try again." << endl;
            }
        //loop if the file is not correct
        } while ( !file.is_open() );
        //close the file
        file.close();
    }
    cout << endl;
    
    //sort the 2 vectors
    sort( names1.begin() , names1.end() );
    sort( names2.begin() , names2.end() );
    
    //create a vector for the intersection and a vector for the union adding 
    //into them from the back
    set_intersection ( names1.begin() , names1.end() , names2.begin() , 
            names2.end() , back_inserter( names_intersection ));
    set_union ( names1.begin() , names1.end() , names2.begin() , names2.end() , 
            back_inserter( names_union ) );
    
    //print out a message saying the number of students in each of the vectors
    cout << "Number of students in " << filename1 << " = " << names1.size() << 
            endl;
    cout << "Number of students in " << filename2 << " = " << names2.size() << 
            endl;
    cout << "Number of students that are present in BOTH " << filename1 << 
            " AND " << filename2 << " = " << names_intersection.size() << endl;
    cout << "Number of students that are present in EITHER " << filename1 <<
            " OR " << filename2 << " = " << names_union.size() << "\n" << endl;

    //if there is information in the intersection vector, print the contents 
    if ( names_intersection.size() != 0 )
    {
        cout << "List of students that are present in BOTH " << filename1
                << " AND " << filename2 << ":" << endl;
        printlist( names_intersection );
    }
    
    //output the intersection and union into .txt files named intersection and 
    //union respectively
    outlist ( names_intersection , "intersection.txt" );
    outlist ( names_union , "union.txt" );
    
    //print a message acknowledging that the intersection has been output
    if ( names_intersection.size() == 0 )
    {
        cout << "The file intersection.txt is EMPTY since there are no " << 
                "students that are present in BOTH " << filename1 << " AND "
                << filename2 << endl;
    }
    else
    {
        cout << "The names of the " << names_intersection.size() << 
                " students that are present in BOTH " << filename1 << " AND " <<
                filename2 << " are written to the file named intersection.txt" 
                << endl;
    }

    //prints a message acknowledging that the union has been output
    if ( names_union.size() == 0 )
    {
        cout << "The file union.txt is EMPTY since there are no " << 
                "students in the 2 files " << filename1 << " AND " << filename2 
                << endl;
    }
    else
    {
        cout << "The names of the " << names_union.size() << " students that" <<
                " are present in EITHER " << filename1 << " OR " << filename2 <<
                " are written to the file named union.txt" << endl;
    }
    return 0;
}
