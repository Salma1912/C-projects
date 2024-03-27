#include <iostream>
#include <string>
using namespace std;
class PhoneBook {
private:
    string* names;
    string* phones;
    int phoneBookSize;

public:
    void setSize(int size)
    {
        names = new string[size];
        phones = new string[size];
        phoneBookSize = size;
    }

    bool isValidPhoneNumber(const string& phoneNumber)
    {
        if (phoneNumber.length() != 11)
        {
            return false;
        }

        for (char c : phoneNumber)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }

        return true;
    }

    bool addEntry(string& name, string& phone)
    {
        if (name.empty())
        {
            cout << "Name must be non-empty." << endl;
            return false;
        }

        while (phone.length() != 11 || !isValidPhoneNumber(phone))
        {
            cout << "Invalid phone number. Please try again." << endl;
            cout << "Enter phone: ";
            cin >> phone;
        }

        for (int i = 0; i < phoneBookSize; ++i)
        {
            if (names[i].empty())
            {
                names[i] = name;
                phones[i] = phone;
                return true;
            }
        }

        cout << "Phone book is full. Cannot add more entries." << endl;

        return false;
    }

    bool displayEntryAtIndex(int index)
    {
        if (index >= 0 && index < phoneBookSize)
        {
            cout << "Name: " << names[index] << ", Phone: " << phones[index] << endl;
            return true;
        }

        return false;
    }

    void displayEntryAtIndices(int* indices)
    {
        for (int i = 0; i < phoneBookSize; i++)
        {
            if (indices[i] == 1)
            {
                cout << "Name: " << names[i] << ", Phone: " << phones[i] << endl;
            }
        }
    }

    void displayAll()
    {
        for (int i = 0; i < phoneBookSize; i++)
        {
            if (!names[i].empty())
            {
                cout << "Name: " << names[i] << ", Phone: " << phones[i] << endl;
            }
        }
    }

    bool findByName(const string& name) const
    {
        for (int i = 0; i < phoneBookSize; i++)
        {
            const string& currentName = names[i];
            int nameLength = currentName.length();
            int queryLength = name.length();

            if (nameLength >= queryLength)
            {
                bool isMatch = true;
                for (int j = 0; j < queryLength; j++)
                {
                    if (currentName[j] != name[j])
                    {
                        isMatch = false;
                        break;
                    }
                }
                if (isMatch)
                {
                    return true;
                }
            }
        }
        return false;
    }

    string findByPhone(const string& phone)
    {
        for (int i = 0; i < phoneBookSize; i++)
        {
            if (phones[i] == phone)
            {
                return names[i];
            }
        }

        return "";
    }

    bool updateNameAt(const string& newName, int index)
    {
        if (index >= 0 && index < phoneBookSize)
        {
            names[index] = newName;
            return true;
        }

        return false;
    }

    bool updatePhoneAt(const string& newPhone, int index)
    {
        if (index >= 0 && index < phoneBookSize)
        {
            phones[index] = newPhone;
            return true;
        }

        return false;
    }

    void copyPB(const PhoneBook& copypb)
    {
        phoneBookSize = copypb.phoneBookSize;
        names = new string[phoneBookSize];
        phones = new string[phoneBookSize];

        for (int i = 0; i < phoneBookSize; ++i)
        {
            names[i] = copypb.names[i];
            phones[i] = copypb.phones[i];
        }
    }

    void clear()
    {
        delete[] names;
        delete[] phones;
        phoneBookSize = 0;
    }

};

int main()
{
    PhoneBook phoneBook;
    int size;

    do {
        cout << "Enter the size of your phone book: ";
        cin >> size;

        if (size > 0)
        {
            phoneBook.setSize(size);
            for (int i = 0; i < size; i++)
            {
                string name, phone;
                cout << "Enter name " << i + 1 << ": " << endl;
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone " << i + 1 << ": " << endl;
                cin >> phone;
                phoneBook.addEntry(name, phone);
            }

            break;
        }

        else if (size == 0)
        {
            cout << "No contacts in the phone book." << endl;
        }
        else
        {
            cout << "Please enter a positive number." << endl;
        }
    }

    while (true);
    int choice;

    do {
        cout << "Phone Book Menu" << endl;
        cout << "1. Display all phone book" << endl;
        cout << "2. Search for entry by name" << endl;
        cout << "3. Search for entry by phone" << endl;
        cout << "4. Find an entry by index" << endl;
        cout << "5. Update name by index" << endl;
        cout << "6. Update phone by index" << endl;
        cout << "7. Copy phone book to another and display entries of the new phone book " << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                phoneBook.displayAll();
                break;

            case 2:
            {
                string name;
                cout << "Enter name to search: ";
                cin >> name;

                bool isMatch = phoneBook.findByName(name);

                if (isMatch)
                {
                    cout << "True" << endl;
                }
                else
                {
                    cout << "False" << endl;
                }

                break;
            }

            case 3:
            {
                string phone;
                cout << "Enter phone number to search: ";
                cin >> phone;
                string foundName = phoneBook.findByPhone(phone);
                if (!foundName.empty())
                {
                    cout << "Found Name: " << foundName << endl;
                }
                else
                {
                    cout << "Phone not found." << endl;
                }
                break;
            }

            case 4:
            {
                int index;
                cout << "Enter index of entry to display: ";
                cin >> index;
                phoneBook.displayEntryAtIndex(index);
                break;
            }

            case 5:
            {
                int index;
                string newName;
                cout << "Enter index of entry to update: ";
                cin >> index;

                cout << "Enter new name: ";
                cin >> newName;

                if (phoneBook.updateNameAt(newName, index))
                {
                    cout << "Name updated successfully." << endl;
                }
                else
                {
                    cout << "Invalid index." << endl;
                }
                break;
            }

            case 6:
            {
                int index;
                string newPhone;
                cout << "Enter index of entry to update: ";
                cin >> index;
                cout << "Enter new phone number: ";
                cin >> newPhone;
                if (phoneBook.updatePhoneAt(newPhone, index))
                {
                    cout << "Phone number updated successfully." << endl;
                }
                else
                {
                    cout << "Invalid index." << endl;
                }
                break;
            }

            case 7:
            {
                PhoneBook newPhoneBook;
                newPhoneBook.copyPB(phoneBook);
                cout << "Entries in the new phone book: " << endl;
                newPhoneBook.displayAll();
                newPhoneBook.clear();
                break;
            }

            case 8:
                cout << "Thank you for using the program." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } while (choice != 8);

    phoneBook.clear();
    return 0;
}

