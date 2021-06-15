/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
25) Write a Java program using threading technology and print the thread index and location
where the element has been found.
*/

class ThreadedSearch {

    static int index, key;
    static int arr[];

    ThreadedSearch(int arr[]) {
        ThreadedSearch.arr = arr;
        index = -1;
        if (arr.length % 10 != 0)
            throw new IllegalArgumentException("Chap");

    }

    public int bSearch(int key) throws InterruptedException {
        ThreadedSearch.key = key;
        SearchThread stAr[] = new SearchThread[arr.length / 10];
        for (int i = 0; i < arr.length / 10; i++) {
            stAr[i] = new SearchThread(i * 10, (i + 1) * 10 - 1);
            stAr[i].start();
        }
        for (int i = 0; i < arr.length / 10; i++) {
            stAr[i].join();
        }
        return index;
    }

    static class SearchThread extends Thread {

        int lo;
        int hi;

        SearchThread(int lo, int hi) {
            this.hi = hi;
            this.lo = lo;
        }

        @Override
        public void run() {
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (arr[mid] == key) {
                    index = mid;
                    break;
                } else if (arr[mid] < key)
                    lo = mid + 1;
                else
                    hi = mid - 1;
            }
        }
    }

}

class Main_Q25 {
    public static void main(String[] args) {
        int arr[] = new int[20];

        for (int i = 0; i < 20; i++) {
            arr[i] = i + 1;
        }

        ThreadedSearch obj = new ThreadedSearch(arr);

        try {
            System.out.println(obj.bSearch(13));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}