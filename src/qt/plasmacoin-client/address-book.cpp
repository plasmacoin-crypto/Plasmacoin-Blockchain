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
	QLineEdit* addressField, QDateEdit* birthday, QDialogButtonBox* buttonBox,
	QLayout* nameLayout, QLayout* usernameLayout, QLayout* addressLayout,
	QLayout* birthdayLayout
):
	m_ContactsList(tableWidget),
	m_NameDisplay(nameDisplay),
	m_UsernameDisplay(usernameDisplay),
	m_AddressDisplay(addressDisplay),
	m_NameField(nameField),
	m_UsernameField(usernameField),
	m_AddressField(addressField),
	m_Birthday(birthday),
	m_ButtonBox(buttonBox),
	m_NameLayout(nameLayout),
	m_UsernameLayout(usernameLayout),
	m_AddressLayout(addressLayout),
	m_BirthdayLayout(birthdayLayout)
{
	m_ContactsList->setRowCount(0);
	SetEditing(false);
}

AddressBook::~AddressBook() {
	m_ContactsList->clear();
	m_ContactsList->setRowCount(0);

	delete m_ContactsList;
	delete m_NameDisplay;
	delete m_UsernameDisplay;
	delete m_AddressDisplay;
	delete m_NameField;
	delete m_UsernameField;
	delete m_AddressField;
	delete m_Birthday;
	delete m_ButtonBox;
	delete m_NameLayout;
	delete m_UsernameLayout;
	delete m_AddressLayout;
	delete m_BirthdayLayout;
	delete m_EditButton;
	delete m_DeleteButton;
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
	m_ButtonBox->clear();

	// Copy the edit button
	QPushButton* editButton = new QPushButton(m_EditButton);
	editButton->setText(m_EditButton->text());

	// Copy the delete button
	QPushButton* deleteButton = new QPushButton(m_DeleteButton);
	deleteButton->setText(m_DeleteButton->text());

	// Add the buttons to the widget
	m_ButtonBox->addButton(editButton, QDialogButtonBox::ActionRole);
	m_ButtonBox->addButton(deleteButton, QDialogButtonBox::DestructiveRole);

	// Show the read only fields
	m_NameDisplay->setVisible(true);
	m_UsernameDisplay->setVisible(true);
	m_AddressDisplay->setVisible(true);

	// Hide the writable fields
	m_NameField->setVisible(false);
	m_UsernameField->setVisible(false);
	m_AddressField->setVisible(false);

	// Replace the writable widgets with the read only widgets in the layouts
	m_NameLayout->replaceWidget(m_NameField, m_NameDisplay);
	m_UsernameLayout->replaceWidget(m_UsernameField, m_UsernameDisplay);
	m_AddressLayout->replaceWidget(m_AddressField, m_AddressDisplay);

	// Make the birthday field read only
	m_Birthday->setReadOnly(true);
	m_Birthday->setCalendarPopup(false);

	m_ContactsList->setSelectionMode(QAbstractItemView::SingleSelection); // Allow selecting contacts
}

// Show writable fields and allow write access
void AddressBook::Unlock() {
	m_ButtonBox->clear();

	// Copy the delete button
	QPushButton* deleteButton = new QPushButton(m_DeleteButton);
	deleteButton->setText(m_DeleteButton->text());

	// Add the delete button along with Qt's default "Ok" and "Cancel" buttons
	m_ButtonBox->addButton(QDialogButtonBox::Ok);
	m_ButtonBox->addButton(QDialogButtonBox::Cancel);
	m_ButtonBox->addButton(deleteButton, QDialogButtonBox::DestructiveRole);

	// Hide the read only fields
	m_NameDisplay->setVisible(false);
	m_UsernameDisplay->setVisible(false);
	m_AddressDisplay->setVisible(false);

	// Show the writable fields
	m_NameField->setVisible(true);
	m_UsernameField->setVisible(true);
	m_AddressField->setVisible(true);

	// Replace the read only widgets with the writable widgets in the layouts
	m_NameLayout->replaceWidget(m_NameDisplay, m_NameField);
	m_UsernameLayout->replaceWidget(m_UsernameDisplay, m_UsernameField);
	m_AddressLayout->replaceWidget(m_AddressDisplay, m_AddressField);

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
