//
// FILENAME: address-book.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for address-book.h
// CREATED: 2021-11-24 @ 4:52 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "address-book.h"

AddressBook::AddressBook(
	Ui_MainWindow* window, QLabel* nameDisplay, QLabel* usernameDisplay,
	QLabel* addressDisplay, QLabel* birthdayDisplay
):
	m_Window(window),
	m_NameDisplay(nameDisplay),
	m_UsernameDisplay(usernameDisplay),
	m_AddressDisplay(addressDisplay),
	m_BirthdayDisplay(birthdayDisplay)
{
	m_Window->contactsList->setRowCount(0);
	SetEditing(false);

	m_NameDisplay->setGeometry(m_Window->nameField->x(), m_Window->nameField->y(), m_Window->nameField->width(), m_Window->nameField->height());
	m_UsernameDisplay->setGeometry(m_Window->usernameField->x(), m_Window->usernameField->y(), m_Window->usernameField->width(), m_Window->usernameField->height());
	m_AddressDisplay->setGeometry(m_Window->addressField->x(), m_Window->addressField->y(), m_Window->addressField->width(), m_Window->addressField->height());
	m_BirthdayDisplay->setGeometry(m_Window->birthday->x(), m_Window->birthday->y(), m_Window->birthday->width(), m_Window->birthday->height());
}

AddressBook::~AddressBook() {
	m_Window->contactsList->clear();
	m_Window->contactsList->setRowCount(0);

	delete m_NameDisplay;
	delete m_UsernameDisplay;
	delete m_AddressDisplay;
	delete m_BirthdayDisplay;
}

// Add a row to the contacts list
void AddressBook::Add(Contact* contact) {
	int rowNum = m_Window->contactsList->rowCount() + 1;
	m_Window->contactsList->setRowCount(rowNum);

	m_Window->contactsList->setItem(rowNum - 1, 0, new QTableWidgetItem(QString::fromStdString(contact->GetUsername())));
	m_Window->contactsList->setItem(rowNum - 1, 1, new QTableWidgetItem(QString::fromStdString(contact->GetAddress())));

	m_Contacts.push_back(contact);
}

void AddressBook::Delete(int row) {
	// Remove the row
	m_Window->contactsList->removeRow(row);
	m_Contacts.erase(m_Contacts.begin() + row);

	m_Window->contactsList->selectRow(row - 1); // Shift to the row above
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
	m_Window->btndiag_confirm->clear();

	// Copy the edit button
	QPushButton* editButton = new QPushButton(m_EditButton);
	editButton->setText(m_EditButton->text());

	// Copy the delete button
	QPushButton* deleteButton = new QPushButton(m_DeleteButton);
	deleteButton->setText(m_DeleteButton->text());

	// Add the buttons to the widget
	m_Window->btndiag_confirm->addButton(editButton, QDialogButtonBox::ActionRole);
	m_Window->btndiag_confirm->addButton(deleteButton, QDialogButtonBox::DestructiveRole);

	// Make the birthday field read only
	// m_Birthday->setReadOnly(true);
	// m_Birthday->setCalendarPopup(false);

	// Show the read only fields
	m_NameDisplay->setVisible(true);
	m_UsernameDisplay->setVisible(true);
	m_AddressDisplay->setVisible(true);
	m_BirthdayDisplay->setVisible(true);

	// Hide the writable fields
	m_Window->nameField->setVisible(false);
	m_Window->usernameField->setVisible(false);
	m_Window->addressField->setVisible(false);
	m_Window->birthday->setVisible(false);

	// Replace the writable widgets with the read only widgets in the layouts
	m_Window->nameLayout->replaceWidget(m_Window->nameField, m_NameDisplay);
	m_Window->usernameLayout->replaceWidget(m_Window->usernameField, m_UsernameDisplay);
	m_Window->addressLayout->replaceWidget(m_Window->addressField, m_AddressDisplay);
	m_Window->birthdayLayout->replaceWidget(m_Window->birthday, m_BirthdayDisplay);

	m_Window->contactsList->setSelectionMode(QAbstractItemView::SingleSelection); // Allow selecting contacts
}

// Show writable fields and allow write access
void AddressBook::Unlock() {
	m_Window->btndiag_confirm->clear();

	// Copy the delete button
	QPushButton* deleteButton = new QPushButton(m_DeleteButton);
	deleteButton->setText(m_DeleteButton->text());

	// Add the delete button along with Qt's default "Ok" and "Cancel" buttons
	m_Window->btndiag_confirm->addButton(QDialogButtonBox::Ok);
	m_Window->btndiag_confirm->addButton(QDialogButtonBox::Cancel);
	m_Window->btndiag_confirm->addButton(deleteButton, QDialogButtonBox::DestructiveRole);

	// Hide the read only fields
	m_NameDisplay->setVisible(false);
	m_UsernameDisplay->setVisible(false);
	m_AddressDisplay->setVisible(false);
	m_BirthdayDisplay->setVisible(false);

	// Show the writable fields
	m_Window->nameField->setVisible(true);
	m_Window->usernameField->setVisible(true);
	m_Window->addressField->setVisible(true);
	m_Window->birthday->setVisible(true);

	// Replace the read only widgets with the writable widgets in the layouts
	m_Window->nameLayout->replaceWidget(m_NameDisplay, m_Window->nameField);
	m_Window->usernameLayout->replaceWidget(m_UsernameDisplay, m_Window->usernameField);
	m_Window->addressLayout->replaceWidget(m_AddressDisplay, m_Window->addressField);
	m_Window->birthdayLayout->replaceWidget(m_BirthdayDisplay, m_Window->birthday);

	// Allow write access to the birthday field
	// m_Birthday->setReadOnly(false);
	// m_Birthday->setCalendarPopup(true);

	m_Window->contactsList->setSelectionMode(QAbstractItemView::NoSelection); // Disallow selecting contacts
}

// Clear and add back all contacts to the address book
void AddressBook::Regenerate() {
	// Clear the table
	m_Window->contactsList->clear();
	m_Window->contactsList->setRowCount(0);

	// Copy the user's contacts
	std::vector<Contact*> contactsCopy;
	std::copy(m_Contacts.begin(), m_Contacts.end(), std::back_inserter(contactsCopy));

	m_Contacts.clear();

	// Add the contacts back into the table (using the copy)
	for (auto contact: contactsCopy) {
		Add(contact);
	}

	m_Window->contactsList->setHorizontalHeaderLabels(QStringList() << "Username" << "Address");
}
