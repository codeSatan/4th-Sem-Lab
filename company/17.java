/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
17) Imagine a toll booth and a bridge. Cars passing by the booth are expected to pay an amount
of Rs. 50/- as toll tax. Mostly they do but sometimes a car goes by without paying. The toll booth
keeps track of the number of the cars that have passed without paying, total number of cars
passed by, and the total amount of money collected. Execute this with a class called “Tollbooth”
and print out the result as follows:
The total number of cars passed by without paying.
Total number of cars passed by.
Total cash collected.
*/

class Tollbooth {

    private static final int TOLL_TAX = 50;
    private int tollUnpaidCount;
    private int tollPaidCount;
    private int totalCars;

    public void addTollPaid() {
        tollPaidCount++;
        totalCars++;
    }

    public void addTollUnpaid() {
        tollUnpaidCount++;
        totalCars++;
    }

    public int getTollUnpaidCount() {
        return tollUnpaidCount;
    }

    public int getTollPaidCount() {
        return tollPaidCount;
    }

    public int getTotalCars() {
        return totalCars;
    }

    public int totalCashCollected() {
        return tollPaidCount * TOLL_TAX;
    }
}

class Main_Q17 {
    public static void main(String[] args) {
        Tollbooth tollbooth = new Tollbooth();
        for (int i = 0; i < 1000; i++) {
            if (Math.random() < 0.1)
                tollbooth.addTollUnpaid();
            else
                tollbooth.addTollPaid();
        }
        System.out.println("TollBooth Details: ");
        System.out.println("Total Cars: " + tollbooth.getTotalCars());
        System.out.println("Cars that paid: " + tollbooth.getTollPaidCount());
        System.out.println("Cars that didn't pay: " + tollbooth.getTollUnpaidCount());
        System.out.println("Total cash collected: " + tollbooth.totalCashCollected());
    }
}