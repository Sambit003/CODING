import java.util.Scanner;

class FactorialOfANumber{
    int num;
    FactorialOfANumber(int n){
        num = n;
    }
    void calculate(){
        int fact = 1;
        for (int i = 1; i <= num; i++){
            fact *= i;
        }
        System.out.print("Factorial of " + num + " is " + fact);
    }
}

class FactorialOfANumberUsingConstructor{
    public static void main(String args[]){
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter a number: ");
            int n = sc.nextInt();
            FactorialOfANumber fact = new FactorialOfANumber(n);
            fact.calculate();
        } 
    }
}