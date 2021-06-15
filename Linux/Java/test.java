//Overloading main:

public class test {
	
    public static void main(String args[])
    {
        System.out.println("Hello");
        test.main("Hi");
        
    }
    public static void main(String args1)
    {
        System.out.println("One arg"+args1);
        test.main("Hello","World");
    }
    public static void main(String args1, String args2)
    {
        System.out.println("Two arg"+args1+args2);
        
        
    }
}
