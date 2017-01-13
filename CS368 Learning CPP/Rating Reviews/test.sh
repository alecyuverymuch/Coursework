#!/bin/bash

# Constants
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CODE_DIR=~gerald/public/html/cs368/assignments/a2
LIB_DIR=/p/course/cs368-gerald/public/libraries

cd $DIR

# Exit if test.c does not exist
if [ ! -f "./test.c" ]; then
    (<&2 echo "Could not find test.c, exiting")
    exit 1
fi

# Print warning messages if files have been changed
for file in "a2.hpp" "main.cpp" "rawReviewRatings.txt" "rawReviews.txt" "stopwords.txt" "trim.cpp" "trim.hpp"; do
    cmp "$CODE_DIR/$file" "$DIR/$file"
done

# Exit if code does not compile
g++ -std=c++11 *.cpp -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Could not compile code, exiting")
    exit $status
fi
rm -rf ./test

# Compile unit tests, or exit if they do not compile
INCLUDE="$LIB_DIR/googletest/googletest/include/"
FILES="./a2.cpp ./test.c ./trim.cpp $LIB_DIR/libgtest.a"
g++ -std=c++11 -isystem $INCLUDE -pthread $FILES -o ./test
status=$?
if ((status != 0)); then
    (<&2 echo "Could not create test file, exiting")
    exit $status
fi

# Run unit tests
./test
status=$?
rm -rf ./test
if ((status != 0)); then
    (<&2 echo "Error in unit tests, exiting")
    exit $status
fi

# Success!
echo "All tests passed!"
exit 0
