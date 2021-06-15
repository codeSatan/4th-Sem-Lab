/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/**
 * 9) Write a Java class “Employee” containing information name, id, address,
 * salary etc. Write necessary constructor and read/write methods. Create a
 * class “Dept” that has a name, location etc. The “Dept” contains a number of
 * “Employee”. Write methods “add” and “remove” to add and remove an employee
 * to/from this department. Write a main() function and create “Information
 * Technology” department. Add five employees and print yearly expenditure for
 * this department.
 */

class Employee {
    private String name, address;
    private int id;
    private double salary;

    public Employee(String name, int id, String address, double salary) {
        this.name = name;
        this.id = id;
        this.address = address;
        this.salary = salary;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return this.id;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getAddress() {
        return this.address;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public double getSalary() {
        return this.salary;
    }

    public void printEmployeeDetails() {
        if (this != null) {
            System.out.println("Name: " + this.getName());
            System.out.println("ID: " + this.getId());
            System.out.println("Address: " + this.getAddress());
            System.out.println("Salary: " + this.getSalary());
        }
    }
}

class Dept {
    private String name, location;
    private Employee[] employees;
    private int size, idx;

    public Dept(String name, String location, int size) {
        this.name = name;
        this.location = location;
        this.size = size;
        this.employees = new Employee[this.size];
        idx = -1;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public String getLocation() {
        return this.location;
    }

    public void add(Employee e) {
        if (idx == -1) {
            // department is empty
            employees[++idx] = e;
            System.out.println("Employee added successfully: " + e.getName());
        } else {
            int flag = 0;
            for (int i = 0; i <= idx; i++) {
                if (employees[i] == null) {
                    employees[i] = e;
                    flag = 1;
                    System.out.println("Employee added successfully: " + e.getName());
                    break;
                }
            }
            if (flag == 0) {
                // no intermediate space left
                if (idx < size - 1) {
                    employees[++idx] = e;
                    System.out.println("Employee added successfully: " + e.getName());
                } else {
                    // department is full
                    System.out.println("Department is full !");
                }
            }
        }
    }

    public void remove(int id) {
        if (idx == -1) {
            System.out.println("Department is empty !");
        } else {
            int flag = 0;
            for (int i = 0; i < size; i++) {
                if (employees[i] != null && id == employees[i].getId()) {
                    employees[i] = null;
                    flag = 1;
                    System.out.println("Employee records deleted successfully for ID: " + id);
                    break;
                }
            }
            if (flag == 0) {
                System.out.println("Employee not found !");
            }
        }
    }

    public void printDepartment() {
        System.out.println("\nDepartMent: " + this.getName() + " ");
        for (int i = 0; i < this.size; i++) {
            if (this.employees[i] != null) {
                this.employees[i].printEmployeeDetails();
                System.out.println();
            }
        }
        System.out.println();
    }

    public double totExpenditure() {
        double tot = 0.0;
        for (int i = 0; i < this.size; i++) {
            if (employees[i] != null)
                tot += employees[i].getSalary();
        }
        return tot;
    }
}

class Main_Q9 {
    public static void main(String[] args) {
        Employee e1 = new Employee("Mickey Mouse", 169, "Disneyland", 15000.00);
        Employee e2 = new Employee("Gol D. Roger", 001, "LaughTale", 25000.00);
        Employee e3 = new Employee("Sasuke Uchiha", 718, "Leaf Village", 30000.00);
        Employee e4 = new Employee("Mikasa Ackermann", 47, "Eldia", 100000.00);
        Employee e5 = new Employee("Tobio Kageyama ", 167, "Karasuno", 41000.00);
        Employee e6 = new Employee("Light Yagami", 61, "Tokyo", 3600.00);

        Dept dept = new Dept("Animation Studies", "Akihabara", 5);

        dept.add(e1);
        dept.add(e2);
        dept.add(e3);
        dept.add(e4);
        dept.add(e5);

        dept.printDepartment();
        // print total expenditure of department
        System.out.println("Total expenditure of department at given time = " + dept.totExpenditure());
        System.out.println("\n\n");

        dept.remove(447);
        dept.remove(169);
        dept.add(e6);

        dept.printDepartment();

        // print total expenditure of department
        System.out.println("Total expenditure of department at given time = " + dept.totExpenditure());
        System.out.println("\n\n");
    }
}