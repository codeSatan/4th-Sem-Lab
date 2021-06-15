/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
2) Write a program to implement a class “student” with the following members.
Name of the student.
Marks of the student obtained in three subjects.
Function to assign initial values.
Function to compute total average.
Function to display the student’s name and the total marks.
Write an appropriate main() function to demonstrate the functioning of the above.
*/


class Student{
    String studentName;
    double chem_marks;
    double maths_marks;
    double phy_marks;

    public void inintialize(String studentName, double chem_marks, double maths_marks, double phy_marks) {
        this.studentName = studentName;
        this.chem_marks = chem_marks;
        this.maths_marks = maths_marks;
        this.phy_marks = phy_marks;
    }

    public double calculateAverage(){
        return (chem_marks+phy_marks+maths_marks)/3;
    }
    public double calculateTotalMarks(){
        return chem_marks+phy_marks+maths_marks;
    }

    public static void main(String[] args) {
        Student student1 = new Student();
        Student student2 = new Student();
        Student student3 = new Student();

        student1.inintialize("Suman Mondal", 90,50,70);
        student2.inintialize("Avinandan Mondal", 70,59,90);
        student3.inintialize("Sayan Mondal", 93,100,78);

        System.out.println("Student 1: "+student1.studentName);
        System.out.println("Total Marks: "+ student1.calculateTotalMarks());
        System.out.println("Average: "+student1.calculateAverage());
        System.out.println();

        System.out.println("Student 2: "+student2.studentName);
        System.out.println("Total Marks: "+ student2.calculateTotalMarks());
        System.out.println("Average: "+student2.calculateAverage());
        System.out.println();

        System.out.println("Student 3: "+student3.studentName);
        System.out.println("Total Marks: "+ student3.calculateTotalMarks());
        System.out.println("Average: "+student3.calculateAverage());
        System.out.println();

    }
}