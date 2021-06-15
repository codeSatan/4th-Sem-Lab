/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
15) Implement the classes for the following inheritance hierarchies.
Create an interface “Shape” that contains methods ‘area’, ‘draw’, ‘rotate’, ‘move’ etc. Now
create two classes “Circle” and “Rectangle” that implement this ‘Shape’ interface and implement
the methods ‘area’, ‘move’, etc. Write a main() function to create two “Circle” and three
“Rectangle”,then move them. Print the details of circles and rectangles before after moving them.
 */

import static java.lang.Math.*;
import java.util.Random;

/* utility class for storing a bi-coordinate point */
class Point {
    double x, y;

    Point(double x, double y) {
        this.x = x;
        this.y = y;
    }
}

interface Shape {
    void area();

    void draw();

    void rotate(double theta); // theta in degrees

    void move(double dx, double dy); // V(x,y) ---> V(x+dx,y+dy)
}

class Circle implements Shape {

    private double x, y; // centre of circle
    private double radius; // radius of circle

    Circle(Point center, double radius) {
        this.x = center.x;
        this.y = center.y;
        this.radius = radius;
    }

    @Override
    public void area() {
        double area = 3.14 * radius * radius;
        System.out.println("Area of circle is " + area);
    }

    @Override
    public void draw() {
        System.out.println("Drawing Circle...");
    }

    @Override
    public void rotate(double theta) {
        System.out.println("Circle rotation does not change the geometry of the circle");
    }

    @Override
    public void move(double dx, double dy) {
        x += dx;
        y += dy;
        System.out.println("New center of circle after translation is: (" + x + "," + y + ")");
    }
}

class Rectangle implements Shape {

    private double X[], Y[]; // coordinates of rectangle in same order

    Rectangle(Point P[]) {
        X = new double[4];
        Y = new double[4];
        for (int i = 0; i < 4; i++) {
            X[i] = P[i].x;
            Y[i] = P[i].y;
        }
    }

    @Override
    public void area() {
        double length = sqrt((X[1] - X[0]) * (X[1] - X[0]) + (Y[1] - Y[0]) * (Y[1] - Y[0]));
        double width = sqrt((X[3] - X[2]) * (X[3] - X[2]) + (Y[3] - Y[2]) * (Y[3] - Y[2]));
        double area = length * width;
        System.out.println("Area of rectangle is " + area);
    }

    @Override
    public void draw() {
        System.out.println("Drawing Rectangle...");
    }

    @Override
    public void rotate(double theta) {
        // assuming pure rotation
        theta = theta * 0.0174533; // theta is assumed as degrees
        for (int i = 0; i < 4; i++) {
            double x = X[i], y = Y[i];
            X[i] = x * cos(theta) - y * sin(theta);
            Y[i] = x * sin(theta) + y * cos(theta);
        }
        System.out.println("New vertex positions of rectangle after pure rotation are: ");
        for (int i = 0; i < 4; i++) {
            System.out.println("(" + X[i] + "," + Y[i] + ")");
        }
    }

    @Override
    public void move(double dx, double dy) {
        // assuming pure translation of all vertices
        for (int i = 0; i < 4; i++) {
            X[i] += dx;
            Y[i] += dy;
        }
        System.out.println("New vertex positions of rectangle after translation are: ");
        for (int i = 0; i < 4; i++) {
            System.out.println("(" + X[i] + "," + Y[i] + ")");
        }
    }
}

class Main_Q15 {
    public static void main(String[] args) {
        // circles
        double r1 = 1.5, r2 = 4.6;
        Point cent1 = new Point(0, 0), cent2 = new Point(-2, 5);
        Circle c1 = new Circle(cent1, r1), c2 = new Circle(cent2, r2);
        c1.area();
        c2.move(-5, -4);
        System.out.println();

        c2.area();
        c1.move(10, -3);
        System.out.println();

        // rectangles
        Rectangle R[] = new Rectangle[3];
        for (int i = 0; i < 3; i++) {
            Point P[] = new Point[4];
            for (int j = 0; j < 4; j++) {
                double x = random() * 5, y = random() * 5;
                P[j] = new Point(x, y);
            }
            R[i] = new Rectangle(P);
            R[i].area();
            Random rand = new Random();
            R[i].move(rand.nextDouble(), rand.nextDouble());
            System.out.println();
        }
    }
}
