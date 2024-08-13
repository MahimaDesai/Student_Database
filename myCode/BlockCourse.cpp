#include "BlockCourse.h"

using namespace std;

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::Data::Time startTime, Poco::Data::Time endTime,
		Poco::Data::Date startDate, Poco::Data::Date endDate)
: Course(courseKey, title, major, creditPoints), startTime{startTime},
  endTime{endTime}, startDate(startDate), endDate(endDate)
{

}

BlockCourse::~BlockCourse()
{

}

const Poco::Data::Date& BlockCourse::getEndDate() const
{
	return endDate;
}

const Poco::Data::Time& BlockCourse::getEndTime() const
{
	return endTime;
}

const Poco::Data::Date& BlockCourse::getStartDate() const
{
	return startDate;
}

const Poco::Data::Time& BlockCourse::getStartTime() const
{
	return startTime;
}

void BlockCourse::write(std::ostream &out) const
{
	ostringstream oss1;
	ostringstream oss2;
	oss1 << setw(2) << setfill('0') << getStartDate().day() << "."
			<< setw(2) << setfill('0') << getStartDate().month() << "."
			<< getStartDate().year();
	oss2 << setw(2) << setfill('0') << getEndDate().day() << "."
			<< setw(2) << setfill('0') << getEndDate().month() << "."
			<< getEndDate().year();

	Poco::DateTime start(1,1,1,getStartTime().hour(),getStartTime().minute());
	Poco::DateTime end(1,1,1,getEndTime().hour(),getEndTime().minute());
	string startT = Poco::DateTimeFormatter::format(start, "%H:%M");
	string endT = Poco::DateTimeFormatter::format(end, "%H:%M");

	out << "B;";
	Course::write(out);
	out << ";" << oss1.str() << ";" << oss2.str() << ";"
			<< startT << ";" << endT;
}

unique_ptr<BlockCourse> BlockCourse::read(std::istream& in)
{
	string courseType, courseKey, title, major, creditPoints;
	string startDay, startMonth, startYear;
	string endDay, endMonth, endYear;
	string startHour, startMinute, endHour, endMinute;

	getline(in, courseKey, ';');
	getline(in, title, ';');
	getline(in, major, ';');
	getline(in, creditPoints, ';');
	getline(in, startDay, '.');
	getline(in, startMonth, '.');
	getline(in, startYear, ';');
	getline(in, endDay, '.');
	getline(in, endMonth, '.');
	getline(in, endYear, ';');
	getline(in, startHour, ':');
	getline(in, startMinute, ';');
	getline(in, endHour, ':');
	getline(in, endMinute, ';');

	unsigned int course_Key = stoi(courseKey);
	float credit_Points = stof(creditPoints);

	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	startDate.assign(stoi(startYear), stoi(startMonth), stoi(startDay));
	endDate.assign(stoi(endYear), stoi(endMonth), stoi(endDay));

	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
	startTime.assign(stoi(startHour), stoi(startMinute), 0);
	endTime.assign(stoi(endHour), stoi(endMinute), 0);

	return make_unique<BlockCourse>(course_Key, title, major, credit_Points,
			startTime, endTime, startDate, endDate);
}
