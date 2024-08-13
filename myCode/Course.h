#ifndef COURSE_H_
#define COURSE_H_

#include <string>
#include <iostream>
#include <map>
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include <Poco/DateTime.h>

/**
 * @brief Class Course
 */
class Course
{
private:
    unsigned int courseKey; ///< Unique identifier for the course.
    std::string title; ///< Title of the course.
    unsigned char major; ///< Major of the course.
    float creditPoints; ///< Credit points assigned to the course.
    static const std::map<unsigned char, std::string> majorById; ///< Static map for major identification.


public:
    /**
     * @brief Constructor
     * @param courseKey Unique identifier for the course.
     * @param title Title of the course.
     * @param newMajor Major of the course.
     * @param creditPoints Credit points assigned to the course.
     */
	Course(unsigned int courseKey, std::string title,
			std::string newMajor, float creditPoints);

	/**
	 * @brief Destructor
	 */
	virtual ~Course();

	/**
	 * @brief Get the course key.
	 * @return The unique identifier for the course.
	 */
	const unsigned int getCourseKey() const;

	/**
	 * @brief Get the credit points assigned to the course.
	 * @return The credit points for the course.
	 */
	const float getCreditPoints() const;

	/**
	 * @brief Get the major associated with the course.
	 * @return The major for the course.
	 */
	const std::string& getMajor() const;

	/**
	 * @brief Get the map of major IDs to major names.
	 * @return The map of major IDs to major names.
	 */
	const std::map<unsigned char, std::string>& getMajorById() const;

	/**
	 * @brief Get the title of the course.
	 * @return The title of the course.
	 */
	const std::string& getTitle() const;

	/**
	 * @brief Set the major for the course.
	 * @param newMajor The new major for the course.
	 */
	void setMajor(std::string& newMajor);

	/**
	 * @brief Write the course information to an output stream.
	 * @param out The output stream to write to.
	 */
	virtual void write(std::ostream& out) const;

};

#endif /* COURSE_H_ */
