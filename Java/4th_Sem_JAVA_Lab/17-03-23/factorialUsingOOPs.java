class factorialCalc {
    int n = 5, fact = 1;
    void calculate() {
        n = 5;
        for (int i = 1; i <= n; i++) {
            fact *= i;
        }
    }
    void display() {
        System.out.println("Factorial of " + n + " is " + fact);
    }
}

class factorialUsingOOPs {
    public static void main(String[] args) {
        factorialCalc f = new factorialCalc();
        f.calculate();
        f.display();
    }
}
