/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
19) Write a program to create two threads. Print “In main thread” in main thread and “
In child thread” in child thread.
*/

class ChildThread extends Thread {
    @Override
    public void run() {
        System.out.println("In Child Thread\n");
    }
}

class MainThread extends Thread {
    public static void main(String[] args) {

        // running on main thread
        Thread main_thread = Thread.currentThread();
        System.out.println("Currently on thread: " + main_thread.getName());
        System.out.println("In Main Thread\n");

        // running on child thread
        ChildThread child_thread = new ChildThread();
        System.out.println("Currently on thread: " + child_thread.getName());
        child_thread.start();
    }
}
