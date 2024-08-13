#include "Course.h"
#include <iostream>

using namespace std;

const std::map<unsigned char,std::string> Course::majorById =
	{
			{ 'A', "AUTOMATION" },
			{ 'E', "EMBEDDED" },
			{ 'C', "COMMUNICATION" },
			{ 'P', "POWER" }
	};

Course::Course(unsigned int courseKey, std::string title, std::string newMajor, float creditPoints)
: courseKey(courseKey), title(title), creditPoints(creditPoints)
{
	setMajor(newMajor);
}

Course::~Course()
{

}

const unsigned int Course::getCourseKey() const
{
	return this->courseKey;
}

const std::string& Course::getTitle() const
{
	return this->title;
}

const std::string& Course::getMajor() const
{
	if(major != ' ')
	{
		return this->majorById.at(major);
	}

	static const std::string emptyString;
	return emptyString;
}

const float Course::getCreditPoints() const
{
	return this->creditPoints;
}

const std::map<unsigned char, std::string>& Course::getMajorById() const
{
	return this->majorById;
}

void Course::setMajor(std::string& newMajor)
{
	std::string result;
	for (char c : newMajor)
	{
		result += std::toupper(c);
	}

	for (const auto& entry : majorById)
	{
		if (entry.second == result)
		{
			this->major = entry.first;
			return;
		}
	}

	this->major = ' ';
}

void Course::write(std::ostream &out) const
{
	string titleupper;
	for (char c : getTitle())
	{
		titleupper += std::toupper(c);
	}
	out << getCourseKey() << ";" << titleupper << ";" << getMajor() << ";" << getCreditPoints();
}
