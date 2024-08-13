#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include <memory>
#include <sstream>
#include <iostream>

/**
 * @brief Class WeeklyCourse
 */
class WeeklyCourse: public Course
{
private:
	Poco::DateTime::DaysOfWeek dayOfWeek; ///< Day of the week
	Poco::Data::Time startTime; ///< Start time of the weekly course.
	Poco::Data::Time endTime; ///< End time of the weekly course.

public:
	/**
	 * @brief Constructor
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param major Major associated with the course.
	 * @param creditPoints Credit points assigned to the course.
	 * @param dayOfWeek Day of the week when the course occurs.
	 * @param startTime Start time of the weekly course.
	 * @param endTime End time of the weekly course.
	 */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
			Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime, Poco::Data::Time endTime);

	/**
	 * @brief Destructor
	 */
	virtual ~WeeklyCourse();

	/**
	 * @brief Get the day of the week.
	 * @return The day of the week.
	 */
	const Poco::DateTime::DaysOfWeek& getDayOfWeek() const;

	/**
	 * @brief Get the end time of the weekly course.
	 * @return The end time.
	 */
	const Poco::Data::Time& getEndTime() const;

	/**
	 * @brief Get the start time of the weekly course.
	 * @return The start time.
	 */
	const Poco::Data::Time& getStartTime() const;

	/**
	 * @brief Write the weekly course information to an output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream& out) const override;

	/**
	 * @brief Read a weekly course from an input stream.
	 * @param in The input stream to read from.
	 * @return A unique pointer to the read weekly course.
	 */
	static std::unique_ptr<WeeklyCourse> read(std::istream& in);
};

#endif /* WEEKLYCOURSE_H_ */
