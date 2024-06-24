#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

class ContactManager {
private:
    std::vector<Contact> contacts;

    void loadContacts() {
        std::ifstream file("contacts.txt");
        if (!file.is_open()) return;

        std::string name, phone, email;
        while (getline(file, name) && getline(file, phone) && getline(file, email)) {
            contacts.push_back({name, phone, email});
        }
        file.close();
    }

    void saveContacts() {
        std::ofstream file("contacts.txt"); 
        for (const auto& contact : contacts) {
            file << contact.name << "\n" << contact.phone << "\n" << contact.email << "\n";
        }
        file.close();
    }

public:
    ContactManager() {
        loadContacts();
    }
    ~ContactManager() {
        saveContacts();
    }

    void addContact() {
        Contact contact;
        std::cout << "Enter name: ";
        std::getline(std::cin, contact.name);
        std::cout << "Enter phone: ";
        std::getline(std::cin, contact.phone);
        std::cout << "Enter email: ";
        std::getline(std::cin, contact.email);
        contacts.push_back(contact);
        std::cout << "Contact added successfully!\n";
    }

    void viewContacts() {
        if (contacts.empty()) {
            std::cout << "No contacts found.\n";
            return;
        }

        for (size_t i = 0; i < contacts.size(); ++i) {
            std::cout << i + 1 << ". Name: " << contacts[i].name
                      << ", Phone: " << contacts[i].phone
                      << ", Email: " << contacts[i].email << "\n";
        }
    }

    void editContact() {
        viewContacts();
        if (contacts.empty()) return;

        size_t index;
        std::cout << "Enter the contact number to edit: ";
        std::cin >> index;
        std::cin.ignore();

        if (index == 0 || index > contacts.size()) {
            std::cout << "Invalid contact number.\n";
            return;
        }

        Contact& contact = contacts[index - 1];
        std::cout << "Enter new name (current: " << contact.name << "): ";
        std::getline(std::cin, contact.name);
        std::cout << "Enter new phone (current: " << contact.phone << "): ";
        std::getline(std::cin, contact.phone);
        std::cout << "Enter new email (current: " << contact.email << "): ";
        std::getline(std::cin, contact.email);

        std::cout << "Contact updated successfully!\n";
    }

    void deleteContact() {
        viewContacts();
        if (contacts.empty()) return;

        size_t index;
        std::cout << "Enter the contact number to delete: ";
        std::cin >> index;
        std::cin.ignore();

        if (index == 0 || index > contacts.size()) {
            std::cout << "Invalid contact number.\n";
            return;
        }

        contacts.erase(contacts.begin() + index - 1);
        std::cout << "Contact deleted successfully!\n";
    }
};

int main() {
    ContactManager manager;
    int choice;

    do {
        std::cout << "\nContact Management System\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. View Contacts\n";
        std::cout << "3. Edit Contact\n";
        std::cout << "4. Delete Contact\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // To ignore the newline character left in the buffer

        switch (choice) {
            case 1:
                manager.addContact();
                break;
            case 2:
                manager.viewContacts();
                break;
            case 3:
                manager.editContact();
                break;
            case 4:
                manager.deleteContact();
                break;
            case 5:
                std::cout << "Exiting the program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}