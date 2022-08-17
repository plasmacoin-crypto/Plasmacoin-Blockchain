//
// FILENAME: contact.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for contact.h
// CREATED: 2021-11-24 @ 5:08 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "contact.h"

Contact::Contact(const string& name, const string& username, const string& address, const QDate& birthday):
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

Node* Contact::MakeNode() const {
	Node* node = new Node("", GetAddress());
	return node;
}

void Contact::Update(const string& name, const string& username, const string& address, const QDate& birthday) {
	m_Name = name;
	m_Username = username;
	m_Address = address;
	m_Birthday = birthday;
}