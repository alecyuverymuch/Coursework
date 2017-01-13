///////////////////////////////////////////////////////////////////////////////
// File Name:      processStudent.cpp
//
// Author:         Alec
// CS email:       ayu@cs.wisc.edu
//
// Description:    Methods to perform some processing on student objects.
///////////////////////////////////////////////////////////////////////////////

#include "processStudent.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

/**
 * @brief Read students' data from an input file and store them in 2 vectors
 *        based on the type of the student.
 *
 * @param inFile The input file with students' data.
 * @param gstudents Vector of graduate students.
 * @param ugstudents Vector of undergraduate students.
 */
void fillStudents(std::ifstream &inFile,
                  std::vector<GradStudent> &gstudents,
                  std::vector<UndergradStudent> &ugstudents) {

    std::string str;
    //go through every line
    while (std::getline(inFile,str))
    {
        //get information from the current line by getting the contents up to 
        //the first comma then deleting until the comma
        std::string type = str.substr(0,str.find(','));
        str.erase(0,str.find(',')+1);
        std::string name = str.substr(0,str.find(','));
        str.erase(0,str.find(',')+1);
        std::string yob = str.substr(0,str.find(','));
        str.erase(0,str.find(',')+1);
        //parse the year to an int
        int yearOfBirth = stoi(yob);
        std::vector<double> assignmentsScore;
        
        //get the assignment scores, parse them into doubles and add them to the
        //array
        for (int i = 0 ; i < 7 ; i++)
        {
            std::string score = str.substr(0,str.find(','));
            str.erase(0,str.find(',')+1);
            double scr = stod(score);
            assignmentsScore.push_back(scr);
        }
        //get the project score then parse it to a double
        std::string project = str.substr(0,str.find(','));
        str.erase(0,str.find(',')+1);
        double projectScore = stod(project);
        //if the type is U, then add an undergrad student to the array using 
        //the array given by the line
        if (type == "U")
        {
            std::string residenceHall = str.substr(0,str.find(','));
            str.erase(0,str.find(',')+1);
            std::string yearInCollege = str;
            ugstudents.push_back(UndergradStudent(name,yearOfBirth,
                    assignmentsScore,projectScore,residenceHall,yearInCollege));
        }
        //if the type is G, then add a grad student to the array using the array
        //given by the line
        else 
        {
            std::string researchArea = str.substr(0,str.find(','));
            str.erase(0,str.find(',')+1);
            std::string advisor = str;
            gstudents.push_back(GradStudent(name,
                    yearOfBirth,assignmentsScore,projectScore,researchArea,
                    advisor));
        }
    }

}

void printStudents(const std::vector<std::reference_wrapper<Student>> &students) 
{

    //go through every student and print the details
    for (int i = 0 ; i < students.size() ; i++)
    {
        students.at(i).get().printDetails();
        std::cout<<std::endl;
    }
}

void computeStatistics(std::vector<std::reference_wrapper<Student>> &students) {

    // TODO: Implement this method.

    // compute the # of students based on the type of students.

    // compute the mean of the total score.

    // sort and print the students based on their total.
    
    std::cout << "Number of students = " << students.size() << std::endl;
    double mean = 0.0;
    for (int i = 0 ; i < students.size() ; i++)
    {
        //add all the total scores from all the students to the mean
        mean += students.at(i).get().getTotal();
    }
    //divide by the total number of students
    mean /= students.size();
    
    std::cout << "The mean of the total score = " << mean <<std::endl;
    std::cout << "The sorted list of students (id, name, total, grade) in " <<
            "descending order of total:" << std::endl;
    
    //sort the students
    std::sort(students.begin(),students.end(),[](Student &s1, Student &s2)
		{return s1.getTotal() > s2.getTotal();});
    //print the info about the students
    for (int j = 0 ; j < students.size() ; j++)
    {
        std::cout << students.at(j).get().getId() << ", " << 
                students.at(j).get().getName() << ", " << 
                students.at(j).get().getTotal() << ", " << 
                students.at(j).get().getGrade() << std::endl;
    }
    std::cout<<std::endl;
}

