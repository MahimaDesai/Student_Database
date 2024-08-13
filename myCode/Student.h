#ifndef STUDENT_H_
#define STUDENT_H_

#include "Enrollment.h"
#include "Address.h"
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

/**
 * @brief Class Student
 */
class Student
{
private:
	static unsigned int nextMatrikelNumber; ///< Next matrikel number.
	unsigned int matrikelNumber; ///< Matrikel number
	std::string firstName; ///< First name of the student.
	std::string lastName; ///< Last name of the student.
	Poco::Data::Date dateOfBirth; ///< Date of birth of the student.
	std::vector<Enrollment> enrollments; ///< Vector of enrollments for the student.
	std::shared_ptr<Address> address; ///< Address of the student.

public:
	/**
	 * @brief Constructor
	 * @param firstName First name of the student.
	 * @param lastName Last name of the student.
	 * @param dateOfBirth Date of birth of the student.
	 * @param address Address of the student.
	 */
	Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address);

	/**
	 * @brief Destructor
	 */
	virtual ~Student();

	/**
	 * @brief Get the vector of enrollments for the student.
	 * @return Vector of enrollments.
	 */
	const std::vector<Enrollment>& getEnrollments() const;

	/**
	 * @brief Get the first name of the student.
	 * @return First name.
	 */
	const std::string& getFirstName() const;

	/**
	 * @brief Get the last name of the student.
	 * @return Last name.
	 */
	const std::string& getLastName() const;

	/**
	 * @brief Get the matrikel number assigned to the student.
	 * @return Matrikel number.
	 */
	const unsigned int getMatrikelNumber() const;

	/**
	 * @brief Get the date of birth of the student.
	 * @return Date of birth.
	 */
	const Poco::Data::Date& getDateOfBirth() const;

	/**
	 * @brief Get the address of the student.
	 * @return Address.
	 */
	const std::shared_ptr<Address>& getAddress() const;

	/**
	 * @brief Set an enrollment for the student.
	 * @param newEnrollment The enrollment to be set.
	 */
	void setEnrollment(const Enrollment& newEnrollment);

	/**
	 * @brief Set the address for the student.
	 * @param address The address to be set.
	 */
	void setAddress(const std::shared_ptr<Address> &address);

	/**
	 * @brief Set the date of birth for the student.
	 * @param dateOfBirth The date of birth to be set.
	 */
	void setDateOfBirth(const Poco::Data::Date &dateOfBirth);

	/**
	 * @brief Set the first name of the student.
	 * @param firstName The first name to be set.
	 */
	void setFirstName(const std::string &firstName);

	/**
	 * @brief Set the last name of the student.
	 * @param lastName The last name to be set.
	 */
	void setLastName(const std::string &lastName);

	/**
	 * @brief Update an existing enrollment with a new grade.
	 * @param courseKey The key of the course to be updated.
	 * @param grade The new grade to be set.
	 */
	void updateEnrollment(unsigned int courseKey, float grade);

	/**
	 * @brief Remove an enrollment for the student.
	 * @param courseKey The key of the course to be removed.
	 */
	void removeEnrollment(unsigned int courseKey);

	/**
	 * @brief Write the student information to an output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream& out) const;

	/**
	 * @brief Read a student from an input stream.
	 * @param in The input stream to read from.
	 * @return The read student object.
	 */
	static Student read(std::istream& in);
};


#endif /* STUDENT_H_ */
