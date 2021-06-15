/*
*NAME: Suman Mondal
*Roll No: 001911001014
*Information Technology 2nd Semester
*/

 /* 3) Write a class “Box” that with three member-variables “height”, “width” and
 * “breadth”. Write suitable constructors to initialize them. Add functions like
 * “getVolume” and “getArea” that will return volume and surface area
 * respectively. Instantiate two arbitrary boxes and then print their volume and
 * surface area.
 */

class Box {
    private double height, width, breadth;

    public Box(double height, double width, double breadth) {
        this.height = height;
        this.breadth = breadth;
        this.width = width;
    }

    double getVolume() {
        return this.breadth * this.width * this.height;
    }

    double getArea() {
        return 2 * (this.breadth * this.height + this.height * this.width + this.width * this.breadth);
    }

    public static void main(String[] args) {
        Box b1 = new Box(3, 4, 5);
        Box b2 = new Box(6, 6, 6);
        System.out.println("Volume of Box 1 = " + b1.getVolume());
        System.out.println("Area of Box 1 = " + b1.getArea());
        System.out.println("Volume of Box 2 = " + b2.getVolume());
        System.out.println("Area of Box 2 = " + b2.getArea());
    }
}