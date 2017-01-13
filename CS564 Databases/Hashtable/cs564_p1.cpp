/*
 * CS 564 Project 1: Reviewing C++ Programming
 * 
 * Alec Yu
 * 
 * Implements a hash table. Accepts a data file in a csv format and puts it into
 * a hash table. The table originally starts with a size a 13 but as more slots 
 * get filled, it dynamically adds more. Then outputs a datafile with the keys 
 * of the entries along with the average of all the column 2 values and the max 
 * of the column  values.
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <iomanip>
using namespace std;


/*
 * Entry
 * 
 * Represents an entry in the table containing a key as a string and 2 integer
 * values contained in an array
 * 
 */
class Entry 
{
        string key;
        int c[2];
    public:        
        Entry( string , int , int );
        string get_key();
        int get_c1();
        int get_c2();
};

/*
 * Entry Constructor
 * 
 * Builds a new Entry
 * 
 * @param 
 * entrystr: a string for the entrys key - column 1 of the data file
 * v1: first int value - column 2
 * v2: second int value - column 3;
 * 
 */
Entry::Entry( string entrystr , int v1 , int v2 )
{
    key = entrystr;
    c[0] = v1;
    c[1] = v2;
}

/*
 * Entry get_key
 * 
 * @return 
 * key: string of the entry
 */
string Entry::get_key()
{
    return key;
}

/*
 * Entry get_c1
 * 
 * @return 
 * c[0] - the first int
 */
int Entry::get_c1()
{
    return c[0];
}

/*
 * Entry get_c2
 * 
 * @return
 * c[1] - the second int
 */
int Entry::get_c2()
{
    return c[1];
}

/*
 * hash_function
 * 
 * returns an integer hash index in accordance to the tablesize
 * 
 * @param
 * str - string to hash
 * tablesize - size of the table (bounds)
 * 
 * @return
 * hash index
 */
int hash_function ( string str , int tablesize)
{
    return (hash<string>{}(str) % tablesize);
}

/*
 * main
 * 
 * Creates and runs the hashtable. Outputs the data file. 
 * Accepts the name of the .dat file to read from the command line
 */
int main ( int argc , char* argv[] )
{
    //declare variables for use
    ifstream file;
    string filename , line , str, num1 , num2 ;
    //start with an initial table size of 13
    int value1 = 0, value2 = 0, occupied = 0, tablesize = 13;
    
    //create the hash table as a 2 dimentional vector of Entrys
    vector<vector<Entry>> hashtable ( tablesize , vector<Entry>() );
    
    //set the fill threshold to 0.7
    double threshold = 0.7;
    
    //get the filename from the command line parameters and open it
    filename = argv[1];
    file.open(filename);
    if (file.is_open())
    {
        
        //go through every line of the file
        while ( getline ( file , line ) )
        {
            //get the key from col 1, and 2 int values from cols 2 and 3
            if (line.find(',') != 0)
                str = line.substr( 0 , line.find(',') );
            else
                str = "";
            line.erase( 0 , line.find(',') + 1 );
            if (line.find(',') == 0)
                value1 = 0;
            else
                value1 = stoi( line.substr( 0 , line.find(',') ) );
            line.erase( 0 , line.find(',') + 1 );     
            if (line.find(',') == 0)
                value2 = 0;
            else
                value2= stoi( line.substr( 0 , line.find(',') ) );
            line.erase( 0 , line.find(',') + 1 ); 
            
            //create a hash key from the Entrys string
            int key = hash_function( str, tablesize );
            
            //if the bucket at the key index is empty, add the new entry to the bucket
            if ( hashtable[key].size() == 0 )
            {
                occupied++;
                hashtable[key].resize( hashtable[key].size() + 1 , Entry ( str , value1 , value2 ) );
            }
            else
            {
                //if the bucket at the key index contains entrys of the same key, then add the new entry to the end
                if ( hashtable[key][0].get_key() == str )
                {
                    hashtable[key].resize( hashtable[key].size() + 1 , Entry ( str , value1 , value2 ) );
                }
                else
                {
                    //increment the key index until you find a bucket with the same keys, then add the entry
                    while ( hashtable[key][0].get_key() != str )
                    {
                        key = (key + 1) % tablesize;
                        if ((hashtable[key].size()) == 0) 
                            break;
                    }
                    occupied++;
                    hashtable[key].resize( hashtable[key].size() + 1 , Entry ( str , value1 , value2 ) );
                }
            }
            //if 70% or more of the table is filled resize the table
            if (( (double)occupied / (double)tablesize ) >= threshold )
            {
                //double the size of the table
                int oldsize = tablesize;
                tablesize = tablesize*2;
                hashtable.resize(tablesize);
                
                //create a new hash table
                vector<vector<Entry>> newtable ( tablesize , vector<Entry>() );
                
                //go through old hashtable and map each row to a location in the new table
                for (int i = 0 ; i < oldsize ; i++ )
                {   
                    //if the current row contains data, hash the key for the row and add it to the new table
                    if ( hashtable[i].size() !=0 )
                    {
                        key = hash_function(hashtable[i][0].get_key() , tablesize );
                        while (newtable[key].size() != 0)
                        {
                            key = (key + 1) % tablesize;   
                        }
                        newtable[key] = hashtable[i];
                        hashtable[i] = vector<Entry>();
                    }
                }
                
                //replace the old table with the new table
                hashtable = newtable;
            }
        }
        //output the following data to a file called "output.dat"
        ofstream output;
        output.open("output.dat");

        //go through the table
        for (int i = 0 ; i < tablesize ; i++)
        {
            //if the current row has data, print its information
            if ( hashtable[i].size() != 0 )
            {
                //print the key
                string key = hashtable[i][0].get_key();

                int max = hashtable[i][0].get_c2();
                double average = 0;

                //loop through all the elements and get the average for c1 and max for c2
                for ( int j = 0 ; j < (int)hashtable[i].size() ; j++)
                {
                    average += hashtable[i][j].get_c1();
                    if (hashtable[i][j].get_c2() > max)
                        max = hashtable[i][j].get_c2();
                }
                average = average / (double) hashtable[i].size();

                //if no average or max data, leave as blank space
                if (average == 0)
                {
                    output << key << "\t|\t\t\t| ";
                    if (max == 0)
                        output << endl;
                    else 
                        output << max << endl;
                }
                //output the info
                else
                    output << key << "\t| " << std::fixed << std::setprecision(12) << average << "\t| " << max << endl;
            }
        }
        //close the output 
        output.close();
        }
    //close the file
    file.close();
    
    
}
