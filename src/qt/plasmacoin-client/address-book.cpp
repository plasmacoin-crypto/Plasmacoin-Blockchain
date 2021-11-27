//
// FILENAME: address-book.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for address-book.h
// CREATED: 2021-11-24 @ 4:52 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "address-book.h"

AddressBook::AddressBook(
	QTableWidget*& tableWidget, QLabel* nameDisplay, QLineEdit* nameField,
	QLabel* usernameDisplay, QLineEdit* usernameField, QLabel* addressDisplay,
	QLineEdit* addressField, QDateEdit* birthday
):
	m_ContactsList(tableWidget),
	m_NameDisplay(nameDisplay),
	m_UsernameDisplay(usernameDisplay),
	m_AddressDisplay(addressDisplay),
	m_NameField(nameField),
	m_UsernameField(usernameField),
	m_AddressField(addressField),
	m_Birthday(birthday)
{
	m_ContactsList->setRowCount(0);

	SetEditing(false);
}

AddressBook::~AddressBook() {
	m_ContactsList->clear();
	m_ContactsList->setRowCount(0);
}

// Add a row to the contacts list
void AddressBook::Add(Contact* contact) {
	int rowNum = m_ContactsList->rowCount() + 1;
	m_ContactsList->setRowCount(rowNum);

	m_ContactsList->setItem(rowNum - 1, 0, new QTableWidgetItem(QString::fromStdString(contact->GetUsername())));
	m_ContactsList->setItem(rowNum - 1, 1, new QTableWidgetItem(QString::fromStdString(contact->GetAddress())));

	m_Contacts.push_back(contact);
}

void AddressBook::Delete(int row) {
	// Remove the row
	m_ContactsList->removeRow(row);
	m_Contacts.erase(m_Contacts.begin() + row);

	m_ContactsList->selectRow(row - 1); // Shift to the row above
}

void AddressBook::Update(Contact* contact, int row) {
	m_Contacts[row] = contact;
	Sort();
}

// Get the contact at a given row number
Contact* AddressBook::At(int row) const {
	return m_Contacts[row];
}

// Sort the address book alphabetically by username
void AddressBook::Sort() {
	// Sort the contacts
	std::sort(m_Contacts.begin(), m_Contacts.end(), [](Contact* c1, Contact* c2) -> bool {
		return c1->GetUsername() < c2->GetUsername();
	});

	Regenerate(); // Update the table
}

// Switch between editing and not editing the address book
void AddressBook::SetEditing(bool editing) {
	return editing? Unlock() : Lock();
}

// Get the row number of a given contact
int AddressBook::GetRowOf(Contact* contact) {
	auto loc = std::find(m_Contacts.begin(), m_Contacts.end(), contact);
	return std::distance(m_Contacts.begin(), loc);
}

void AddressBook::SetInsertion(bool insertion) {
	m_IsInserting = insertion;
}

bool AddressBook::IsInserting() const {
	return m_IsInserting;
}

// Hide all writable fields and make sure everything is read only
void AddressBook::Lock() {
	// Hide the writable fields
	m_NameField->setVisible(false);
	m_UsernameField->setVisible(false);
	m_AddressField->setVisible(false);

	// Show the read only fields
	m_NameDisplay->setVisible(true);
	m_UsernameDisplay->setVisible(true);
	m_AddressDisplay->setVisible(true);

	// Make the birthday field read only
	m_Birthday->setReadOnly(true);
	m_Birthday->setCalendarPopup(false);

	m_ContactsList->setSelectionMode(QAbstractItemView::SingleSelection); // Allow selecting contacts
}

// Show writable fields and allow write access
void AddressBook::Unlock() {
	// Hide the read only fields
	m_NameDisplay->setVisible(false);
	m_UsernameDisplay->setVisible(false);
	m_AddressDisplay->setVisible(false);

	// Show the read only fields
	m_NameField->setVisible(true);
	m_UsernameField->setVisible(true);
	m_AddressField->setVisible(true);

	// Allow write access to the birthday field
	m_Birthday->setReadOnly(false);
	m_Birthday->setCalendarPopup(true);

	m_ContactsList->setSelectionMode(QAbstractItemView::NoSelection); // Disallow selecting contacts
}

// Clear and add back all contacts to the address book
void AddressBook::Regenerate() {
	// Clear the table
	m_ContactsList->clear();
	m_ContactsList->setRowCount(0);

	// Copy the user's contacts
	std::vector<Contact*> contactsCopy;
	std::copy(m_Contacts.begin(), m_Contacts.end(), std::back_inserter(contactsCopy));

	m_Contacts.clear();

	// Add the contacts back into the table (using the copy)
	for (auto contact: contactsCopy) {
		Add(contact);
	}

	m_ContactsList->setHorizontalHeaderLabels(QStringList() << "Username" << "Address");
}
