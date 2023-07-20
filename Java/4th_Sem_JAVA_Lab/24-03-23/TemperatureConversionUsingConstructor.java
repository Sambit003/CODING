import java.util.Scanner;

class TemperatureConversion{
    double celsius, fahrenheit;
    TemperatureConversion(double c){
        celsius = c;
    }
    void convert(){
        fahrenheit = (celsius * 9 / 5) + 32;
    }
    void display(){
        System.out.println("Fahrenheit = " + fahrenheit);
    }
}

class TemperatureConversionUsingConstructor{
    public static void main(String args[]){
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter Celsius: ");
            double c = sc.nextDouble();
            TemperatureConversion temp = new TemperatureConversion(c);
            temp.convert();
            temp.display();
        }
    }
}