import java.io.*;

class AreaOfACircle{
    double radius, area;
    AreaOfACircle(double r){
        radius = r;
    }
    void calculate(){
        area = 3.141 * radius * radius;
    }
    void display(){
        System.out.println("Area of a circle = " + area);
    }
}

class AreaOfACircleUsingConstructor {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter radius: ");
        double r = Double.parseDouble(br.readLine());
        AreaOfACircle area = new AreaOfACircle(r);
        area.calculate();
        area.display();
    }
}

