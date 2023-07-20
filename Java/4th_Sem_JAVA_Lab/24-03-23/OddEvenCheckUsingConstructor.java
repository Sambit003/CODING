import java.util.Scanner;

class OddEvenCheck{
    int num;
    OddEvenCheck(int n){
        num = n;
    }
    void check(){
        if (num == 0){
            System.out.println("Neither Even nor Odd");
        }
        else if(num % 2 == 0){
            System.out.println("Even");
        }
        else{
            System.out.println("Odd");
        }
    }
}

class OddEvenCheckUsingConstructor{
    public static void main(String args[]){
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter a number: ");
            int n = sc.nextInt();
            OddEvenCheck oddEven = new OddEvenCheck(n);
            oddEven.check();
        }
    }
}
