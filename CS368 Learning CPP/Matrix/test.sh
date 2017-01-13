#!/bin/bash

# Constants
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_DIR=~gerald/public/html/cs368/assignments/a4
LIB_DIR=/p/course/cs368-gerald/public/libraries
VALID_ARGS=("BasicMatrixTest" "ConstMatrixTest" "BasicBracketTest" "ConstBracketTest" "BasicPrintTest" "ConstPrintTest" "BasicComparisonTest" "ConstComparisonTest" "MismatchedComparisonTest" "BasicAdditionTest" "ConstAdditionTest" "MismatchedAdditionTest" "BasicSubtractionTest" "BasicMatrixMultiplicationTest" "BasicScalarMultiplicationTest" "BasicCompoundAdditionTest" "ConstCompoundAdditionTest" "BasicCompoundSubtractionTest" "BasicCompoundMatrixMultiplicationTest" "BasicCompoundScalarMultiplicationTest" "ComplexTest")

cd $DIR

if (($# == 0)); then
    (<&2 echo "Warning: no arguments specified.")
    (<&2 echo "USAGE: ./test.sh -t=[true|false] <TEST1> <TEST2> ...")
    (<&2 echo "Only performing preliminary checks.")
else
    # https://stackoverflow.com/questions/192249/how-do-i-parse-command-line-arguments-in-bash
    flag=0
    tests=()
    TEMPLATE=-1
    for i in "$@"
    do
        case $i in 
            -t=*|--template=*)
                t="${i#*=}"
                if [[ "$t" == "true" ]]; then
                    TEMPLATE=1
                elif [[ "$t" == "false" ]]; then
                    TEMPLATE=0
                else
                    (<&2 echo "Template flag \"$t\" is invalid, must be true or false")
                    flag=1
                fi
                shift
                ;;
            -*)
                (<&2 echo "Argument \"$i\" is invalid")
                flag=1
                ;;
            *)
                tests+=("$i")
                ;;
        esac
    done
    if ((TEMPLATE == -1)); then
        (<&2 echo "Did not specify -t=true or -t=false")
        flag=1
    fi
    if ((flag == 1)); then
        (<&2 "Errors in arguments, exiting")
        exit 1
    fi
fi

# Exit if necessary files do not exist
flag=0
for file in "main.cpp" "Matrix.hpp"; do
    if [ ! -f "./$file" ]; then
        (<&2 echo "Could not find $file")
        flag=1
    fi
done
if ((flag == 1)); then
    exit 1
fi

# Print warning messages if files have been changed
cmp "$CODE_DIR/main.cpp" "$DIR/main.cpp"

# Basic checks for Matrix.hpp
MUTABLE_COUNT=$(grep -o "mutable" ./Matrix.hpp | wc -l)
VOLATILE_COUNT=$(grep -o "volatile" ./Matrix.hpp | wc -l)
CLASS_COUNT=$(grep -o "class" ./Matrix.hpp | wc -l)
flag=0
if ((MUTABLE_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"mutable\" in Matrix.hpp")
    flag=1
fi
if ((VOLATILE_COUNT > 0)); then
    (<&2 echo "There are more than 0 occurrences of the word \"volatile\" in Matrix.hpp")
    flag=1
fi
if ((CLASS_COUNT == 0)); then
    (<&2 echo "There are 0 occurrences of the word \"class\" in Matrix.hpp")
    flag=1
fi
if ((CLASS_COUNT > 1)); then
    (<&2 echo "There is more than 1 occurrence of the word \"class\" in Matrix.hpp")
    flag=1
fi
if ((flag == 1)); then
    (<&2 echo "Please fix the above errors in Matrix.hpp, exiting")
    exit 1
fi

# Exit if code does not compile
INCLUDE="$LIB_DIR/googletest/googletest/include/"
FILES="./test.c $LIB_DIR/libgtest.a"
g++ -std=c++11 -D "UseTemplate=-1" -isystem $INCLUDE -pthread $FILES -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Could not compile code, exiting")
    exit $status
fi
rm -rf ./test

# Warn if main.cpp does not compile
g++ -std=c++11 ./main.cpp -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Warning: main.cpp does not compile")
fi
rm -rf ./test

# Compile and run unit tests
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
        arg0="Run$arg"
        arg1="UseTemplate=$TEMPLATE"
        if [[ "$arg" == "ConstAdditionTest" ]]; then
            output=$(g++ -std=c++11 -D "$arg0" -D "$arg1" -isystem $INCLUDE -pthread $FILES -o ./test 2>&1 > /dev/null)
            if [ -z "$output" ]; then
                (<&2 echo "$arg should not have compiled")
            elif [ -z "$(echo "$output" | grep 'error: passing .const .*. as .this. argument of .*::operator=.* discards qualifiers')" ]; then
                (<&2 echo "$output")
                (<&2 echo "Expected $arg to raise a compiler error, but got the wrong compiler error")
            else
                echo "Passed ConstAdditionTest"
                ((passed_test_count += 1))
            fi
        else
            g++ -std=c++11 -D "$arg0" -D "$arg1" -isystem $INCLUDE -pthread $FILES -o ./test
            status=$?
            if ((status != 0)); then
                (<&2 echo "Could not compile $arg, ignoring")
            else
                ./test --gtest_filter="A4Test.$arg"
                status=$?
                if ((status == 0)); then
                    ((passed_test_count += 1))
               fi
            fi
            rm -rf ./test
        fi
        echo
    fi
done

# Success (possibly)
echo "$passed_test_count/$test_count tests passed"
if (($passed_test_count < $test_count)); then
    exit 1
else
    exit 0
fi
