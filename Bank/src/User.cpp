#include "../Header/User.h"

using namespace std;

int User::nextId = 1;

User::User() {}

User::User(const string& nationalCode, const string& name, const string& phone,
	const string& password, time_t birthDate, time_t joinDate,
	GenderEnum gender, RoleEnum role)
	: nationalCode(nationalCode), name(name), phone(phone),
	password(password), birthDate(birthDate), joinDate(joinDate),
	gender(gender), role(role)
{
	setId(nextId++);	
}

User::User(int id, const string& nationalCode, const string& name, const string& phone,
	const string& password, time_t birthDate, time_t joinDate,
	GenderEnum gender, RoleEnum role)
	: BaseEntity(id), nationalCode(nationalCode), name(name), phone(phone),
	password(password), birthDate(birthDate), joinDate(joinDate),
	gender(gender), role(role)
{}

string User::getNationalCode() const
{
	return nationalCode;
}

string User::getName() const
{
	return name;
}

string User::getPhone() const
{
	return phone;
}

string User::getPassword() const
{
	return password;
}

time_t User::getBirthDate() const
{
	return birthDate;
}

time_t User::getJoinDate() const
{
	return joinDate;
}

GenderEnum User::getGender() const
{
	return gender;
}

RoleEnum User::getRole() const
{
	return role;
}

void User::setPassword(string password)
{
	this->password = password;
}

void User::setPhone(string phone)
{
	this->phone = phone;
}

void User::setNextId(int nextId)
{
	User::nextId = nextId;
}

string User::toString() const
{
	string userStr = "";

	userStr += to_string(getId());
	userStr += ",";
	userStr += nationalCode;
	userStr += ",";
	userStr += name;
	userStr += ",";
	userStr += phone;
	userStr += ",";
	userStr += password;
	userStr += ",";
	long long longBirthDate = birthDate;
	userStr += to_string(longBirthDate);
	userStr += ",";
	long long longJoinDate = this->joinDate;
	userStr += to_string(longJoinDate);
	userStr += ",";

	switch (gender)
	{
		case Male: 
		{
			userStr += "Male";
			userStr += ",";
			break; 
		}
		case Female:
		{
			userStr += "Female";
			userStr += ",";
			break; 
		}
	}
	switch (role)
	{
		case Admin: 
		{
			userStr += "Admin";
			break;
		}
		case Employee: 
		{
			userStr += "Employee";
			break; 
		}
		case Customer: 
		{
			userStr += "Customer";
			break;
		}
	}

	return userStr;
}

User* User::fromString(std::vector<string> entityFields) const
{
	int userId = stoi(entityFields[0]);
	string nationalCode = entityFields[1];
	string name = entityFields[2];
	string phone = entityFields[3];
	string password = entityFields[4];
	long long longBirthDate = stoll(entityFields[5]);
	long long joinDate = stoll(entityFields[6]);
	GenderEnum gender;
	RoleEnum role;

	if (entityFields[7] == "Male")
		gender = Male;
	else if (entityFields[7] == "Female")
		gender = Female;

	if (entityFields[8] == "Admin")
		role = Admin;
	else if (entityFields[8] == "Employee")
		role = Employee;
	else if (entityFields[8] == "Customer")
		role = Customer;

	User* user = new User(nationalCode, name, phone, password, longBirthDate, joinDate, gender, role);

	return user;
}
User* User::fromString_reload(std::vector<std::string> entityFields) const
{
	int userId = stoi(entityFields[0]);
	string nationalCode = entityFields[1];
	string name = entityFields[2];
	string phone = entityFields[3];
	string password = entityFields[4];
	long long longBirthDate = stoll(entityFields[5]);
	long long joinDate = stoll(entityFields[6]);
	GenderEnum gender;
	RoleEnum role;

	if (entityFields[7] == "Male")
		gender = Male;
	else if (entityFields[7] == "Female")
		gender = Female;

	if (entityFields[8] == "Admin")
		role = Admin;
	else if (entityFields[8] == "Employee")
		role = Employee;
	else if (entityFields[8] == "Customer")
		role = Customer;

	User* user = new User(userId ,nationalCode, name, phone, password, longBirthDate, joinDate, gender, role);

	return user;
}