#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student
{
public:
    int roll;
    char name[50];
    float marks;

    void input()
    {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const
    {
        cout << setw(10) << roll
             << setw(20) << name
             << setw(10) << marks << endl;
    }
};

void addStudent()
{
    Student s;
    ofstream out("student.txt", ios::binary | ios::app);
    s.input();
    out.write(reinterpret_cast<char *>(&s), sizeof(s));
    out.close();
    cout << "Student Added Successfully!\n";
}

void updateStudent()
{
    Student s;
    int r;
    bool found = false;

    fstream file("student.txt", ios::binary | ios::in | ios::out);

    cout << "Enter Roll Number to Update: ";
    cin >> r;

    while (file.read(reinterpret_cast<char *>(&s), sizeof(s)))
    {
        if (s.roll == r)
        {
            cout << "Existing Record:\n";
            s.display();

            cout << "\nEnter New Details:\n";
            s.input();

            int pos = file.tellg() - sizeof(s);
            file.seekp(pos);
            file.write(reinterpret_cast<char *>(&s), sizeof(s));

            found = true;
            cout << "Record Updated Successfully!\n";
            break;
        }
    }

    if (!found)
        cout << "Student Not Found!\n";

    file.close();
}

void deleteStudent()
{
    Student s;
    int r;
    bool found = false;

    ifstream in("student.txt", ios::binary);
    ofstream out("temp.txt", ios::binary);

    cout << "Enter Roll Number to Delete: ";
    cin >> r;

    while (in.read(reinterpret_cast<char *>(&s), sizeof(s)))
    {
        if (s.roll == r)
        {
            found = true;
        }
        else
        {
            out.write(reinterpret_cast<char *>(&s), sizeof(s));
        }
    }

    in.close();
    out.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        cout << "Student Deleted Successfully!\n";
    else
        cout << "Student Not Found!\n";
}

void displayAll()
{
    Student s;
    ifstream in("student.txt", ios::binary);

    cout << setw(10) << "Roll"
         << setw(20) << "Name"
         << setw(10) << "Marks" << endl;

    while (in.read(reinterpret_cast<char *>(&s), sizeof(s)))
    {
        s.display();
    }
    in.close();
}

void searchStudent()
{
    Student s;
    int r;
    bool found = false;
    ifstream in("student.txt", ios::binary);

    cout << "Enter Roll Number to Search: ";
    cin >> r;

    while (in.read(reinterpret_cast<char *>(&s), sizeof(s)))
    {
        if (s.roll == r)
        {
            cout << "Student Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student Not Found!\n";

    in.close();
}

int main()
{
    int choice;
    do
    {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
