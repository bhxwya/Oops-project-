#include <iostream>
#include <string>

using namespace std;

class SchoolMember {
protected:
    string name;
    int age;

public:
    SchoolMember(string name, int age) : name(name), age(age) {}

    virtual void displayDetails() const = 0;

    string getName() const { return name; }
    int getAge() const { return age; }

    void setName(const string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
};

class Alumni : public SchoolMember {
private:
    string graduationYear;

public:
    Alumni(string name, int age, string graduationYear) 
        : SchoolMember(name, age), graduationYear(graduationYear) {}

    void displayDetails() const override {
        cout << "Alumni Name: " << name << "\nAge: " << age << "\nGraduation Year: " << graduationYear << endl;
    }

    string getGraduationYear() const { return graduationYear; }
    void setGraduationYear(const string& newYear) { graduationYear = newYear; }
};

class Teacher : public SchoolMember {
private:
    string subject;

public:
    Teacher(string name, int age, string subject) 
        : SchoolMember(name, age), subject(subject) {}

    void displayDetails() const override {
        cout << "Teacher Name: " << name << "\nAge: " << age << "\nSubject: " << subject << endl;
    }

    string getSubject() const { return subject; }
    void setSubject(const string& newSubject) { subject = newSubject; }
};

class Student : public SchoolMember {
private:
    string grade;

public:
    Student(string name, int age, string grade) 
        : SchoolMember(name, age), grade(grade) {}

    void displayDetails() const override {
        cout << "Student Name: " << name << "\nAge: " << age << "\nGrade: " << grade << endl;
    }

    string getGrade() const { return grade; }
    void setGrade(const string& newGrade) { grade = newGrade; }
};

class SchoolDatabase {
private:
    SchoolMember* members[100];
    int count;

public:
    SchoolDatabase() : count(0) {}

    void addMember(SchoolMember* member) {
        if (count < 100) {
            members[count++] = member;
        } else {
            cout << "Database is full!" << endl;
        }
    }

    void removeMember(const string& name) {
        for (int i = 0; i < count; i++) {
            if (members[i]->getName() == name) {
                delete members[i];
                for (int j = i; j < count - 1; j++) {
                    members[j] = members[j + 1];
                }
                count--;
                cout << "Member " << name << " removed successfully." << endl;
                return;
            }
        }
        cout << "Member not found!" << endl;
    }

    void updateMember(const string& name) {
        for (int i = 0; i < count; i++) {
            if (members[i]->getName() == name) {
                if (Alumni* alumni = dynamic_cast<Alumni*>(members[i])) {
                    string newYear;
                    cout << "Enter new graduation year: ";
                    cin >> newYear;
                    alumni->setGraduationYear(newYear);
                } else if (Teacher* teacher = dynamic_cast<Teacher*>(members[i])) {
                    string newSubject;
                    cout << "Enter new subject: ";
                    cin >> newSubject;
                    teacher->setSubject(newSubject);
                } else if (Student* student = dynamic_cast<Student*>(members[i])) {
                    string newGrade;
                    cout << "Enter new grade: ";
                    cin >> newGrade;
                    student->setGrade(newGrade);
                }
                cout << "Details updated successfully." << endl;
                return;
            }
        }
        cout << "Member not found!" << endl;
    }

    void displayAllMembers() const {
        if (count == 0) {
            cout << "No members in the database." << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            members[i]->displayDetails();
            cout << endl;
        }
    }

    void searchMember(const string& name) const {
        for (int i = 0; i < count; i++) {
            if (members[i]->getName() == name) {
                members[i]->displayDetails();
                return;
            }
        }
        cout << "Member not found!" << endl;
    }

    void displayMemberCount() const {
        int alumniCount = 0, teacherCount = 0, studentCount = 0;
        for (int i = 0; i < count; i++) {
            if (dynamic_cast<Alumni*>(members[i])) alumniCount++;
            else if (dynamic_cast<Teacher*>(members[i])) teacherCount++;
            else if (dynamic_cast<Student*>(members[i])) studentCount++;
        }
        cout << "Total Alumni: " << alumniCount << endl;
        cout << "Total Teachers: " << teacherCount << endl;
        cout << "Total Students: " << studentCount << endl;
    }

    void sortMembersByName() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (members[i]->getName() > members[j]->getName()) {
                    swap(members[i], members[j]);
                }
            }
        }
        cout << "Members sorted by name." << endl;
    }

    int getMemberCount() const { return count; }
    SchoolMember* getMember(int index) const { return members[index]; }
};

int main() {
    SchoolDatabase db;

    db.addMember(new Alumni("Aarav", 32, "2010"));
    db.addMember(new Teacher("Neha", 40, "Science"));
    db.addMember(new Student("Ishaan", 17, "11th Grade"));
    db.addMember(new Student("Ananya", 19, "Undergraduate"));
    db.addMember(new Teacher("Ravi", 45, "Mathematics"));
    db.addMember(new Alumni("Simran", 28, "2015"));

    int choice;
    string name;

    while (true) {
        cout << "\nSchool Alumni System Menu:\n";
        cout << "1. Display All Members\n";
        cout << "2. Search Member by Name\n";
        cout << "3. Update Member Details\n";
        cout << "4. Remove Member\n";
        cout << "5. Display Member Count\n";
        cout << "6. Sort Members by Name\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                db.displayAllMembers();
                break;

            case 2:
                cout << "Enter the name of the member: ";
                cin.ignore();
                getline(cin, name);
                db.searchMember(name);
                break;

            case 3:
                cout << "Enter the name of the member to update: ";
                cin.ignore();
                getline(cin, name);
                db.updateMember(name);
                break;

            case 4:
                cout << "Enter the name of the member to remove: ";
                cin.ignore();
                getline(cin, name);
                db.removeMember(name);
                break;

            case 5:
                db.displayMemberCount();
                break;

            case 6:
                db.sortMembersByName();
                break;

            case 7:
                for (int i = 0; i < db.getMemberCount(); i++) {
                    delete db.getMember(i);
                }
                return 0;

            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
