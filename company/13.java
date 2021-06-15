/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
13) Implement a class for a “Person”. Person has data members ‘age’, ’weight’, ‘height’,
‘dateOfBirth’, ‘address’ with proper reader/write methods etc. Now create two subclasses
“Employee” and “Student”. Employee will have additional data member ‘salary’,
‘dateOfJoining’, ‘experience’ etc. Student has data members ‘roll’, ‘listOfSubjects’, their marks
and methods ‘calculateGrade’. Again create two sub-classes “Technician” and “Professor” from
Employee. Professor has data members ‘courses’, ‘listOfAdvisee’ and their add/remove
methods. Write a main() function to demonstrate the creation of objects of different classes and
their method calls.
*/

import java.util.HashMap;
import java.util.HashSet;

class Date {
    int day, month, year;

    public Date() {
        day = 1;
        month = 1;
        year = 1970;

    }

    public Date(int day) {
        if (day > 31 || day <= 0) {
            System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
        } else {
            this.day = day;
            month = 1;
            year = 1970;
        }
    }

    public Date(int day, int month) {

        this.year = 1970;

        if (month > 12 || month <= 0) {
            System.out.print("\n\n\nInvalid month, could not create object !!\n");
            return;
        }

        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            if (day > 31 || day <= 0) {
                System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
            }

        } else if (month == 2) {
            if (this.isLeapYear()) {
                if (day > 29 || day < 0) {
                    System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
                }

            } else {
                if (day > 28 || day < 0) {
                    System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
                }
            }

        } else {
            if (day > 30 || day < 0) {
                System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
            }
        }

        this.day = day;
        this.month = month;

    }

    public Date(int day, int month, int year) {
        this.year = year;

        if (month > 12 || month <= 0) {
            System.out.print("\n\n\nInvalid month, could not create object !!\n");
            return;
        }

        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            if (day > 31 || day <= 0) {
                System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
            }

        } else if (month == 2) {
            if (this.isLeapYear()) {
                if (day > 29 || day < 0) {
                    System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
                }

            } else {
                if (day > 28 || day < 0) {
                    System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
                }
            }

        } else {
            if (day > 30 || day < 0) {
                System.out.print("\n\n\nInvalid day !!\nCould not create object of date!!\n\n");
            }
        }

        this.day = day;
        this.month = month;
    }

    public boolean isLeapYear() {

        boolean isLeapYear = false;
        if (year % 4 == 0) {

            if (year % 100 == 0) {

                if (year % 400 == 0)
                    isLeapYear = true;
                else
                    isLeapYear = false;
            }

            isLeapYear = true;

        } else
            isLeapYear = false;

        return isLeapYear;
    }

    public String toString() {
        String d = new String();
        if (day < 10)
            d += '0';

        d += day + "-";

        if (month < 10)
            d += '0';
        d += month + "-" + year;

        return d;
    }

    private boolean isLastDayOfMonth() {

        if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                && day == 31)
            return true;

        else if (this.isLeapYear() && month == 2 && day == 29)
            return true;
        else if (day == 30)
            return true;

        return false;
    }

    private boolean isLastMonthOfYear() {
        if (month == 12)
            return true;
        else
            return false;
    }

    private int lastDayOfMonth() {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            return 31;

        if (month == 2) {
            if (this.isLeapYear())
                return 29;
            else
                return 28;
        } else
            return 30;

    }

    public Date nextDay() {
        int d = day, m = month, y = year;

        if (this.isLastDayOfMonth()) {
            if (!isLastMonthOfYear()) {
                d = 1;
                m++;

            } else {
                d = 1;
                month = 1;
                year++;
            }
        } else {
            d++;
        }

        return new Date(d, m, y);

    }

    public Date previousDay() {
        int d = day, m = month, y = year;

        if (day == 1) {
            if (month == 1) {
                d = 31;
                m = 12;
                y--;
            } else {

                Date temp = new Date(d, m - 1, y);
                d = temp.lastDayOfMonth();
                m = month - 1;
            }
        } else
            d--;

        return new Date(d, m, y);
    }

}

class Person {

    String name;
    int age;
    double weight;
    double height;
    Date dob;
    String address;

    public Person(String name, int age, double weight, double height, Date dob, String address) {
        this.name = name;
        this.age = age;
        this.weight = weight;
        this.height = height;
        this.dob = dob;
        this.address = address;
    }

    public void display() {
        System.out.print("\nName : " + name);
        System.out.print("\nAge : " + age);
        System.out.print("\nHeight : " + height + " meter");
        System.out.print("\nWeight : " + weight + " kg");
        System.out.print("\nDate of birth : " + dob);
        System.out.print("\nAddress : " + address);
    }
}

class Employee_ extends Person {
    double salary;
    Date dateOfJoining;
    int daysOfExperience;

    public Employee_(String name, int age, double weight, double height, Date dob, String address, double salary,
                     Date dateOfJoining, int daysOfExperience) {
        super(name, age, weight, height, dob, address);

        this.salary = salary;
        this.dateOfJoining = dateOfJoining;
        this.daysOfExperience = daysOfExperience;
    }

    @Override
    public void display() {

        System.out.print("\nEmployee details:\n___________________________");
        super.display();
        System.out.print("\nSalary : " + salary + " rupees per month !!");
        System.out.print("\nDate of Joining : " + dateOfJoining);
        System.out.print("\nNo of experience days: " + daysOfExperience);
    }
}

class Student_ extends Person {
    int rollNumber;

    HashMap<String, Integer> subjectMarks;

    public Student_(String name, int age, double weight, double height, Date dob, String address, int rollNumber) {

        super(name, age, weight, height, dob, address);
        this.rollNumber = rollNumber;

        this.subjectMarks = new HashMap<>();

    }

    public void addSubject(String subName, int marks) {

        if (subjectMarks.containsKey(subName)) {

            System.out.print("\nAlready contains this subject " + subName + ", can not add this subject sorry :(\n");
        } else {

            subjectMarks.put(subName, marks);
        }

    }

    public void modifyMarks(String subName, int newMarks) {

        if (!subjectMarks.containsKey(subName)) {

            System.out.print(
                    "\nSubject with subject name " + subName + " does not exist, can not modify marks sorry :(\n");
        } else {

            subjectMarks.put(subName, newMarks);
        }

    }

    public int totalMarks() {
        int sum = 0;

        for (String subName : subjectMarks.keySet()) {
            sum += subjectMarks.get(subName);
        }
        return sum;
    }

    public char calculateGrade() {

        int noOfSub = subjectMarks.size();
        int total = totalMarks() / noOfSub;

        if (total >= 90 && total <= 100)
            return 'S';

        else if (total >= 80 && total < 90)
            return 'A';
        else if (total >= 70 && total < 80)
            return 'B';
        else if (total >= 60 && total < 70)
            return 'C';
        else if (total >= 50 && total < 60)
            return 'D';
        else if (total >= 40 && total < 50)
            return 'E';
        else
            return 'F';

    }

    @Override
    public void display() {
        System.out.print("\nStudent details:\n_______________________");
        super.display();

        System.out.print("\nRoll Number : " + rollNumber);
        System.out.print("\nMarks of each subject :");

        for (String subName : subjectMarks.keySet()) {
            System.out.print("\n" + subName + " : " + subjectMarks.get(subName));
        }

        int total = totalMarks();
        System.out.print("\nTotal marks : " + total);
        System.out.print("\nCurrent Grade : " + calculateGrade());

    }
}

class Technician extends Person {

    public Technician(String name, int age, double weight, double height, Date dob, String address) {
        super(name, age, weight, height, dob, address);
    }

    @Override
    public void display() {
        System.out.print("\nTechnician details:\n__________________________");
        super.display();
    }
}

class Professor extends Person {

    HashSet<String> course;

    public Professor(String name, int age, double weight, double height, Date dob, String address,
                     String courseNames[]) {

        super(name, age, weight, height, dob, address);

        course = new HashSet<>();
        for (int i = 0; i < courseNames.length; i++) {

            course.add(courseNames[i]);
        }

    }

    @Override
    public void display() {
        System.out.print("\n\nProfessor Details:\n_________________________");

        super.display();

        System.out.print("\nCourse list:   ");

        for (String s : course)
            System.out.print(s + " , ");
    }

}

class Main_Q13 {
    public static void main(String arg[]) {

        Person p = new Person("Amy Santiago", 44, 67, 1.81, new Date(11, 2, 1987), "Brooklyn");

        System.out.print("Person Details:\n_________________________");
        p.display();

        Student_ s = new Student_("Terry Jeffords", 20, 70, 1.65, new Date(8, 7, 2000), "New York", 31);
        s.addSubject("Maths", 80);
        s.addSubject("OOS", 81);
        s.addSubject("DSA", 82);
        s.addSubject("DBMS", 83);

        s.modifyMarks("OOS", 84);
        System.out.print("\n\n\n\n");
        s.display();

        Employee_ e = new Employee_("Charles Boyle", 123, 456, 789, new Date(1, 2, 1958), "Ex's Basement", 123,
                new Date(1, 2, 2021), 100);
        System.out.print("\n\n\n\n");
        e.display();

        Technician t = new Technician("Raymond Holt", 123, 456, 789, new Date(1, 1, 1961), "Brooklyn-Nine-Nine");
        System.out.print("\n\n\n\n");
        t.display();

        Professor prof = new Professor("Kevin Cotzner", 123, 14213, 123, new Date(2, 3, 1962), "UC Riverside",
                new String[] { "DBMS", "OOS", "DSA", "Maths" });
        System.out.print("\n\n\n\n");
        prof.display();

    }

}
