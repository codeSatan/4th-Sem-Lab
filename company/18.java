/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
18) Write two interfaces “Fruit” and “Vegetable” containing methods ‘hasAPeel’ and
‘hasARoot’. Now write a class “Tomato” implementing Fruit and Vegetable. Instantiate an object
of Tomato. Print the details of this object.
*/

interface Fruit {
    void hasAPeel();
}

interface Vegetable {
    void hasARoot();
}

class Tomato implements Fruit, Vegetable {

    private boolean hasRoot, hasPeel;

    Tomato(boolean hasRoot, boolean hasPeel) {
        this.hasRoot = hasRoot;
        this.hasPeel = hasPeel;
    }

    @Override
    public void hasARoot() {
        System.out.println("Tomato has root: " + hasRoot);
    }

    @Override
    public void hasAPeel() {
        System.out.println("Tomato has peel: " + hasPeel);
    }
}

class Main_Q18 {
    public static void main(String[] args) {
        Tomato obj = new Tomato(true, true);
        obj.hasARoot();
        obj.hasAPeel();
    }
}
