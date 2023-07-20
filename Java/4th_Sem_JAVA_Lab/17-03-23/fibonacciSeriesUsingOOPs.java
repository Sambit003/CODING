class fibonacci {
    int n = 10;
    void printSeries() {
        int a = 0, b = 1, c;
        System.out.print(a + " " + b + " ");
        for (int i = 2; i < n; i++){
            c = a + b;
            System.out.print(c + " ");
            a = b;
            b = c;
        }
    }
}
public class fibonacciSeriesUsingOOPs {
    public static void main(String[] args) {
        fibonacci f = new fibonacci();
        f.printSeries();
    }
}
