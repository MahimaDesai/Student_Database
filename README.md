# Student_Database
# Exercise 3.1: StudentDB

![image](https://github.com/user-attachments/assets/c70f4a91-1bb9-4970-b6b7-432af38e5e1b)

Define constructors and getters as required. Try to keep the classes immutable, i.e. define setter functions only if required for the use cases described below.

Remember the storage space optimization in Course: the property major is stored internally as a char and mapped to a string using the static data member majorById. Thus although the class uses only a character for storing the major, it accepts a std::string for the major in its constructor and provides a getter function std::string getMajor(), the optimization is completely hidden from the user of the class.

Matrikel numbers for new students are generated automatically. Each time a new student is created, the value from class member nextMatrikelNumber is used, which is incremented afterwards.

The class SimpleUI provides a simple user interface for the database. It is created with the student database as argument. The run method continuously lists the available commands waits for the user to choose one by entering the number and executes the command. Command execution may involve further data input from the user, of course. Command execution is implemented by invoking the methods of the various classes.

Note that all communication with user must be implemented in SimpleUI. Using cin or cout in any of the other classes results in 0 points for the submission. With respect to the general model-viewcontroller pattern (look it up!), the StudentDb is the model and the SimpleUI provides both the view and the controller.

The commands to be implemented are:
1. Add new Course: Queries the user for the required data and creates the new course in the database.
2. List courses: Prints all courses in the database with their data.
3. Add new student: Queries the user for the required data (member data of Student and Address) and 
	creates a new student in the database. 
4. Add enrollment: Queries the user for a matrikel number, a course id and a semester and adds the enrollment. 
	If the enrollment already exists, a warning messages is printed.
5. Print student: Queries the user for a matrikel number and prints the student including the enrolled courses 
	and their results.
6. Search student: Queries the user for a string and prints the matrikel number, last name and first name of all students 
	that have the provided string as substring in their 	first or last name. 
7. Update student: Queries the user for a matrikel number. If the corresponding student is found in the data base, 
	the properties (except for the matrikel number) are presented in a numbered list.     
	Entering the item number allows the user to modify the property, entering "0" terminates the update. 
	The list of properties also includes the enrollments. When an enrollment is chosen for update, 
	the user can remove the enrollment or enter a mark for the enrollment.

Remember that Address is immutable, as discussed in the lecture. If any property of the address is changed, a new object must be created.

There’s no prescribed format for the output of data. However, although this is only a user interface for testing purposes, you should keep usability in mind and format any output accordingly.

Create a StudentDb and a SimpleUI in main and test your implementation.

# Exercise 3.2: Persisting the Database

Write the database content to a file. The file format is derived from the commonly used CSV format (https://en.wikipedia.org/wiki/Comma-separated_values).

In order to store all data in one file, we first write a line with the number of data sets of a given kind and then all data sets, using a semicolon to separate the values. The file starts with the courses, followed by the student data (Student's data members and address data), followed by the enrollment data.

Here’s a short example:

