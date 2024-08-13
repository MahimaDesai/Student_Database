#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include "Student.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"
#include <memory>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <algorithm>
#include <cctype>

/**
 * @brief Class StudentDb
 */
class StudentDb
{
private:
	std::map<int, Student> students; ///< Map of students indexed by their matrikel number.
	std::map<int, std::unique_ptr<const Course>> courses; ///< Map of courses indexed by their course key.

public:
	/**
	 * @brief Constructor
	 */
	StudentDb();

	/**
	 * @brief Destructor
	 */
	virtual ~StudentDb();

	/**
	 * @brief Get the map of courses in the database.
	 * @return Map of courses.
	 */
	const std::map<int, std::unique_ptr<const Course>>& getCourses() const;

	/**
	 * @brief Get the map of students in the database.
	 * @return Map of students.
	 */
	const std::map<int, Student>& getStudents() const;

	/**
	 * @brief Add a weekly course to the database.
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param newMajor Major associated with the course.
	 * @param creditPoints Credit points assigned to the course.
	 * @param dayOfWeek Day of the week when the course occurs.
	 * @param startTime Start time of the weekly course.
	 * @param endTime End time of the weekly course.
	 */
	void addWeeklyCourse(unsigned int courseKey, std::string title,
			std::string newMajor, float creditPoints,
			Poco::DateTime::DaysOfWeek dayOfWeek,
			Poco::Data::Time startTime,
			Poco::Data::Time endTime);

	/**
	 * @brief Add a block course to the database.
	 * @param courseKey Unique identifier for the course.
	 * @param title Title of the course.
	 * @param newMajor Major associated with the course.
	 * @param creditPoints Credit points assigned to the course.
	 * @param startTime Start time of the block course.
	 * @param endTime End time of the block course.
	 * @param startDate Start date of the block course.
	 * @param endDate End date of the block course.
	 */
	void addBlockCourse(unsigned int courseKey, std::string title,
			std::string newMajor, float creditPoints,
			Poco::Data::Time startTime,
			Poco::Data::Time endTime,
			Poco::Data::Date startDate,
			Poco::Data::Date endDate);

	/**
	 * @brief Add a student to the database.
	 * @param firstName First name of the student.
	 * @param lastName Last name of the student.
	 * @param dateOfBirth Date of birth of the student.
	 * @param street Street name of the student's address.
	 * @param postalCode Postal code of the student's address.
	 * @param cityName City name of the student's address.
	 * @param additionalInfo Additional information about the student's address.
	 */
	void addStudent(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, std::string street,
			unsigned short postalCode, std::string cityName,
			std::string additionalInfo);

	/**
	 * @brief Add an enrollment to the database.
	 * @param matrikelNumber Matrikel number of the student.
	 * @param courseKey Unique identifier for the course.
	 * @param semester Semester in which the enrollment took place.
	 */
	void addEnrollment(unsigned int matrikelNumber, unsigned int courseKey,
			std::string semester);

	/**
	 * @brief Update information for a student in the database.
	 * @param matrikelNumber Matrikel number of the student.
	 * @param choice Choice of information to update.
	 * @param firstName New first name for the student.
	 * @param lastName New last name for the student.
	 * @param dateOfBirth New date of birth for the student.
	 */
	void updateStudentInfo(unsigned int matrikelNumber, unsigned int choice,
			std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth);

	/**
	 * @brief Update the address for a student in the database.
	 * @param matrikelNumber Matrikel number of the student.
	 * @param street New street name for the student's address.
	 * @param postalCode New postal code for the student's address.
	 * @param cityName New city name for the student's address.
	 * @param additionalInfo New additional information about the student's address.
	 */
	void updateAddress(unsigned int matrikelNumber, std::string street,
			unsigned short postalCode, std::string cityName,
			std::string additionalInfo);

	/**
	 * @brief Update the grade for an enrollment in the database.
	 * @param matrikelNumber Matrikel number of the student.
	 * @param courseKey Unique identifier for the course.
	 * @param courseChoice Choice of course to update.
	 * @param grade New grade to be set.
	 */
	void updateEnrollment(unsigned int matrikelNumber, unsigned int courseKey,
			unsigned int courseChoice, float grade);

	/**
	 * @brief Write the database information to an output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream& out);

	/**
	 * @brief Read the database information from an input stream.
	 * @param in The input stream to read from.
	 */
	void read(std::istream& in);

	/**
	 * @brief Fetch data from a server based on the count provided.
	 * @param dataCount Number of data entries to fetch.
	 */
	void fetchDataFromServer(unsigned int dataCount);

	/**
	 * @brief Parse JSON data and add it to the database.
	 * @param jsonString JSON data to be parsed.
	 */
	void parseJsonData(std::string jsonString);

	/**
	 * @brief Check the validity of data strings.
	 * @param firstName First name of the student.
	 * @param lastName Last name of the student.
	 * @param street Street name of the student's address.
	 * @param city City name of the student's address.
	 * @param additionalInfo Additional information about the student's address.
	 * @param postCodeStr Postal code string to be checked.
	 * @return True if all data strings are valid, false otherwise.
	 */
	bool dataCheck(std::string firstName, std::string lastName,
			std::string street, std::string city, std::string additionalInfo,
			std::string postCodeStr);
};

#endif /* STUDENTDB_H_ */
