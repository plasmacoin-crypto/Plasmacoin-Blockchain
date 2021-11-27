//
// FILENAME: contact.h | Plasmacoin Cryptocurrency
// DESCRIPTION: A Plasmacoin contact (more specifically, contact data)
// CREATED: 2021-11-24 @ 5:08 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>

#include <string>

using std::string;

class Contact {
public:
	Contact(std::string name, std::string username, std::string address, const QDate& birthday);

	string GetName() const;
	string GetUsername() const;
	string GetAddress() const;
	QDate GetBirthday() const;

	void Update(std::string name, std::string username, std::string address, const QDate& birthday);

private:
	string m_Name, m_Username, m_Address;
	QDate m_Birthday;
};

#endif // CONTACT_H