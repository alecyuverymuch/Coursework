#!/bin/bash

# Constants
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_DIR=~gerald/public/html/cs368/assignments/a3
LIB_DIR=/p/course/cs368-gerald/public/libraries
VALID_ARGS=("BasicStudentTest" "BasicUndergradStudentTest" "BasicGradStudentTest" "BasicProcessStudentTest" "AdvancedStudentTest" "AdvancedUndergradStudentTest" "AdvancedGradStudentTest" "AdvancedProcessStudentTest")

cd $DIR

if (($# == 0)); then
    (<&2 echo "Warning: no arguments specified.")
    (<&2 echo "USAGE: ./test.sh <TEST1> <TEST2> ...")
    (<&2 echo "Only performing preliminary checks.")
fi

# Exit if necessary files do not exist
flag=0
for file in "GradStudent.cpp" "GradStudent.hpp" "main.cpp" "processStudent.cpp" "processStudent.hpp" "Student.cpp" "Student.hpp" "students.txt" "test.c" "UndergradStudent.cpp" "UndergradStudent.hpp"; do
    if [ ! -f "./$file" ]; then
        (<&2 echo "Could not find $file")
        flag=1
    fi
done
if ((flag == 1)); then
    exit 1
fi

# Print warning messages if files have been changed
for file in "GradStudent.hpp" "main.cpp" "processStudent.hpp" "students.txt" "UndergradStudent.hpp"; do
    cmp "$CODE_DIR/$file" "$DIR/$file"
done

# Basic checks for Student.hpp
PUBLIC_COUNT=$(grep -o "public" ./Student.hpp | wc -l)
PROTECTED_COUNT=$(grep -o "protected" ./Student.hpp | wc -l)
PRIVATE_COUNT=$(grep -o "private" ./Student.hpp | wc -l)
FRIEND_COUNT=$(grep -o "friend" ./Student.hpp | wc -l)
NUM_STUDENTS_COUNT=$(grep -o "static int numStudents" ./Student.hpp | wc -l)
flag=0
if ((PUBLIC_COUNT == 0)); then
    (<&2 echo "Could not find public section of Student class")
    flag=1
fi
if ((PUBLIC_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"public\" in Student.hpp")
    flag=1
fi
if ((PROTECTED_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"protected\" in Student.hpp")
    flag=1
fi
if ((PRIVATE_COUNT == 0)); then
    (<&2 echo "Could not find private section of Student class")
    flag=1
fi
if ((PRIVATE_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"private\" in Student.hpp")
    flag=1
fi
if ((FRIEND_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"friend\" in Student.hpp")
    flag=1
fi
if ((NUM_STUDENTS_COUNT == 0)); then
    (<&2 echo "Could not find line \"static int numStudents\" in Student.hpp")
    flag=1
fi
if ((NUM_STUDENTS_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the line \"static int numStudents\" in Student.hpp")
    flag=1
fi
if ((flag == 1)); then
    (<&2 echo "Please fix the above errors in Student.hpp, exiting")
    exit 1
fi

# More advanced checks for Student.hpp
cmp <(head -n32 "$CODE_DIR/Student.hpp") <(head -n32 ./Student.hpp) > /dev/null 2>&1
status=$?
if ((status != 0)); then
    (<&2 echo "Warning: changes to first 32 lines of Student.hpp")
fi
cmp <(tail -n93 "$CODE_DIR/Student.hpp") <(tail -n93 ./Student.hpp) > /dev/null 2>&1
status=$?
if ((status != 0)); then
    (<&2 echo "Warning: changes to last 93 lines of Student.hpp")
fi
MODIFIED=$(tail -n+33 ./Student.hpp | head -n-93)
BRACE_COUNT=$(echo $MODIFIED | grep -o "}" | wc -l)
if ((BRACE_COUNT > 0)); then
    (<&2 echo "Warning: found $BRACE_COUNT occurrences of \"}\" in modified section of Student.hpp. Make sure the implementations of all methods are in Student.cpp.")
fi
SEMICOLON_COUNT=$(echo $MODIFIED | grep -o ";" | wc -l)
FUNCTION_COUNT=$(echo $MODIFIED | grep -o ") *;" | wc -l)
if ((FUNCTION_COUNT < SEMICOLON_COUNT)); then
    (<&2 echo "Warning: found $SEMICOLON_COUNT occurrences of \";\" and $FUNCTION_COUNT occurrences of \")\" followed by \";\" in modified section of Student.hpp. You may only define new methods, not new instance variables, in Student.hpp.")
fi

# Exit if code does not compile
CODE_FILES="./GradStudent.cpp ./processStudent.cpp ./Student.cpp ./UndergradStudent.cpp"
g++ -std=c++11 $CODE_FILES ./main.cpp -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Could not compile code, exiting")
    exit $status
fi
rm -rf ./test

# Compile unit tests, or exit if they do not compile
INCLUDE="$LIB_DIR/googletest/googletest/include/"
FILES="$CODE_FILES ./test.c $LIB_DIR/libgtest.a"
g++ -std=c++11 -isystem $INCLUDE -pthread $FILES -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Could not create test file, exiting")
    exit $status
fi

# Run unit tests
passed_test_count=0
test_count=0
for arg in "$@"; do
    flag=0
    for valid_arg in ${VALID_ARGS[@]}; do
        if [ "$arg" == "$valid_arg" ]; then
            ((test_count += 1))
            flag=1
        fi
    done
    if ((flag == 0)); then
        echo "$arg is not a valid test, ignoring"
    else
        ./test --gtest_filter="A3Test.$arg"
        status=$?
        if ((status == 0)); then
            ((passed_test_count += 1))
        fi
    fi
    echo
done
rm -rf ./test

# Success (possibly)
echo "$passed_test_count/$test_count tests passed"
if (($passed_test_count < $test_count)); then
    exit 1
else
    exit 0
fi
