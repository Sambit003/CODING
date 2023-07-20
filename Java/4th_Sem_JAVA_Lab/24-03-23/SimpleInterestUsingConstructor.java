// Simple interest using constructor
import java.util.Scanner;

class SimpleInterest{
    double principle, rate, time, si;
    SimpleInterest(double p, double r, double t){
        principle = p;
        rate = r;
        time = t;
    }
    void calculate(){
        si = (principle * rate * time) / 100;
    }
    void display(){
        System.out.println("Simple Interest = " + si);
    }
}

class SimpleInterestUsingConstructor{
    public static void main(String args[]){
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter Principal, Rate and Time: ");
            double p = sc.nextDouble();
            double r = sc.nextDouble();
            double t = sc.nextDouble();
            SimpleInterest simpleI = new SimpleInterest(p, r, t);
            simpleI.calculate();
            simpleI.display();
        }
    }
}
