/*
 * NAME: Suman Mondal
 * Roll No: 001911001014
 * Information Technology 2nd Semester
*/
 /*
 * 4) Implement a class for stack of integers using an array. Please note that
 * the operations defined for a stack data structure are as follows: “push”,
 * “pop”, “print”. There should be a constructor to create an array of integers;
 * the size of the array is provided by the user. Write a main() function to (i)
 * create a stack to hold maximum of 30 integers; (ii) push the numbers 10, 20,
 * 30, 15, 9 to the stack; (iii) print the stack; (iii) pop thrice and (iv)
 * print the stack again.
 */

class Stack {
    private int arr[];
    private int size, top;

    public Stack(int size) {
        this.size = size;
        arr = new int[size];
        top = -1;
    }

    void push(int x) {
        if (top == size - 1)
            System.out.println("Stack overflow");
        else
            arr[++top] = x;
    }

    int pop() {
        if (top == -1) {
            System.out.println("Stack underflow");
            return -9999;
        }
        return arr[top--];
    }

    void print() {
        System.out.println("Contents of stack");
        for (int i = top; i >= 0; i--)
            System.out.println(arr[i] + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        Stack st = new Stack(30);
        st.push(10);
        st.push(20);
        st.push(30);
        st.push(40);
        st.push(50);
        st.print();
        int pp = st.pop();
        pp = st.pop();
        pp = st.pop();
        st.print();
    }
}
