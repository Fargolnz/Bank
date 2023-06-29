#include "../Header/UserSession.h"

UserSession::UserSession() {}

UserSession::UserSession(int id, RoleEnum role) : id(id), role(role) {}

int UserSession::getId()
{
	return id;
}

RoleEnum UserSession::getRole()
{
	return role;
}