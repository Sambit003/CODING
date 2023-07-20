class fibonacciSeries {
    public static void main(String[] args){
        int n = 10, a = 0, b = 1, c;
        System.out.print("Fibonacci Series: " + a + " " + b + " ");
        for (int i = 2; i < n; i++){
            c = a + b;
            System.out.print(c + " ");
            a = b;
            b = c;
        }
    }    
}
