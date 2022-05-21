//
// FILENAME: address-book.h | Plasmacoin Cryptocurrency
// DESCRIPTION: The user's address book (contacts)
// CREATED: 2021-11-24 @ 4:52 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <QtWidgets/QMainWindow>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QStringList>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLayout>
#include <QLayoutItem>

#include "ui.h"

#include "contact.h"

class AddressBook : public QMainWindow, public Ui_MainWindow {
public:
	AddressBook(
		QTableWidget*& tableWidget, QLabel* nameDisplay, QLineEdit* nameField,
		QLabel* usernameDisplay, QLineEdit* usernameField, QLabel* addressDisplay,
		QLineEdit* addressField, QLabel* birthdayDisplay, QDateEdit* birthday,
		QDialogButtonBox* buttonBox, QLayout* nameLayout, QLayout* usernameLayout,
		QLayout* addressLayout, QLayout* birthdayLayout
	);
	~AddressBook();

	void Add(Contact* contact);
	void Delete(int row);
	void Update(Contact* contact, int row);

	Contact* At(int row) const;
	void Sort();
	void SetEditing(bool editing);
	int GetRowOf(Contact* contact);
	inline size_t Size();

	void SetInsertion(bool insertion);
	bool IsInserting() const;

private:
	// Lock/unlock editing by hiding/showing writable fields
	void Lock();
	void Unlock();

	void Regenerate();

	QTableWidget*& m_ContactsList;
	QLabel *m_NameDisplay, *m_UsernameDisplay, *m_AddressDisplay, *m_BirthdayDisplay;
	QLineEdit *m_NameField, *m_UsernameField, *m_AddressField;
	QDateEdit* m_Birthday;
	QDialogButtonBox* m_ButtonBox;
	QLayout *m_NameLayout, *m_UsernameLayout, *m_AddressLayout, *m_BirthdayLayout;

	QPushButton* m_EditButton = new QPushButton("Edit Contact");
	QPushButton* m_DeleteButton = new QPushButton("Delete Contact");

	std::vector<Contact*> m_Contacts;
	bool m_IsInserting = false;
};

inline size_t AddressBook::Size() {
	return m_ContactsList->rowCount();
}

#endif // ADDRESS_BOOK_H