class primeNumCheck {
    public static void main(String args[]) {
        int n = 7;
        boolean isPrime = true;
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            System.out.print("The number " + n + " is Prime");
        else
            System.out.print("The number " + n + " is not Prime");
    } 
}
