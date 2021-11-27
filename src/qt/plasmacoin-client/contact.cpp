//
// FILENAME: contact.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for contact.h
// CREATED: 2021-11-24 @ 5:08 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "contact.h"

Contact::Contact(std::string name, std::string username, std::string address, const QDate& birthday):
	m_Name(name),
	m_Username(username),
	m_Address(address),
	m_Birthday(birthday)
{}

string Contact::GetName() const {
	return m_Name;
}

string Contact::GetUsername() const {
	return m_Username;
}

string Contact::GetAddress() const {
	return m_Address;
}

QDate Contact::GetBirthday() const {
	return m_Birthday;
}

void Contact::Update(std::string name, std::string username, std::string address, const QDate& birthday) {
	m_Name = name;
	m_Username = username;
	m_Address = address;
	m_Birthday = birthday;
}