#include "Student.h"

using namespace std;

unsigned int Student::nextMatrikelNumber = 100000;

Student::Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address)
 :firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), address(address)
{
	matrikelNumber = nextMatrikelNumber++;
}

Student::~Student()
{

}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return this->enrollments;
}

const std::string& Student::getFirstName() const
{
	return this->firstName;
}

const std::string& Student::getLastName() const
{
	return this->lastName;
}

const unsigned int Student::getMatrikelNumber() const
{
	return this->matrikelNumber;
}

const Poco::Data::Date& Student::getDateOfBirth() const
{
	return this->dateOfBirth;
}

const std::shared_ptr<Address>& Student::getAddress() const
{
	return this->address;
}

void Student::setEnrollment(const Enrollment& newEnrollment)
{
	this->enrollments.push_back(newEnrollment);
}

void Student::setAddress(const std::shared_ptr<Address> &address)
{
	this->address = address;
}

void Student::setDateOfBirth(const Poco::Data::Date &dateOfBirth)
{
	this->dateOfBirth = dateOfBirth;
}

void Student::setFirstName(const std::string &firstName)
{
	this->firstName = firstName;
}

void Student::setLastName(const std::string &lastName)
{
	this->lastName = lastName;
}

void Student::updateEnrollment(unsigned int courseKey, float grade)
{
	for(auto& enrollment : enrollments)
	{
		if((enrollment.getCourse()->getCourseKey()) == courseKey)
		{
			enrollment.setGrade(grade);
		}
	}
}

void Student::removeEnrollment(unsigned int courseKey)
{
	for (auto it = enrollments.begin(); it != enrollments.end();)
	{
		if (it->getCourse()->getCourseKey() == courseKey)
		{
			it = enrollments.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Student::write(std::ostream &out) const
{
	ostringstream oss;
	oss << setw(2) << setfill('0') << getDateOfBirth().day() << "."
			<< setw(2) << setfill('0') << getDateOfBirth().month() << "."
			<< getDateOfBirth().year();

	out << getMatrikelNumber() << ";" << getFirstName() << ";" << getLastName()
			<< ";" << oss.str();

	getAddress()->write(out);
}

Student Student::read(std::istream &in)
{
	string matrikelnumberstr, firstName, lastName;
	string Day, Month, Year;

	getline(in, matrikelnumberstr, ';');
	getline(in, firstName, ';');
	getline(in, lastName, ';');
	getline(in, Day, '.');
	getline(in, Month, '.');
	getline(in, Year, ';');

	Student::nextMatrikelNumber = stoul(matrikelnumberstr);

	Poco::Data::Date dob;
	dob.assign(stoi(Year), stoi(Month), stoi(Day));

	shared_ptr<Address> address = Address::read(in);

	return Student(firstName, lastName, dob, address);
}
