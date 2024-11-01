public class A {

    private int num;

    public void initNum(String[] args) {
        if (args.length < 1) {
            System.err.println("Error: Provide an integer argument.");
            System.exit(1);
        }
        num = Integer.parseInt(args[0]);
    }

    public void checkPrime() {
        if (num <= 1) {
            System.out.println(num + " is not prime.");
            return;
        }
        for (int i = 2; i * i <= num; i++) { 
            if (num % i == 0) {
                System.out.println(num + " is not prime.");
                return;
            }
        }
        System.out.println(num + " is prime.");
    }

    public static void main(String[] args) {
        A obj = new A();
        obj.initNum(args);
        obj.checkPrime();
    }
}