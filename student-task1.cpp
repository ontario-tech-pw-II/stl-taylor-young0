// Student class is implemented based on string and do not need any change

#include <iostream>
#include <string>
#include <list>

using namespace std;

// ----------------------------- Base class

class Person{
  protected:
    string name;

  public:
    void setname(char const *);
    string getname();


    Person();         // default constructor
    Person(const char *);
    Person(const Person &);     // copy constructor

    Person(const string &);

    virtual ~Person();

};

void Person::setname(char const *n)
{
  name = n;
}

string Person::getname()
{
  return name;
}


Person::Person()
{
  name = "";
}

Person::Person(char const *n)
{
  setname(n);
}

Person::Person(const string & n)
{
  name = n;
}

Person::~Person()
{
}

Person::Person(const Person &t):name(t.name)
{
}

// -----------------------------  Student class

class Student : public Person{
  private:
    double grade;

  public:

        void setgrade(double);
        double getgrade();

        Student();    // default constructor
    Student(char const *, double);
    Student(const Student &);  // copy constructor

    ~Student();

  friend ostream & operator<<(ostream &, const Student &);

};

void Student::setgrade(double g)
{
  grade =g;
}

double Student::getgrade()
{
  return grade;
}

ostream & operator<<(ostream & out, const Student & s)
{
    out << s.name << "," << s.grade;
    return out;

}

Student::Student(): grade(0)
{
}

Student::Student(char const *n, double g): Person(n)
{
  setgrade(g);
}

Student::Student(const Student &t):Person(t.name)
{
  grade = t.grade;
}

Student::~Student()
{
}

int main() {
  list<Student> students;
  list<Student>::iterator i;
  bool moreToEnter = true;
  string name;
  double grade;

  // Allow the user to enter more students while they have more to enter
  while (moreToEnter) {
    cout << "Please enter student name (or DONE to stop): ";
    cin >> name;

    // Make sure we have another student to add
    if (name != "DONE") {
      cout << "Please enter student grade: ";
      cin >> grade;

      // Create the new Student
      Student s = Student(name.c_str(), grade);

      // Loop through each student until we have inserted it
      i = students.begin();
      bool inserted = false;
      while (!inserted) {
        // Find the correct spot to insert the student in the list
        // This will either occur at the end, or when we find one with
        // a grade value greater than the one just made (Student s)
        if (i == students.end() || s.getgrade() < (*i).getgrade()) {
          students.insert(i, s);
          // Stop the loop, we have found and inserted into our spot
          inserted = true;
        }
        i++;
      }
    } else {
      // User has entered DONE, meaning that they entered all their students
      moreToEnter = false;
    }
  }

  // Print out the students in ascending order
  cout << "Printing out the students in ascending order..." << '\n';
  for (i = students.begin(); i != students.end(); ++i) {
    cout << (*i);
    cout << '\n';
  }
  cout << '\n';

  // Print out the students in descending order
  cout << "Printing out the students in descending order..." << '\n';
  list<Student>::reverse_iterator j;
  for (j = students.rbegin(); j != students.rend(); ++j) {
    cout << (*j);
    cout << '\n';
  }
  cout << '\n';
}
