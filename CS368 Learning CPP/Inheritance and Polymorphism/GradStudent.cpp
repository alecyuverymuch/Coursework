///////////////////////////////////////////////////////////////////////////////
// File Name:      GradStudent.cpp
//
// Author:         Alec Yu
// CS email:       ayu@cs.wisc.edu
//
// Description:    Graduate student class containing information about a
//                 graduate student
///////////////////////////////////////////////////////////////////////////////
#include "GradStudent.hpp"

#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

int GradStudent::numGradStudents = 0;

/**
 * @brief Constructor for a graduate student.
 *
 * @param name Graduate student's name.
 * @param yearOfBirth Graduate student's YOB.
 * @param assignmentsScore Graduate student's assignment scores.
 * @param projectScore Graduate student's project score.
 * @param researchArea Graduate student's research area.
 * @param advisor Graduate student's advisor.
 */
GradStudent::GradStudent(std::string name, int yearOfBirth,
            const std::vector<double> &assignmentsScore, double projectScore,
            std::string researchArea, std::string advisor) : 
            Student(name,yearOfBirth,assignmentsScore,projectScore)
{
    //increment the number of grad students
    ++GradStudent::numGradStudents;
    GradStudent::researchArea = researchArea;
    GradStudent::advisor = advisor;
}

/**
 * @brief Getter for the student's research area.
 *
 * @return The research area of the student.
 */
std::string GradStudent::getResearchArea()
{
    return researchArea;
}

/**
 * @brief Getter for the student's advisor.
 *
 * @return The advisor of the student.
 */
std::string GradStudent::getAdvisor()
{
    return advisor;
}

/**
 * @brief Get the total number of graduate students.
 *
 * @return The number of graduate students.
 */
int GradStudent::getNumStudents()
{
    return GradStudent::numGradStudents;
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
void GradStudent::printDetails()
{
    Student::printDetails();
    std::cout << "Type = Graduate Student" << std::endl;
    std::cout << "Research Area = " << getResearchArea() << std::endl;
    std::cout << "Advisor = " << getAdvisor() << std::endl;
}

/**
 * @brief Get the total score of a student.
 *
 * @return The total score of the student.
 */
double GradStudent::getTotal()
{
    double total = 0.0;
    std::vector<double> scores = getAssignmentsScore();
    //get the average of the scores
    for (int i = 0; i < scores.size() ; i++)
    {
        total += scores.at(i);
    }
    total /= scores.size();
    
    return 0.5*total+0.5*getProjectScore();
}

/**
 * @brief Get the letter grade obtained by a student.
 *
 * @return The letter grade of the student. The possible letter grades are "CR" and "N".
 */
std::string GradStudent::getGrade()
{
    if (getTotal() >=80)
        return "CR";
    else
        return "N";
}