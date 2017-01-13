///////////////////////////////////////////////////////////////////////////////
// File Name:      Student.cpp
//
// Author:         Alec Yu
// CS email:       ayu@cs.wisc.edu
//
// Description:    Student class containing information about a student
///////////////////////////////////////////////////////////////////////////////

#include "Student.hpp"
#include <time.h>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
//using namespace std;
int Student::numStudents = 0;

/**
 * @brief A parameterised constructor for a Student.
 *
 * @param name Student's name.
 * @param yearOfBirth Student's year of birth.
 * @param assignmentsScore Student's assignment scores.
 * @param projectScore Student's project score.
 */
Student::Student(std::string name,int yearOfBirth,
        const std::vector<double> &assignmentsScore, double projectScore)
{
    Student::name = name;
    Student::yearOfBirth = yearOfBirth;
    Student::assignmentsScore = assignmentsScore;
    Student::projectScore = projectScore;
    //increment the student count
    numStudents++;
    //the student id is the current num students
    id = Student::numStudents;
}

/**
* @brief Getter for student's id.
*
* @return The id of the student.
*/
int Student::getId()
{
    return id;
}

/**
* @brief Getter for student's name.
*
* @return The name of the student.
*/
std::string Student::getName()
{
    return Student::name;
}

/**
* @brief Getter for student's YOB.
*
* @return The YOB of the student.
*/
int Student::getYearOfBirth()
{
    return Student::yearOfBirth;
}

/**
* @brief Get the age of a student.
*
* @return The student's age.
*/
int Student::getAge()
{
    //get the current year
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    int year = aTime->tm_year + 1900;
    
    //return the current year - the birth year
    return year-getYearOfBirth();
}

/**
* @brief Getter for student's assignment scores.
*
* @return A const reference to the vector of student's assignment scores.
*/
const std::vector<double> &Student::getAssignmentsScore()
{
    return Student::assignmentsScore;
}

/**
* @brief Getter for student's project score.
*
* @return The project score of the student.
*/
double Student::getProjectScore()
{
    return Student::projectScore;
}

/**
* @brief Get the total number of students.
*
* @return The total number of students.
*/
int Student::getNumStudents()
{
    return Student::numStudents;
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
void Student::printDetails()
{
    std::cout <<"STUDENT DETAILS:" << std::endl;
    std::vector<double> scores = getAssignmentsScore();
    std::cout << "Id = " << getId() << std::endl;
    std::cout << "Name = " << getName() << std::endl;
    std::cout << "Age = " << getAge() << std::endl;
    std::cout << "Assignments = [";
    for (int i = 0; i < scores.size(); i++)
    {
        std::cout << scores.at(i);
        if (i != scores.size()-1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
    std::cout << "Project = " << getProjectScore() << std::endl;
    std::cout << "Total = " << getTotal() << std::endl;
    std::cout << "Grade = " << getGrade() << std::endl;
}