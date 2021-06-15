/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
 */

/*
24) Consider the following parallel binary search algorithm for series a1, a2…an sorted in
increasing order such that n mod 10 = 0. Element to be searched is e.
a) Create n/10 threads t1, t2,..,tn/10.
b) Distribute the numbers among threads such that ti will have numbers ai, ai+1, ….a2i-1.
c) Distribute the element e to all threads.
d) Each thread searches the element e in its sub-array using binary search algorithm.
*/

class MTBinSearch {

    static int index, key;
    static int arr[];

    MTBinSearch(int arr[]) {
        MTBinSearch.arr = arr;
        index = -1;
        if (arr.length % 10 != 0)
            throw new IllegalArgumentException("Illegal Entry");

    }

    public int bSearch(int key) throws InterruptedException {
        MTBinSearch.key = key;
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

class Main_Q24 {
    public static void main(String[] args) {
        int arr[] = new int[20];

        for (int i = 0; i < 20; i++) {
            arr[i] = i + 1;
        }

        MTBinSearch obj = new MTBinSearch(arr);

        try {
            System.out.println(obj.bSearch(7));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}