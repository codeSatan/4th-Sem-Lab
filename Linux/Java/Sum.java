public class Sum {
    int sum (int x, int y){
        return (x+y);
    }

    int sum(int x, int y, int z){
        return (x+y+z);
    }

    double sum(double x, double y){
        return x+y;
    }

    double sum (double x, double y, double z){
        return x+y+z;
    }

    double sum (int x, double y){
        return x+y;
    }
    public static void main(String[] args) {
        Sum s = new Sum();
        System.out.println(s.sum(1, 2));
        System.out.println(s.sum(1, 2, 3));
        System.out.println(s.sum(1.5, 2.5));
        System.out.println(s.sum(1.5, 2));
        System.out.println(s.sum(1f, 2.5));
    }
}
