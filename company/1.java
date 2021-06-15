/*
NAME: Suman Mondal
Roll No: 001911001014
Information Technology 2nd Semester
*/

/*
1) Create a class “Room” which will hold the “height”, “width” and “breadth” of the room in three fields.
This class also has a method “volume()” to calculate the volume of this room.
Create another class “RoomDemo” which will use the earlier class, create instances of rooms,
and display the volume of room
*/

class Room {

    private double height;
    private double width;
    private double breadth;

    public Room(double height, double width, double breadth) {
        this.height = height;
        this.width = width;
        this.breadth = breadth;
    }

    double volume() {
        return this.breadth * this.height * this.width;
    }
}

class RoomDemo {
    public static void main(String[] args) {
        Room r1 = new Room(3, 4, 5);
        Room r2 = new Room(1.5, 2.3, 4.8);
        System.out.println("Volume of Room 1 = " + r1.volume());
        System.out.println("Volume of Room 2 = " + r2.volume());
    }
}