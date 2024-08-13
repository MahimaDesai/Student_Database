#include "Enrollment.h"

using namespace std;

Enrollment::Enrollment(std::string& semester, const Course* course)
 :semester(semester), course(course)
{
	this->grade = 0;
}

Enrollment::~Enrollment()
{

}

const float Enrollment::getGrade() const
{
	return this->grade;
}

const std::string& Enrollment::getSemester() const
{
	return this->semester;
}

const Course* Enrollment::getCourse() const
{
	return this->course;
}

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}

void Enrollment::write(std::ostream &out) const
{
	out << getCourse()->getCourseKey() << ";" << getSemester();
	if(getGrade()>0)
	{
		out << ";" << getGrade();
	}
}

Enrollment Enrollment::read(std::istream &in, const Course* course)
{
	string semesterstr, gradestr;

	getline(in, semesterstr, ';');
	getline(in, gradestr, ';');

	Enrollment readEnrollment(semesterstr, course);
	readEnrollment.setGrade(stof(gradestr));

	return readEnrollment;
}
