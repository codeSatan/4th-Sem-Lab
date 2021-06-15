/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
14) Create a base class “Automobile”. An Automobile contains data members ‘make’, ‘type’,
‘maxSpeed’, ‘price’, ‘mileage’, ‘registrationNumber’ etc. with their reader/writer methods. Now
create two sub-classes “Track” and “Car”. Track has data members ‘capacity’, ‘hoodType’,
‘noOfWheels’ etc. Car has data members ‘noOfDoors’, ‘seatingCapacity’ and their reader/writer
methods. Create a main() function to demonstrate this.
*/

class Automobile {
    int make, type, maxSpeed, price, mileage, registrationNumber;

    public Automobile(int make, int type, int maxSpeed, int price, int mileage, int registrationNumber) {
        this.make = make;
        this.type = type;
        this.maxSpeed = maxSpeed;
        this.price = price;
        this.mileage = mileage;
        this.registrationNumber = registrationNumber;
    }

    public int getMake() {
        return make;
    }

    public void setMake(int make) {
        this.make = make;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getMaxSpeed() {
        return maxSpeed;
    }

    public void setMaxSpeed(int maxSpeed) {
        this.maxSpeed = maxSpeed;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public int getMileage() {
        return mileage;
    }

    public void setMileage(int mileage) {
        this.mileage = mileage;
    }

    public int getRegistrationNumber() {
        return registrationNumber;
    }

    public void setRegistrationNumber(int registrationNumber) {
        this.registrationNumber = registrationNumber;
    }

    @Override
    public String toString() {
        return "\nMake Model: " + make + "\nMaximum Speed: " + maxSpeed + " kmph " + "\nMileage of Vehicle: " + mileage + "\nPrice: Rs." + price
                + "/-" + "\nRegistration Number: " + registrationNumber + "\nType of Vehicle: " + type;
    }

}

class Truck extends Automobile {
    int capacity, hoodType, noOfWheels;

    public Truck(int make, int type, int maxSpeed, int price, int mileage, int registrationNumber, int capacity,
                 int hoodType, int noOfWheels) {
        super(make, type, maxSpeed, price, mileage, registrationNumber);
        this.capacity = capacity;
        this.hoodType = hoodType;
        this.noOfWheels = noOfWheels;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public int getHoodType() {
        return hoodType;
    }

    public void setHoodType(int hoodType) {
        this.hoodType = hoodType;
    }

    public int getNoOfWheels() {
        return noOfWheels;
    }

    public void setNoOfWheels(int noOfWheels) {
        this.noOfWheels = noOfWheels;
    }

    @Override
    public String toString() {
        return super.toString() + "\nCapacity: " + capacity + "\nHoodType: " + hoodType + "\nNo Of Wheels: " + noOfWheels;
    }

}

class Car extends Automobile {
    int noOfDoors, seatingCapacity;

    public Car(int make, int type, int maxSpeed, int price, int mileage, int registrationNumber, int noOfDoors,
               int seatingCapacity) {
        super(make, type, maxSpeed, price, mileage, registrationNumber);
        this.noOfDoors = noOfDoors;
        this.seatingCapacity = seatingCapacity;
    }

    public int getNoOfDoors() {
        return noOfDoors;
    }

    public void setNoOfDoors(int noOfDoors) {
        this.noOfDoors = noOfDoors;
    }

    public int getSeatingCapacity() {
        return seatingCapacity;
    }

    public void setSeatingCapacity(int seatingCapacity) {
        this.seatingCapacity = seatingCapacity;
    }

    @Override
    public String toString() {
        return super.toString() + "\nNo Of Doors: " + noOfDoors + "\nSeating Capacity: " + seatingCapacity;
    }

}

class Main_Q14 {
    public static void main(String arg[]) {
        Truck t = new Truck(1, 2, 100, 1000000, 40, 13096, 100, 2, 16);
        System.out.print("\nTruck details : " + t);

        Car c = new Car(2, 3, 120, 500000, 50, 168937, 4, 4);
        System.out.print("\n\nCar details : " + c);
    }
}