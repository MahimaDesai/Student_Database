#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"
#include <sstream>
#include <iomanip>
#include <memory>

/**
 * @brief Class BlockCourse
 */
class BlockCourse: public Course
{
private:
	Poco::Data::Time startTime; ///< Start time of the block course.
	Poco::Data::Time endTime; ///< End time of the block course.
	Poco::Data::Date startDate; ///< Start date of the block course.
	Poco::Data::Date endDate; ///< End date of the block course.

public:
	/**
	 * @brief Constructor
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param major Major associated with the course.
	 * @param creditPoints Credit points assigned to the course.
	 * @param startTime Start time of the block course.
	 * @param endTime End time of the block course.
	 * @param startDate Start date of the block course.
	 * @param endDate End date of the block course.
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
			Poco::Data::Time startTime, Poco::Data::Time endTime,
			Poco::Data::Date startDate, Poco::Data::Date endDate);

	/**
	 * @brief Destructor
	 */
	virtual ~BlockCourse();

	/**
	 * @brief Get the end date of the block course.
	 * @return The end date.
	 */
	const Poco::Data::Date& getEndDate() const;

	/**
	 * @brief Get the end time of the block course.
	 * @return The end time.
	 */
	const Poco::Data::Time& getEndTime() const;

	/**
	 * @brief Get the start date of the block course.
	 * @return The start date.
	 */
	const Poco::Data::Date& getStartDate() const;

	/**
	 * @brief Get the start time of the block course.
	 * @return The start time.
	 */
	const Poco::Data::Time& getStartTime() const;

	/**
	 * @brief Write the block course information to an output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream& out) const override;

	/**
	 * @brief Read a block course from an input stream.
	 * @param in The input stream to read from.
	 * @return A unique pointer to the read block course.
	 */
	static std::unique_ptr<BlockCourse> read(std::istream& in);
};

#endif /* BLOCKCOURSE_H_ */
