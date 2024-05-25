#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Contact {
    string firstName;
    string lastName;
    string mobilePhone;
    string homePhone;
    string workPhone;
    string email;

    void display() const {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Mobile Phone: " << mobilePhone << endl;
        cout << "Home Phone: " << homePhone << endl;
        cout << "Work Phone: " << workPhone << endl;
        if (!email.empty()) {
            cout << "Email: " << email << endl;
        }
    }
};

class ContactManager {
private:
    stack<Contact> contacts;

    void displayContact(const Contact& contact) const {
        contact.display();
        cout << "-----------------------------" << endl;
    }

public:
    void addContact(const Contact& contact) {
        contacts.push(contact);
    }

    void editContact(const string& firstName, const string& lastName) {
        stack<Contact> tempStack;
        bool found = false;

        while (!contacts.empty()) {
            Contact current = contacts.top();
            contacts.pop();
            if (current.firstName == firstName && current.lastName == lastName) {
                found = true;
                cout << "Editing contact: " << firstName << " " << lastName << endl;
                cout << "Enter new mobile phone: "; cin >> current.mobilePhone;
                cout << "Enter new home phone: "; cin >> current.homePhone;
                cout << "Enter new work phone: "; cin >> current.workPhone;
                cout << "Enter new email: "; cin >> current.email;
            }
            tempStack.push(current);
        }

        while (!tempStack.empty()) {
            contacts.push(tempStack.top());
            tempStack.pop();
        }

        if (!found) {
            cout << "Contact not found!" << endl;
        }
    }

    void deleteContact(const string& firstName, const string& lastName) {
        stack<Contact> tempStack;
        bool found = false;

        while (!contacts.empty()) {
            Contact current = contacts.top();
            contacts.pop();
            if (current.firstName == firstName && current.lastName == lastName) {
                found = true;
                cout << "Contact deleted." << endl;
            } else {
                tempStack.push(current);
            }
        }

        while (!tempStack.empty()) {
            contacts.push(tempStack.top());
            tempStack.pop();
        }

        if (!found) {
            cout << "Contact not found!" << endl;
        }
    }

    void searchContacts(const string& searchTerm) const {
        stack<Contact> tempStack = contacts;
        while (!tempStack.empty()) {
            Contact current = tempStack.top();
            tempStack.pop();
            if (current.firstName.find(searchTerm) != string::npos || current.lastName.find(searchTerm) != string::npos ||
                current.mobilePhone.find(searchTerm) != string::npos || current.homePhone.find(searchTerm) != string::npos ||
                current.workPhone.find(searchTerm) != string::npos) {
                displayContact(current);
            }
        }
    }

    void displayAllContacts() const {
        stack<Contact> tempStack = contacts;
        while (!tempStack.empty()) {
            Contact current = tempStack.top();
            tempStack.pop();
            displayContact(current);
        }
    }
};

int main() {
    ContactManager cm;
    char choice;

    do {
        cout << "\nContact Manager\n";
        cout << "1. Add Contact\n";
        cout << "2. Edit Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Search Contacts\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            Contact contact;
            cout << "Enter first name: "; cin >> contact.firstName;
            cout << "Enter last name: "; cin >> contact.lastName;
            cout << "Enter mobile phone: "; cin >> contact.mobilePhone;
            cout << "Enter home phone: "; cin >> contact.homePhone;
            cout << "Enter work phone: "; cin >> contact.workPhone;
            cout << "Enter email (optional): "; cin >> contact.email;
            cm.addContact(contact);
            break;
        }
        case '2': {
            string firstName, lastName;
            cout << "Enter first name of the contact to edit: "; cin >> firstName;
            cout << "Enter last name of the contact to edit: "; cin >> lastName;
            cm.editContact(firstName, lastName);
            break;
        }
        case '3': {
            string firstName, lastName;
            cout << "Enter first name of the contact to delete: "; cin >> firstName;
            cout << "Enter last name of the contact to delete: "; cin >> lastName;
            cm.deleteContact(firstName, lastName);
            break;
        }
        case '4': {
            string searchTerm;
            cout << "Enter search term: "; cin >> searchTerm;
            cm.searchContacts(searchTerm);
            break;
        }
        case '5':
            cm.displayAllContacts();
            break;
        case '6':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != '6');

    return 0;
}
