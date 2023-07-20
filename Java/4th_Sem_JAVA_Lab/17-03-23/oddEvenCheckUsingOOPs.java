class oddEven {
    int num = 0;
    void check() {
        if (num == 0) {
            System.out.println("Not even or odd");
        } else if (num % 2 == 0) {
            System.out.println("Even");
        } else {
            System.out.println("Odd");
        }
    }
}

class oddEvenCheckUsingOOPs {
    public static void main(String[] args) {
        oddEven o = new oddEven();
        o.check();
    }
}
