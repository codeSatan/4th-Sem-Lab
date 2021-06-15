/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
21) Consider the following series
x = 1+1/1! +1/2! + 1/3! + ………1/10!
Create two threads t1 & t2. t1 will generate the denominators and t2 will form the term and add
them up. Finally print the result.
*/

class SeriesSum {

    static int LIMIT;
    double[] arr = new double[LIMIT + 1];
    int flag = 0;

    static double factorial(int n) {
        return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
    }

    private void calTerm() {
        synchronized (this) {
            while (flag <= LIMIT) {
                arr[flag] = ((double) 1 / factorial(flag));
                System.out.println("Term number " + (flag + 1) + " is " + 1 + "/" + flag + "!");
                flag += 1;

                notify();
            }
        }
    }

    private void calSum() {
        double sumFinal = 0.0;
        synchronized (this) {
            flag = 0;
            while (flag <= LIMIT) {
                sumFinal = sumFinal + arr[flag];
                flag += 1;
                notify();
            }

            System.out.println("Final Sum = " + sumFinal);
        }
    }

    public static void main(String[] args) {

        LIMIT = 10;
        SeriesSum obj = new SeriesSum();

        Thread term = new Thread(new Runnable() {
            public void run() {
                obj.calTerm();
            }
        });
        Thread sum = new Thread(new Runnable() {
            public void run() {
                obj.calSum();
            }
        });

        term.start();
        sum.start();
    }
}