import java.util.Scanner;

class VolumeOfBox{
    double length, breadth, height;
    VolumeOfBox(double l, double b, double h){
        length = l;
        breadth = b;
        height = h;
    }
    void calculate(){
        double volume = length * breadth * height;
        System.out.println("Volume of Box = " + volume);
    }
}

class VolumeOfBoxUsingConstructor{
    public static void main(String args[]){
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter Length, Breadth and Height: ");
            double l = sc.nextDouble();
            double b = sc.nextDouble();
            double h = sc.nextDouble();
            VolumeOfBox volume = new VolumeOfBox(l, b, h);
            volume.calculate();
        }
    }
}