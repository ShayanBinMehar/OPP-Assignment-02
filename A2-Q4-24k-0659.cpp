#include <iostream>
#include <string>

using namespace std;

class User {
protected:
    string name;
    int ID;
    string email;
    unsigned long hashed_password;

public:
    User(const string& name, int ID, const string& email, const string& password)
        : name(name), ID(ID), email(email) {
        hashed_password = generateHash(password);
    }

    unsigned long generateHash(const string& password) const {
        unsigned long hash = 5381;
        for (char c : password) {
            hash = (hash * 33) + c;
        }
        return hash;
    }

    bool authenticate(const string& password) const {
        return hashed_password == generateHash(password);
    }

    virtual void display() const {
        cout << "Name: " << name << ", ID: " << ID << ", Email: " << email << endl;
    }

    virtual bool accessLab() const {
        return false;
    }

    string getName() const {
        return name;
    }

    virtual ~User() {}
};

class Student : public User {
protected:
    int assignments[10];

public:
    Student(const string& name, int ID, const string& email, const string& password)
        : User(name, ID, email, password) {
        for (int i = 0; i < 10; ++i) {
            assignments[i] = 0;
        }
    }

    void submitAssignment(int index) {
        if (index >= 0 && index < 10) {
            assignments[index] = 1;
        } else {
            cout << "Invalid assignment index!" << endl;
        }
    }

    void display() const override {
        User::display();
        cout << "Assignments Status: ";
        for (int i = 0; i < 10; ++i) {
            cout << assignments[i] << " ";
        }
        cout << endl;
    }
};

class TA : public Student {
private:
    Student* assigned_students[10];
    string projects[2];
    int assigned_student_count;
    int project_count;

public:
    TA(const string& name, int ID, const string& email, const string& password)
        : Student(name, ID, email, password), assigned_student_count(0), project_count(0) {}

    void assignStudent(Student* student) {
        if (assigned_student_count < 10) {
            assigned_students[assigned_student_count++] = student;
        }
    }

    void startProject(const string& project) {
        if (project_count < 2) {
            projects[project_count++] = project;
        }
    }

    void display() const override {
        Student::display();
        cout << "Assigned Students: " << assigned_student_count << ", Projects: " << project_count << endl;
    }

    bool accessLab() const override {
        return true;
    }
};

class Professor : public User {
private:
    TA* tas[10];
    int ta_count;

public:
    Professor(const string& name, int ID, const string& email, const string& password)
        : User(name, ID, email, password), ta_count(0) {}

    void workWithTA(TA* ta) {
        if (ta_count < 10) {
            tas[ta_count++] = ta;
        }
    }

    void display() const override {
        User::display();
        cout << "Number of TAs: " << ta_count << endl;
    }

    bool accessLab() const override {
        return true;
    }
};

void authenticateAndPerformAction(User* user, const string& action) {
    if (action == "access_lab" && user->accessLab()) {
        cout << user->getName() << " has access to the lab." << endl;
    } else {
        cout << user->getName() << " does not have permission for this action." << endl;
    }
}

int main() {
    Student student("Alice", 1, "alice@example.com", "password123");
    TA ta("Bob", 2, "bob@example.com", "password456");
    Professor professor("Dr. Smith", 3, "smith@example.com", "password789");

    student.display();
    ta.display();
    professor.display();

    student.submitAssignment(0);
    ta.assignStudent(&student);
    ta.startProject("Project A");
    professor.workWithTA(&ta);

    cout << endl << "Re-displaying TA and Professor info after changes:\n";
    ta.display();
    professor.display();

    cout << endl << "Lab Access Check:\n";
    authenticateAndPerformAction(&student, "access_lab");
    authenticateAndPerformAction(&ta, "access_lab");
    authenticateAndPerformAction(&professor, "access_lab");

    return 0;
}
