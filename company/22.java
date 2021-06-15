/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
22) Consider a file that contains a number of integers. Create two threads. Call them ‘producer’
and ‘consumer’ thread. Producer thread will be reading the integers from the file continuously
while consumer thread will add them up. Use proper synchronization mechanism if needed.
*/

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class FileSum {

    public boolean hasRead;
    public int sum;
    private int lastRead;
    private final File file;

    FileSum(File f) {
        sum = 0;
        hasRead = true;
        this.file = f;
    }

    public synchronized void read() throws FileNotFoundException, InterruptedException {

        Scanner sc;
        sc = new Scanner(file);

        while (sc.hasNextInt()) {
            while (!hasRead) {
                wait();
            }
            lastRead = sc.nextInt();
            System.out.println("Value read: " + lastRead);
            hasRead = false;
            notify();
        }
        sc.close();
    }

    public synchronized void getSum() throws InterruptedException {
        while (true) {
            while (hasRead) {
                wait();
            }
            sum += lastRead;

            hasRead = true;

            System.out.println("Now sum: " + sum);
            notify();
        }

    }

}

class Producer implements Runnable {

    FileSum f;

    Producer(FileSum f) {
        this.f = f;
        Thread t2 = new Thread(this, "Producer");
        t2.start();
    }

    @Override
    public void run() {
        try {
            f.read();
        } catch (FileNotFoundException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Consumer implements Runnable {

    FileSum f;

    Consumer(FileSum f) {
        this.f = f;
        Thread t1 = new Thread(this, "Consumer");
        t1.start();
    }

    @Override
    public void run() {
        try {
            f.getSum();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Main_Q22 {
    public static void main(String[] args) {
        File f = new File("C:\\Users\\monda\\IdeaProjects\\OOSLab_RB(Java)\\src\\com\\company\\myNumberFile.txt");
        FileSum fs = new FileSum(f);
        new Producer(fs);
        new Consumer(fs);
    }
}
