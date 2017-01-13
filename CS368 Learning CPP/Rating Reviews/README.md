# a2.cpp
### Description
This program executes the following:  
1. Reads a raw text file containing movie reviews and ratings.  
2. Removes the punctuations and stopwords (e.g. is, and, the, etc.) from the reviews and writes the contents to a clean review file.  
3. Associates a value for all words found in the clean reviews based on the average rating of the word and adds it to a map.  
4. Uses the map between the words and their associated values to rate reviews from another file that doesn’t have any rating already.  
5. Writes the ratings of the reviews to an output file.  
The trim.cpp and trim.hpp files are used in trimming whitespaces in strings  
### Input files
Input files include:  
- `rawReviewRatings.txt`  
- `rawReviews.txt`  
  
- `rawReviewRatingsBig.txt`  
- `rawReviewsBig.txt`  
as test cases and  
- `stopwords.txt`  
as a file containing all the stopwords to be cleaned from the review files.  
### Compiling and Running
To compile the program:  
`$ g++ *.cpp -std=c++11`  
where *.cpp means all the .cpp files are to be compiled. You need not mention the names of the .hpp files since they are included from within the .cpp files. The option “-std=c++11” informs the compiler that our may contain C++11 features (e.g. std::unordered_map was introduced only in C++11).  
To run the program:  
`$ ./a.out rawReviewRatings.txt rawReviews.txt`  
If you don’t give these 2 command line arguments to your program, then the following error message will be printed. This error handling is already handled for you in main.cpp.  
`$ ./a.out  
USAGE: ./a.out <ReviewRatingsFile> <ReviewsFile>`
