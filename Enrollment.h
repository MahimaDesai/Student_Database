#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include "Course.h"

/**
 * @brief Class Enrollment
 */
class Enrollment
{
private:
	float grade; ///< Grade achieved in the enrollment.
	std::string semester; ///< Semester of the enrollment
	const Course* course; ///< Pointer to the enrolled course.

public:
	/**
	 * @brief Constructor .
	 * @param semester Semester in which the enrollment took place.
	 * @param course Pointer to the enrolled course.
	 */
	Enrollment(std::string& semester, const Course* course);

	/**
	 * @brief Destructor
	 */
	virtual ~Enrollment();

	/**
	 * @brief Get the grade achieved in the enrollment.
	 * @return The grade.
	 */
	const float getGrade() const;

	/**
	 * @brief Get the semester in which the enrollment took place.
	 * @return The semester.
	 */
	const std::string& getSemester() const;

	/**
	 * @brief Get the pointer to the enrolled course.
	 * @return Pointer to the course.
	 */
	const Course* getCourse() const;

	/**
	 * @brief Set the grade for the enrollment.
	 * @param grade The grade to be set.
	 */
	void setGrade(float grade);

	/**
	 * @brief Write the enrollment information to an output stream.
	 * @param out The output stream to write to.
	 */
	void write(std::ostream& out) const;

	/**
	 * @brief Read an enrollment from an input stream.
	 * @param in The input stream to read from.
	 * @param course Pointer to the enrolled course.
	 * @return The read enrollment.
	 */
	static Enrollment read(std::istream& in, const Course* course);
};

#endif /* ENROLLMENT_H_ */
