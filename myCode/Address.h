#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <iostream>
#include <memory>

/**
 * @brief Class Address
 */
class Address
{
private:
    std::string street; ///< Street name
    unsigned short postalCode; ///< Postal code
    std::string cityName; ///< City name
    std::string additionalInfo; ///< Additional information

public:
    /**
     * @brief Constructor
     * @param street Street name of the address.
     * @param postalCode Postal code of the address.
     * @param cityName City name of the address.
     * @param additionalInfo Additional information about the address.
     */
    Address(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);

    /**
     * @brief Destructor
     */
    virtual ~Address();

    /**
     * @brief Get additional information about the address.
     * @return Additional information.
     */
    const std::string& getAdditionalInfo() const;

    /**
     * @brief Get the city name of the address.
     * @return City name.
     */
    const std::string& getCityName() const;

    /**
     * @brief Get the postal code of the address.
     * @return Postal code.
     */
    const unsigned short getPostalCode() const;

    /**
     * @brief Get the street name of the address.
     * @return Street name.
     */
    const std::string& getStreet() const;

    /**
     * @brief Write the address information to an output stream.
     * @param out The output stream to write to.
     */
    void write(std::ostream& out) const;

    /**
     * @brief Read an address from an input stream.
     * @param in The input stream to read from.
     * @return A shared pointer to the read address.
     */
    static std::shared_ptr<Address> read(std::istream& in);
};

#endif /* ADDRESS_H_ */
