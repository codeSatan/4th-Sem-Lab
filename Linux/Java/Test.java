public class Test {
    int a,b;
    Test(){
        a = 10;
        b = 20;  //calls the constructor bitch
        System.out.println("Within def const");
    }

    void get(){
        display(this);;
    }

    void display(Test obj){
        System.out.println("a = "+a+"b = "+b);
    }
    public static void main(String[] args) {
        Test ob = new Test();
        ob.get();
    }
    
}
