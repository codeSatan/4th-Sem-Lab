/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
23) Consider the series 1+2+3+…+100. This can be considered as
(1+3+5+…+99)+(2+4+6+…+100). Create two threads to compute two series in parallel (do not
use simplified equation). Finally print the final sum.
*/

class OddEvenSumParallel {

    static int number = 1;
    static final int LIMIT = 100;

    static int sum = 0;

    private void sumOddNos() {
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
                sum += number;
                number++;
                // Notify to second thread
                notify();
            }
        }
    }

    private void sumEvenNos() {
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
                sum += number;
                number++;
                // Notify to 2nd thread
                notify();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {

        OddEvenSumParallel obj = new OddEvenSumParallel();

        Thread odd = new Thread(new Runnable() {
            public void run() {
                obj.sumOddNos();
            };
        });

        Thread even = new Thread(new Runnable() {
            public void run() {
                obj.sumEvenNos();
            };
        });

        odd.start();
        even.start();

        odd.join();
        even.join();

        System.out.println("Total sum = " + sum);
    }
}