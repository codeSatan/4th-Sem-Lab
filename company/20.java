/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
20) Create two threads and call them EvenThread and OddThread. EvenThread will print number
as 2 4 6 8 10... and OddThread will print number as 1 3 5…. Now synchronize these two thread
to get the output as 1 2 3 4 5 6 7 8.
*/

class OddEvenThreadSync {

    static int number = 1;
    static final int LIMIT = 10;

    private void printOddNos() {
        /* to print odd numbers */
        synchronized (this) {
            while (number < LIMIT) {
                while ((number & 1) == 1) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                System.out.println(number);
                number++;
                // Notify to second thread
                notify();
            }
        }
    }

    private void printEvenNos() {
        /* to print even numbers */
        synchronized (this) {
            while (number < LIMIT) {
                while ((number & 1) == 0) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                System.out.println(number);
                number++;
                // Notify to 2nd thread
                notify();
            }
        }
    }

    public static void main(String[] args) {

        OddEvenThreadSync obj = new OddEvenThreadSync();

        Thread odd = new Thread(new Runnable() {
            public void run() {
                obj.printOddNos();
                try {
                    Thread.sleep(1000);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            };
        });

        Thread even = new Thread(new Runnable() {
            public void run() {
                obj.printEvenNos();
                try {
                    Thread.sleep(1000);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            };
        });

        odd.start();
        even.start();
    }
}