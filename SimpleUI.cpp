#include "SimpleUI.h"

using namespace std;

SimpleUI::SimpleUI(StudentDb& db): studentDb (db)
{

}

SimpleUI::~SimpleUI()
{

}

void SimpleUI::run()
{
	bool exit = false;
	while(!exit)
	{
		//Show choices and get input
		cout << endl << "Enter your choice from the below options:" << endl
				<< "1.  Add new course" << endl << "2.  List courses" << endl
				<< "3.  Add new student" << endl << "4.  Add enrollment" << endl
				<< "5.  Print student" << endl << "6.  Search student" << endl
				<< "7.  Update student" << endl << "8.  Write to file"<< endl
				<< "9.  Read from file" << endl << "10. Read from server" << endl
				<< "0.  Exit" << endl;

		unsigned int choice;
		cin >> choice;
		cout << endl;

		switch(choice)
		{
		case 0: //Exit
		{
			exit = true;
			cout << "Exiting program... Run again to start" << endl;
		}
		break;
		case 1: //Add new course
		{
			addCourse();
		}
		break;
		case 2: //List courses
		{
			listCourse();
		}
		break;
		case 3: //Add new student
		{
			addStudent();
		}
		break;
		case 4: //Add enrollment
		{
			addEnrollment();
		}
		break;
		case 5: //Print student
		{
			printStudent();
		}
		break;
		case 6: //Search student
		{
			searchStudent();
		}
		break;
		case 7: //Update student
		{
			updateStudent();
		}
		break;
		case 8: //Write file
		{
			string filename;
			cout << "Enter the file name to write to: " << endl;
			cin >> filename;
			ofstream out(filename);
			this->studentDb.write(out);
		}
		break;
		case 9: // Read file
		{
			string filename;
			cout << "Enter the file name to read from: " << endl;
			cin >> filename;
			ifstream in(filename);
			this->studentDb.read(in);
		}
		break;
		case 10: // Read from server
		{
			unsigned int dataCount;
			cout << "Enter no. of student's data to be fetched from server: ";
			cin >> dataCount;
			this->studentDb.fetchDataFromServer(dataCount);
		}
		break;
		default:
		{
			cout << "Please enter a valid choice!!" << endl;
		}
		break;
		}
	}
}

void SimpleUI::addCourse()
{
	unsigned char courseType;
	unsigned int courseKey;
	std::string title;
	std::string newMajor;
	float creditPoints;

	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;

	cout << "Enter course type [W:Weekly, B:Blocked]:";
	cin >> courseType;
	cout << "Enter course key:";
	cin >> courseKey;
	cout << "Enter title:";
	cin.ignore();
	std::getline(std::cin, title);
	cout << "Enter major:";
	cin >> newMajor;
	cout << "Enter credit points:";
	cin >> creditPoints;

	int startHour, startMinute;
	int endHour, endMinute;
	cout << "Enter course start time [Hour]:";
	cin >> startHour;
	cout << "Enter course start time [Minute]:";
	cin >> startMinute;
	cout << "Enter course end time [Hour]:";
	cin >> endHour;
	cout << "Enter course end time [Minute]:";
	cin >> endMinute;

	startTime.assign(startHour, startMinute, 0);
	endTime.assign(endHour, endMinute, 0);


	if(courseType == 'W' || courseType == 'w')
	{
		int day;
		cout << "Enter day of the week[1:Sunday... 7:Saturday]:";
		cin >> day;

		Poco::DateTime::DaysOfWeek dayOfWeek;
		switch (day)
		{
		case 1:
			dayOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY;
			break;
		case 2:
			dayOfWeek = Poco::DateTime::DaysOfWeek::MONDAY;
			break;
		case 3:
			dayOfWeek = Poco::DateTime::DaysOfWeek::TUESDAY;
			break;
		case 4:
			dayOfWeek = Poco::DateTime::DaysOfWeek::WEDNESDAY;
			break;
		case 5:
			dayOfWeek = Poco::DateTime::DaysOfWeek::THURSDAY;
			break;
		case 6:
			dayOfWeek = Poco::DateTime::DaysOfWeek::FRIDAY;
			break;
		case 7:
			dayOfWeek = Poco::DateTime::DaysOfWeek::SATURDAY;
			break;
		default:
			std::cerr << "Invalid day input.. Try again!!" << std::endl;
			break;
		}

		this->studentDb.addWeeklyCourse(courseKey, title, newMajor, creditPoints,
				dayOfWeek, startTime, endTime);

	}
	else if(courseType == 'B' || courseType == 'b')
	{
		int startDay, startMonth, startYear;
		int endDay, endMonth, endYear;
		cout << "Enter course start date [Day]:";
		cin >> startDay;
		cout << "Enter course start date [Month]:";
		cin >> startMonth;
		cout << "Enter course start date [Year]:";
		cin >> startYear;
		cout << "Enter course end date [Day]:";
		cin >> endDay;
		cout << "Enter course end date [Month]:";
		cin >> endMonth;
		cout << "Enter course end date [Year]:";
		cin >> endYear;

		startDate.assign(startYear, startMonth, startDay);
		endDate.assign(endYear, endMonth, endDay);

		this->studentDb.addBlockCourse(courseKey, title, newMajor, creditPoints,
				startTime, endTime, startDate, endDate);
	}
	else
	{
		cout << "Invalid course type!!" << endl;
	}
}

void SimpleUI::listCourse()
{
	if(this->studentDb.getCourses().size() > 0)
	{
		cout << this->studentDb.getCourses().size() << endl;

		for(const auto& entry : this->studentDb.getCourses())
		{
			const Course* course = entry.second.get();
			if (const BlockCourse* blockCourse = dynamic_cast<const BlockCourse*>(course))
			{
				ostringstream oss1;
				ostringstream oss2;
				oss1 << setw(2) << setfill('0') << blockCourse->getStartDate().day() << "."
						<< setw(2) << setfill('0') << blockCourse->getStartDate().month() << "."
						<< blockCourse->getStartDate().year();
				oss2 << setw(2) << setfill('0') << blockCourse->getEndDate().day() << "."
						<< setw(2) << setfill('0') << blockCourse->getEndDate().month() << "."
						<< blockCourse->getEndDate().year();

				Poco::DateTime start(1,1,1,blockCourse->getStartTime().hour(),
						blockCourse->getStartTime().minute());
				Poco::DateTime end(1,1,1,blockCourse->getEndTime().hour(),
						blockCourse->getEndTime().minute());
				string startTime = Poco::DateTimeFormatter::format(start, "%H:%M");
				string endTime = Poco::DateTimeFormatter::format(end, "%H:%M");
				std::string titleUpper;
				for (char c : blockCourse->getTitle())
				{
					titleUpper += std::toupper(c);
				}

				cout << "Type : Block course" << endl
					 << "Course Key: " << blockCourse->getCourseKey() << endl
				     << "Title: " << titleUpper << endl
				     << "Major: " << blockCourse->getMajor() << endl
				     << "Credit Points: " << blockCourse->getCreditPoints() << endl
				     << "Start Date: " << oss1.str() << endl
				     << "End Date: " << oss2.str() << endl
				     << "Start Time: " << startTime << endl
				     << "End Time: " << endTime << endl;
			}
			else if (const WeeklyCourse* weeklyCourse = dynamic_cast<const WeeklyCourse*>(course))
			{
				Poco::DateTime start(1,1,1,weeklyCourse->getStartTime().hour(),
						weeklyCourse->getStartTime().minute());
				Poco::DateTime end(1,1,1,weeklyCourse->getEndTime().hour(),
						weeklyCourse->getEndTime().minute());
				string startTime = Poco::DateTimeFormatter::format(start, "%H:%M");
				string endTime = Poco::DateTimeFormatter::format(end , "%H:%M");
				std::string titleUpper;
				for (char c : weeklyCourse->getTitle())
				{
					titleUpper += std::toupper(c);
				}

				cout << "Type: Weekly Course" << endl
				     << "Course Key: " << weeklyCourse->getCourseKey() << endl
				     << "Title: " << titleUpper << endl
				     << "Major: " << weeklyCourse->getMajor() << endl
				     << "Credit Points: " << weeklyCourse->getCreditPoints() << endl
				     << "Day of Week: " << weeklyCourse->getDayOfWeek() << endl
				     << "Start Time: " << startTime << endl
				     << "End Time: " << endTime << endl;
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No courses added!!" << endl;
	}
}

void SimpleUI::addStudent()
{
	std::string firstName;
	std::string lastName;
	Poco::Data::Date dateOfBirth;
	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;

	int birthDay, birthMonth, birthYear;
	cout << "Enter first name:";
	cin >> firstName;
	cout << "Enter last name:";
	cin >> lastName;
	cout << "Enter birth date [Day]:";
	cin >> birthDay;
	cout << "Enter birth month [Month]:";
	cin >> birthMonth;
	cout << "Enter birth year [Year]:";
	cin >> birthYear;
	cin.ignore();
	cout << "Enter street:";
	getline(cin , street);
	cout << "Enter postal code:";
	cin >> postalCode;
	cin.ignore();
	cout << "Enter city name:";
	getline(cin , cityName);
	cout << "Enter additional info:";
	getline(cin , additionalInfo);

	dateOfBirth.assign(birthYear, birthMonth, birthDay);

	this->studentDb.addStudent(firstName, lastName, dateOfBirth,
			street, postalCode, cityName, additionalInfo);

}

void SimpleUI::addEnrollment()
{
	unsigned int matrikelNumber;
	unsigned int courseKey;
	std::string semester;

	cout << "Enter matrikel number:" << endl;
	cin >> matrikelNumber;

	auto iterator = this->studentDb.getStudents().find(matrikelNumber);
	if (iterator != this->studentDb.getStudents().end())
	{
		cout << "Enter course key:" << endl;
		cin >> courseKey;

		auto courseIterator = this->studentDb.getCourses().find(courseKey);
		if(courseIterator != this->studentDb.getCourses().end())
		{
			bool enrollmentExists = false;
			for (auto& enrollment : iterator->second.getEnrollments())
			{
				if (enrollment.getCourse()->getCourseKey() == courseKey)
				{
					enrollmentExists = true;
					break;
				}
			}
			if (!enrollmentExists)
			{
				cout << "Enter semester:" << endl;
				cin >> semester;

				this->studentDb.addEnrollment(matrikelNumber, courseKey, semester);
			}
			else
				cout << "Enrollment already exists!!" << endl;
		}
		else
			cout << "Invalid course key!!" << endl;

	}
	else
		cout << "Invalid matrikel number entered!!" << endl;
}

void SimpleUI::printStudent()
{
	unsigned int matrikelNumber;
	cout << "Enter matrikel number:" << endl;
	cin >> matrikelNumber;

	auto studentIterator = this->studentDb.getStudents().find(matrikelNumber);
	if (studentIterator != this->studentDb.getStudents().end())
	{
		auto& student = studentIterator->second;
		ostringstream oss;
		oss << setw(2) << setfill('0') << student.getDateOfBirth().day() << "."
				<< setw(2) << setfill('0') << student.getDateOfBirth().month() << "."
				<< student.getDateOfBirth().year();

		cout << endl << "Student Information" << endl
		     << "Matrikel Number: " << student.getMatrikelNumber() << endl
		     << "First Name: " << student.getFirstName() << endl
		     << "Last Name: " << student.getLastName() << endl
		     << "Date of Birth: " << oss.str() << endl;

		cout << "Address" << endl
		     << "Street: " << student.getAddress()->getStreet() << endl
		     << "Postal Code: " << student.getAddress()->getPostalCode() << endl
		     << "City: " << student.getAddress()->getCityName() << endl;

		if(student.getAddress()->getAdditionalInfo() != " ")
		{
			cout << "Additional Info: " << student.getAddress()->getAdditionalInfo();
		}
		cout << endl;

		if(student.getEnrollments().size() > 0)
		{
			cout << endl << "Enrollments: " << student.getEnrollments().size() << endl;
			for(const auto& enrollment : student.getEnrollments())
			{
				cout << "Course key: " << enrollment.getCourse()->getCourseKey() << endl
						<< "Semester: " << enrollment.getSemester() << endl;
				if(enrollment.getGrade() != 0)
				{
					cout << "Grade: " << fixed << setprecision(1) << enrollment.getGrade() << endl;
				}
			}
		}
		else
			cout << endl << "No enrollments exist!!" << endl;
	}
	else
	{
		cout << "Invalid matrikel number... Try again!!" << endl;
	}
	cout << endl;
}

void SimpleUI::searchStudent()
{
	std::string input;
	cout << "Enter the string: " << endl;
	cin >> input;

	bool studentFound = false;
	for(const auto& entry : this->studentDb.getStudents())
	{
		if((entry.second.getFirstName().find(input) != std::string::npos) ||
				(entry.second.getLastName().find(input) != std::string::npos))
		{
			studentFound = true;
			cout << endl << "Student Information:" << endl
			     << "Matrikel Number: " << entry.second.getMatrikelNumber() << endl
			     << "First Name: " << entry.second.getFirstName() << endl
			     << "Last Name: " << entry.second.getLastName() << endl;
		}
	}
	if(!studentFound)
	{
		cout << endl << "No student found!!" << endl;
	}
}

void SimpleUI::updateStudent()
{
	unsigned int matrikelNumber;
	cout << "Enter matrikel number:" << endl;
	cin >> matrikelNumber;

	auto studentIterator = this->studentDb.getStudents().find(matrikelNumber);
	if (studentIterator != this->studentDb.getStudents().end())
	{
		bool exit = false;
		while(!exit)
		{
			cout << endl << "Enter your choice from the below options:" << endl
					<< "1. Update first name" << endl << "2. Update last name" << endl
					<< "3. Update date of birth" << endl << "4. Update enrollment" << endl
					<< "5. Update address" << endl << "0. Exit" << endl;

			unsigned int choice;
			cin >> choice;
			cout << endl;

			std::string firstName;
			std::string lastName;
			Poco::Data::Date dateOfBirth;
			switch(choice)
			{
			case 0: //Exit
			{
				exit = true;
				cout << "Exiting update process!!" << endl;
			}
			break;
			case 1: //Update first name
			{
				cout << "Enter first name:" << endl;
				cin >> firstName;
				this->studentDb.updateStudentInfo(matrikelNumber, choice,
						firstName, lastName, dateOfBirth);
			}
			break;
			case 2: //Update last name
			{
				cout << "Enter last name:" << endl;
				cin >> lastName;
				this->studentDb.updateStudentInfo(matrikelNumber, choice,
						firstName, lastName, dateOfBirth);
			}
			break;
			case 3: //Update date of birth
			{
				int birthDay, birthMonth, birthYear;
				cout << "Enter birth date [Day]:" << endl;
				cin >> birthDay;
				cout << "Enter birth month [Month]:" << endl;
				cin >> birthMonth;
				cout << "Enter birth year [Year]:" << endl;
				cin >> birthYear;
				dateOfBirth.assign(birthYear, birthMonth, birthDay);
				this->studentDb.updateStudentInfo(matrikelNumber, choice,
						firstName, lastName, dateOfBirth);
			}
			break;
			case 4: //Update enrollment
			{
				unsigned int courseKey;
				cout << "Enter course key: " << endl;
				cin >> courseKey;

				const auto& student = this->studentDb.getStudents().at(matrikelNumber);
				bool validCourseKey = false;
				for(const auto& enrollment : student.getEnrollments())
				{
					if((enrollment.getCourse()->getCourseKey()) == courseKey)
					{
						validCourseKey = true;
					}
				}
				if(validCourseKey)
				{
					cout << endl << "Select an option:" << endl
							<< "1. Update grade" << endl
							<< "2. Remove enrollment" << endl
							<< "0. Exit" << endl;
					unsigned int courseChoice;
					cin >> courseChoice;

					float grade;
					switch(courseChoice)
					{
					case 0: //Exit
					{
						cout << endl << "Exiting enrollment update!!" << endl;
					}
					break;
					case 1: //Update grade
					{
						cout << "Enter grade:" << endl;
						cin >> grade;
						this->studentDb.updateEnrollment(matrikelNumber,
								courseKey, courseChoice, grade);
					}
					break;
					case 2: //Delete enrollment
					{
						this->studentDb.updateEnrollment(matrikelNumber,
								courseKey, courseChoice, grade);
					}
					break;
					default:
					{
						cout << endl << "Please enter a valid choice!!" << endl;
					}
					break;
					}
				}
				else
				{
					cout << endl << "Invalid course key!!" << endl;
				}
			}
			break;
			case 5: //Update address (creating new as address is mutable)
			{
				std::string street;
				unsigned short postalCode;
				std::string cityName;
				std::string additionalInfo;

				cout << "Enter street:" << endl;
				cin >> street;
				cout << "Enter postal code:" << endl;
				cin >> postalCode;
				cout << "Enter city name:" << endl;
				cin >> cityName;
				cout << "Enter additional info:" << endl;
				cin >> additionalInfo;
				this->studentDb.updateAddress(matrikelNumber, street, postalCode, cityName, additionalInfo);
			}
			break;
			default:
			{
				cout << "Please enter a valid choice!!" << endl;
			}
			break;
			}

		}
	}
}
