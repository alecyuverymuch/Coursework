# SQL Queries
### Desciption
A series of queries written as responce to class prompts. Prompts and tables not provided. Includes pictures of the results of each query as well as a java file implementing JDBC with Postgres. 
### Assumptions - Part A:
	We assumed that limit N was fair game for the queries to retrieve things like top N results. We would like to note that instead of limit N,
	we could simply add row_number() to the table and select from there. Limit N was just quicker, and thus created less clutter.
	
### Assumptions - Part B:
	We assumed that it might be faster to create a view of the user's desired query in order to more easily grab the samples from that view,
	instead of re-running the query multiple times. The view is deleted when it is done, however it should be noted that the temprorary view
	is not deleted when the program crashes, thus you may create cluttered views if you crash the program too much.
