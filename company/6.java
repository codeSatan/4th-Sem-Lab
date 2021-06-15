/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/**
 * 6) Write a class to represent complex numbers with necessary constructors.
 * Write member functions to add, multiply two complex numbers. There should be
 * three constructors: (i) to initialize real and imaginary parts to 0; (ii) to
 * initialize imaginary part to 0 but to initialize the real part to user
 * defined value; (iii) to initialize the real part and the imaginary part to
 * user defined values. Also, write a main() function to (i) create two complex
 * numbers 3+2i and 4-2i; (ii) to print the sum and product of those numbers.
 */

class Complex {
    private double x, y;

    public Complex() {
        this.x = this.y = 0;
    }

    public Complex(double x) {
        this.x = x;
        this.y = 0;
    }

    public Complex(double x, double y) {
        this.x = x;
        this.y = y;
    }

    static Complex add(Complex c1, Complex c2) {
        Complex temp = new Complex(c1.x + c2.x, c1.y + c2.y);
        return temp;
    }

    void add(Complex c) {
        // inplace addition
        this.x += c.x;
        this.y += c.y;
    }

    static Complex multiply(Complex c1, Complex c2) {
        Complex temp = new Complex(c1.x * c2.x - c1.y * c2.y, c1.x * c2.y + c1.y * c2.x);
        return temp;
    }

    void multiply(Complex cm) {
        // inplace addition
        double a = this.x, b = this.y, c = cm.x, d = cm.y;
        this.x = a * c - b * d;
        this.y = a * d + b * c;
    }

    void print() {
        if (this.y < 0)
            System.out.println(this.x + "" + this.y + "i");
        else
            System.out.println(this.x + "+" + this.y + "i");
    }

    public static void main(String[] args) {
        Complex c1 = new Complex(7, 5);
        Complex c2 = new Complex(8, -1);
        Complex c3 = add(c1, c2);
        Complex c4 = multiply(c1, c2);
        c3.print();
        c4.print();

        // inplace
        c1.add(c2);
        c3.multiply(c4);
        c1.print();
        c3.print();
    }
}
