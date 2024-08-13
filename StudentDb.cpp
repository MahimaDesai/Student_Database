#include "StudentDb.h"

#include <boost/json/src.hpp>

using namespace std;

StudentDb::StudentDb()
{

}

StudentDb::~StudentDb()
{

}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses() const
{
	return this->courses;
}

const std::map<int, Student>& StudentDb::getStudents() const
{
	return this->students;
}

void StudentDb::addWeeklyCourse(unsigned int courseKey, std::string title,
		std::string newMajor, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime,
		Poco::Data::Time endTime)
{
	unique_ptr<WeeklyCourse> newCourse =
			make_unique<WeeklyCourse>(courseKey, title, newMajor, creditPoints,
					dayOfWeek, startTime, endTime);

	this->courses.insert(make_pair(courseKey, move(newCourse)));
}

void StudentDb::addBlockCourse(unsigned int courseKey, std::string title,
		std::string newMajor, float creditPoints,
		Poco::Data::Time startTime,
		Poco::Data::Time endTime,
		Poco::Data::Date startDate,
		Poco::Data::Date endDate)
{
	unique_ptr<BlockCourse> newCourse =
			make_unique<BlockCourse>(courseKey, title, newMajor, creditPoints,
					startTime, endTime, startDate, endDate);

	this->courses.insert(make_pair(courseKey, move(newCourse)));
}

void StudentDb::addStudent(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::string street,
		unsigned short postalCode, std::string cityName,
		std::string additionalInfo)
{
	shared_ptr<Address> studentAddress = make_shared<Address>
	(street, postalCode, cityName, additionalInfo);
	Student newStudent(firstName, lastName, dateOfBirth, studentAddress);
	this->students.insert(make_pair((newStudent.getMatrikelNumber()), move(newStudent)));
}

void StudentDb::addEnrollment(unsigned int matrikelNumber,
		unsigned int courseKey, std::string semester)
{
	auto& enrollCourse = this->courses.at(courseKey);
	Enrollment newEnrollment(semester, enrollCourse.get());
	this->students.at(matrikelNumber).setEnrollment(newEnrollment);
}

void StudentDb::updateStudentInfo(unsigned int matrikelNumber, unsigned int choice,
		std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth)
{
	switch(choice)
	{
	case 1:
		this->students.at(matrikelNumber).setFirstName(firstName);
		break;
	case 2:
		this->students.at(matrikelNumber).setLastName(lastName);
		break;
	case 3:
		this->students.at(matrikelNumber).setDateOfBirth(dateOfBirth);
		break;
	default:
		break;
	}
}

void StudentDb::updateAddress(unsigned int matrikelNumber, std::string street,
		unsigned short postalCode, std::string cityName, std::string additionalInfo)
{
	shared_ptr<Address> studentAddress = make_shared<Address>
	(street, postalCode, cityName, additionalInfo);
	this->students.at(matrikelNumber).setAddress(studentAddress);
}

void StudentDb::updateEnrollment(unsigned int matrikelNumber, unsigned int courseKey,
		unsigned int courseChoice, float grade)
{
	if(courseChoice == 1)
	{
		this->students.at(matrikelNumber).updateEnrollment(courseKey, grade);
	}
	else if(courseChoice == 2)
	{
		this->students.at(matrikelNumber).removeEnrollment(courseKey);
	}
}

void StudentDb::write(std::ostream& out)
{
	if(this->courses.size() > 0)
	{
		out << this->courses.size() << endl;
	}
	for(const auto& entry : this->courses)
	{
		const Course* course = entry.second.get();
		course->write(out);
		out << endl;
	}

	if(this->students.size() > 0)
	{
		out << this->students.size() << endl;
	}
	unsigned int totalEnrollments = 0;
	for(const auto& entry : this->students)
	{
		entry.second.write(out);
		totalEnrollments = totalEnrollments
				+ entry.second.getEnrollments().size();
		out << endl;
	}

	if(totalEnrollments > 0)
	{
		out << totalEnrollments << endl;
	}
	for(const auto& entry : this->students)
	{
		for(const auto& enrollment : entry.second.getEnrollments())
		{
			out << entry.second.getMatrikelNumber() << ";";
			enrollment.write(out);
			out << endl;
		}
	}
}

void StudentDb::read(std::istream &in)
{
	this->courses.clear();
	this->students.clear();

	string data;
	int count = 0;
	while(getline(in, data))
	{
		if(data.find(';') == std::string::npos)
		{
			count++;
		}
		else if(data.find(';') != std::string::npos)
		{
			if(count == 1) //Courses
			{
				istringstream iss(data);
				string type;
				getline(iss, type, ';');

				if (type == "W" || type == "w")
				{
					unique_ptr<WeeklyCourse> newCourse = WeeklyCourse::read(iss);
					this->courses.insert(make_pair(newCourse.get()->getCourseKey(),
							move(newCourse)));
				}
				else if (type == "B" || type == "b")
				{
					unique_ptr<BlockCourse> newCourse = BlockCourse::read(iss);
					this->courses.insert(make_pair(newCourse.get()->getCourseKey(),
							move(newCourse)));
				}
			}
			else if((count == 1 || count == 2) && isdigit(data[0])) //Students
			{
				istringstream iss(data);
				Student student = Student::read(iss);
				this->students.insert(make_pair((student.getMatrikelNumber()), move(student)));

			}
			else if (count == 3) //Enrollments
			{
				istringstream iss(data);
				string matrikel, courseKey;
				getline(iss, matrikel, ';');
				getline(iss, courseKey, ';');

				auto& enrollCourse = this->courses.at(stoi(courseKey));
				Enrollment enrollment = Enrollment::read(iss, enrollCourse.get());
				this->students.at(stoi(matrikel)).setEnrollment(enrollment);

			}
		}
	}
}

void StudentDb::fetchDataFromServer(unsigned int dataCount)
{
	string hostName = "www.hhs.users.h-da.cloud";
	string port = "4242";

	boost::asio::ip::tcp::iostream stream;
	stream.connect(hostName, port);

	if(!stream)
	{
		cerr << "Connection Unsuccessful: " << stream.error().message() << endl;
	}

	for(unsigned int idx = 0; idx < dataCount; idx++)
	{
		stream << "generate" << endl;
		stream.flush();

		string line1, line2, line3;

		getline(stream, line1);
		getline(stream, line2);
		this->parseJsonData(line2);
		getline(stream, line3);
	}
	stream << "quit" << endl;
	stream.flush();
}

void StudentDb::parseJsonData(std::string jsonString)
{
	boost::json::value parsedData = boost::json::parse(jsonString);

	string firstName = parsedData.at("name").at("firstName").as_string().c_str();
	string lastName = parsedData.at("name").at("lastName").as_string().c_str();
	int year = parsedData.at("dateOfBirth").at("year").as_int64() + 1900;
	int month = parsedData.at("dateOfBirth").at("month").as_int64() + 1;
	int day = parsedData.at("dateOfBirth").at("date").as_int64();

	string street = parsedData.at("location").at("street").as_string().c_str();
	string postCodeStr = parsedData.at("location").at("postCode").as_string().c_str();
	string city = parsedData.at("location").at("city").as_string().c_str();
	string additionalInfo = parsedData.at("location").at("state").as_string().c_str();

	Poco::Data::Date dateOfBirth(year, month, day);

	if(dataCheck(firstName, lastName, street, city, additionalInfo, postCodeStr))
	{
		int postCode = stoi(postCodeStr);
		shared_ptr<Address> address = make_shared<Address>(street, postCode, city, additionalInfo);
		Student addStudent(firstName, lastName, dateOfBirth, address);
		this->students.insert(make_pair(addStudent.getMatrikelNumber(), addStudent));
	}
}

bool StudentDb::dataCheck(std::string firstName, std::string lastName,
		std::string street, std::string city, std::string additionalInfo, std::string postCodeStr)
{
	bool postCodeCheck = all_of(postCodeStr.begin(), postCodeStr.end(), ::isdigit) ? true : false;

	bool streetCheck = all_of(street.begin(), street.end(), ::isprint)? true : false;
	bool cityCheck = all_of(city.begin(), city.end(), ::isprint)? true : false;
	bool additionaInfoCheck = all_of(additionalInfo.begin(), additionalInfo.end(), ::isprint)? true : false;

	bool firstNameCheck = all_of(firstName.begin(), firstName.end(), ::isalpha)? true : false;
	bool lastNameCheck = all_of(lastName.begin(), lastName.end(), ::isalpha)? true : false;

	if(postCodeCheck && streetCheck && additionaInfoCheck && firstNameCheck &&
			lastNameCheck && cityCheck)
	{
		return true;
	}
	else
	{
		return false;
	}
}
