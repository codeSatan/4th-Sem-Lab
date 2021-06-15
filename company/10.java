/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
10) Implement a class for a “Student”. Information about a student includes name, roll no and an
array of five subject names. The class should have suitable constructor and get/set methods.
Implement a class “TabulationSheet”. A tabulation sheet contains roll numbers and marks of
each student for a particular subject. This class should have a method for adding the marks and
roll no of a student.
Implement a class “MarkSheet”. A mark sheet contains marks of all subjects for a particular
student. This class should have a method to add name of a student and marks in each subject.
Write a main() function to create three “Student” objects, Five “Tabulationsheet” objects for Five
subjects and three “Marksheet” object for three students. Print the mark sheets.
*/

import java.util.ArrayList;

class Main_Q10 {

    static class Student {
        private String name;
        private int roll;
        private String[] subjects;

        public Student(String name, int roll, String[] subjects) {
            this.name = name;
            this.roll = roll;
            this.subjects = new String[subjects.length];
            for (int i = 0; i < subjects.length; i++)
                this.subjects[i] = subjects[i];
        }

        public void setName(String name) {
            this.name = name;
        }

        public String getName() {
            return this.name;
        }

        public void setRoll(int roll) {
            this.roll = roll;
        }

        public int getRoll() {
            return this.roll;
        }

        public void setSubjects(String[] subjects) {
            this.subjects = new String[subjects.length];
            for (int i = 0; i < subjects.length; i++)
                this.subjects[i] = subjects[i];
        }

        public String[] getSubjects() {
            return this.subjects;
        }

        public void printStudentDetails() {
            if (this != null) {
                System.out.println("Name: " + this.getName());
                System.out.println("Roll: " + this.getRoll());
            }
        }
    }

    static class TabulationSheet {
        private ArrayList<Integer> rolls;
        private ArrayList<Double> marks;

        public TabulationSheet() {
            this.rolls = new ArrayList<>();
            this.marks = new ArrayList<>();
        }

        public void add(int roll, double mark) {
            rolls.add(roll);
            marks.add(mark);
        }

        public double getMarks(int idx) {
            return marks.get(idx);
        }
    }

    static class MarkSheet {
        private ArrayList<String> names;
        private ArrayList<TabulationSheet> tSheets;

        public MarkSheet() {
            this.names = new ArrayList<>();
            this.tSheets = new ArrayList<>();
        }

        public void add(String name, TabulationSheet tSheet) {
            names.add(name);
            tSheets.add(tSheet);
        }

        public TabulationSheet getTSheet(int idx) {
            return tSheets.get(idx);
        }
    }

    public static void main(String[] args) {

        String subjects[] = { "DSA", "Graph Theory", "Computer Networks", "DBMS", "OOS" };

        Student s1 = new Student("Suman Mondal", 15, subjects);
        Student s2 = new Student("Sayan Mondal", 12, subjects);
        Student s3 = new Student("Avinandan Mondal", 41, subjects);

        Student[] studs = { s1, s2, s3 };

        MarkSheet[] sheets = new MarkSheet[3];
        for (int i = 0; i < 3; i++) {
            sheets[i] = new MarkSheet();
            TabulationSheet tSheet = new TabulationSheet();
            for (int j = 0; j < 5; j++) {
                double marks = Math.random() * 100.0;
                tSheet.add(studs[i].getRoll(), marks);
            }
            sheets[i].add(studs[i].getName(), tSheet);
        }

        // printing the marksheets
        for (int i = 0; i < 3; i++) {
            studs[i].printStudentDetails();
            System.out.println("Marks in the five subjects:");
            TabulationSheet tSheet = sheets[i].getTSheet(0);
            for (int j = 0; j < 5; j++) {
                double marks = tSheet.getMarks(j);
                System.out.println(subjects[j] + " : " + marks);
            }
            System.out.println();
        }
    }
}