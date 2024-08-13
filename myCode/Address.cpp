#include "Address.h"

using namespace std;

Address::Address(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
 :street(street), postalCode(postalCode), cityName(cityName), additionalInfo(additionalInfo)
{

}

Address::~Address()
{

}

const std::string& Address::getAdditionalInfo() const
{
	return this->additionalInfo;
}

const std::string& Address::getCityName() const
{
	return this->cityName;
}

const unsigned short Address::getPostalCode() const
{
	return this->postalCode;
}

const std::string& Address::getStreet() const
{
	return this->street;
}

void Address::write(std::ostream &out) const
{
	out << ";" << getStreet() << ";" << getPostalCode() << ";"
			<< getCityName() << ";" << getAdditionalInfo();
}

shared_ptr<Address> Address::read(std::istream &in)
{
	string street, postalcodeStr, city, additionalinfo;

	getline(in, street, ';');
	getline(in, postalcodeStr, ';');
	getline(in, city, ';');
	getline(in, additionalinfo, ';');

	unsigned short postalcode = stoi(postalcodeStr);

	return make_shared<Address>(street, postalcode, city, additionalinfo);
}
