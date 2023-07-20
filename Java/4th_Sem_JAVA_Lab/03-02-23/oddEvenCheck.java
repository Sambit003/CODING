class oddEvenCheck {
    public static void main(String args[]) {
        int num = 5;
        if(num == 0)    
            System.out.print("Zero, Neither Even nor Odd");
        else if (num % 2 == 0)
            System.out.print("The number " +num+ " is Even");
        else 
            System.out.print("The number " +num+ " is Odd");
    }
}
