
class Box{
    int length, width, height;

    Box(int a, int b, int c){
        length = a;
        width = b;
        height = c;
    }

    Box(int a, int b){
        length = a+b;
        width = a-b; 
        height = a*b;
    }

    Box(int a){
        length = 2*a;
        width = a;
        height = 3*a;
    }

    Box(){
        length = width = height = 5;

    }

    int volume(){return (length*width*height);}

    public static void main(String[] args) {

        Box b1 = new Box(5,6,7);
        Box b2 = new Box(5,3);
        Box b3 = new Box(5);
        Box b4 = new Box();
        System.out.println("Box1 volume"+ b1.volume());
        System.out.println("Box2 volume"+ b2.volume());
        System.out.println("Box3 volume"+ b3.volume());
        System.out.println("Box4 volume"+ b4.volume());


        
    }
    
}
