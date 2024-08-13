#include "WeeklyCourse.h"

using namespace std;

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime, Poco::Data::Time endTime)
: Course(courseKey, title, major, creditPoints), dayOfWeek{dayOfWeek}, startTime{startTime},
  endTime{endTime}
{

}

WeeklyCourse::~WeeklyCourse()
{

}

const Poco::DateTime::DaysOfWeek& WeeklyCourse::getDayOfWeek() const
{
	return dayOfWeek;
}

const Poco::Data::Time& WeeklyCourse::getEndTime() const
{
	return endTime;
}

const Poco::Data::Time& WeeklyCourse::getStartTime() const
{
	return startTime;
}

void WeeklyCourse::write(std::ostream &out) const
{
	Poco::DateTime start(1,1,1,getStartTime().hour(),
			getStartTime().minute());
	Poco::DateTime end(1,1,1,getEndTime().hour(),
			getEndTime().minute());
	string startT = Poco::DateTimeFormatter::format(start, "%H:%M");
	string endT = Poco::DateTimeFormatter::format(end , "%H:%M");

	out << "W;";
	Course::write(out);
	out << ";" << getDayOfWeek() << ";" << startT << ";" << endT;
}

unique_ptr<WeeklyCourse> WeeklyCourse::read(std::istream &in)
{
	string courseKeyStr, title, major, creditPointsStr;
	string day, startHour, startMinute, endHour, endMinute;

	getline(in, courseKeyStr, ';');
	getline(in, title, ';');
	getline(in, major, ';');
	getline(in, creditPointsStr, ';');
	getline(in, day, ';');
	getline(in, startHour, ':');
	getline(in, startMinute, ';');
	getline(in, endHour, ':');
	getline(in, endMinute, ';');

	unsigned int courseKey = stoul(courseKeyStr);
	float creditPoints = stof(creditPointsStr);

	Poco::DateTime::DaysOfWeek daysOfWeek =
			static_cast<Poco::DateTime::DaysOfWeek>(stoi(day));

	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
	startTime.assign(stoi(startHour), stoi(startMinute), 0);
	endTime.assign(stoi(endHour), stoi(endMinute), 0);

	return make_unique<WeeklyCourse>(courseKey, title, major,
			creditPoints, daysOfWeek, startTime, endTime);
}
