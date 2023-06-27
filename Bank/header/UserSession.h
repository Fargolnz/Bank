// After user logged in successfully, we will use an object from this class instead of user.

#pragma once
#include "RoleEnum.h"

class UserSession
{
public:
	UserSession();
	UserSession(int id, RoleEnum role);
	RoleEnum getRole();
	int getId();
private:
	int id;
	RoleEnum role;
};

