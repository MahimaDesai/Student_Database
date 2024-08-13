#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDb.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Poco/DateTimeFormatter.h>
#include <Poco/LocalDateTime.h>

/**
 * @brief Class SimpleUI
 */
class SimpleUI
{
private:
    StudentDb& studentDb; ///< Reference to the Student Database

public:
    /**
     * @brief Constructor
     * @param db Reference to the Student Database.
     */
    SimpleUI(StudentDb& db);

    /**
     * @brief Destructor
     */
    virtual ~SimpleUI();

    /**
     * @brief Run the main loop of the user interface.
     */
    void run();

    /**
     * @brief Add a course to the database.
     */
    void addCourse();

    /**
     * @brief List all courses in the database.
     */
    void listCourse();

    /**
     * @brief Add a student to the database.
     */
    void addStudent();

    /**
     * @brief Add an enrollment for a student in the database.
     */
    void addEnrollment();

    /**
     * @brief Print information about a specific student.
     */
    void printStudent();

    /**
     * @brief Search for a student in the database.
     */
    void searchStudent();

    /**
     * @brief Update information for a specific student in the database.
     */
    void updateStudent();
};

#endif /* SIMPLEUI_H_ */
