///////////////////////////////////////////////////////////////////////////////
// File Name:      UndergradStudent.cpp
//
// Author:         Alec Yu
// CS email:       ayu@cs.wisc.edu
//
// Description:    Undergrad student class containing information about an 
//                 undergrad student
///////////////////////////////////////////////////////////////////////////////
#include "UndergradStudent.hpp"

#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

int UndergradStudent::numUndergradStudents = 0;

/**
 * @brief Constructor for an undergraduate student.
 *
 * @param name Undergraduate student's name
 * @param yearOfBirth Undergraduate student's YOB
 * @param assignmentsScore Undergraduate student's assignment scores.
 * @param projectScore Undergraduate student's project score.
 * @param residenceHall Undergraduate student's residence hall.
 * @param yearInCollege Undergraduate student's year in college.
 */
UndergradStudent::UndergradStudent(std::string name, int yearOfBirth,
                     const std::vector<double> &assignmentsScore,
                     double projectScore, std::string residenceHall,
                     std::string yearInCollege) : Student(name,yearOfBirth,
                     assignmentsScore,projectScore)
{
    UndergradStudent::residenceHall = residenceHall;
    UndergradStudent::yearInCollege = yearInCollege;
    //increment the number of undergrad students
    ++UndergradStudent::numUndergradStudents;
}

/**
 * @brief Getter for a student's residence hall.
 *
 * @return The residence hall in which the student resides.
 */
std::string UndergradStudent::getResidenceHall()
{
    return residenceHall;
}

/**
 * @brief Getter for a student's year in college.
 *
 * @return The year in college of the student.
 */
std::string UndergradStudent::getYearInCollege()
{
    return yearInCollege;
}

/**
 * @brief Get the total number of undergraduate students.
 *
 * @return The number of undergraduate students.
 */
int UndergradStudent::getNumStudents()
{
    return UndergradStudent::numUndergradStudents;
}

/**
 * @brief Prints the details of the student.
 * 
 * @example This method prints the following details of a student.
 * Id = 10
 * Name = Rex Fernando
 * Age =  19
 * Assignments = [57, 90, 81, 96, 80, 95, 78]
 * Project = 98
 * Total = 90.2143
 * Grade = CR
 */
void UndergradStudent::printDetails()
{
    Student::printDetails();
    std::cout << "Type = Undergraduate Student" << std::endl;
    std::cout << "Residence Hall = " << getResidenceHall() << std::endl;
    std::cout << "Year in College = " << getYearInCollege() << std::endl;
}

/**
 * @brief Get the total score of a student.
 *
 * @return The total score of the student.
 */
double UndergradStudent::getTotal()
{
    double total = 0.0;
    std::vector<double> scores = getAssignmentsScore();
    //go through all the scores and add it to the total
    for (int i = 0; i < scores.size() ; i++)
    {
        total += scores.at(i);
    }
    //divide by amount of scores to get average
    total /= scores.size();
    
    return 0.7*total+0.3*getProjectScore();
}

/**
 * @brief Get the letter grade obtained by a student.
 *
 * @return The letter grade of the student. The possible letter grades are "CR" and "N".
 */
std::string UndergradStudent::getGrade()
{
    if (getTotal() >=70)
        return "CR";
    else
        return "N";
}