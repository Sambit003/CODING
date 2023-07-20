import java.util.Scanner;

class FibonacciSeries{
    int term;
    FibonacciSeries(int t){
        term = t;
    }
    void print(){
        int a = 0, b = 1, c;
        System.out.print("Fibonacci Series: " + a + " " + b + " ");
        for (int i = 2; i < term; i++){
            c = a + b;
            System.out.print(c + " ");
            a = b;
            b = c;
        }
    }
}

class FibonacciSeriesPrintUsingConstructor{
    public static void main(String args[]){
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter number of terms: ");
            int t = sc.nextInt();
            FibonacciSeries fibo = new FibonacciSeries(t);
            fibo.print();
        }
    }
}