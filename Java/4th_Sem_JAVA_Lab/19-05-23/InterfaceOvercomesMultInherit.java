// 3. WAP to prove that interface overcomes the problem of multiple inheritance partially.

import java.util.Scanner;

interface A {
    void display();
}
// The above interface is about to be implemented by class C.

interface B {
    void display1();
}
// The above interface is about to be implemented by class C.

class C implements A, B {
    public void display() {
        System.out.println("Hello!");
    }

    public void display1() {
        System.out.println("Hi!");
    }
}
// The above class implements both the interfaces A and B. It overrides the methods display() and display1().

public class InterfaceOvercomesMultInherit {
    public static void main (String args[]) {
        try (Scanner sc = new Scanner(System.in)) {
            C c = new C();
            c.display();
            c.display1();
        }
        catch (Exception e) {
            System.out.println("Error: " + e);
        }
        finally {
            System.out.println("Program completed!");
        }
    }
}
// The above program compiles and runs successfully. This proves that interface overcomes the problem of multiple
// inheritance partially. Here the method display() is common to both the interfaces A and B. The class C implements
// both the interfaces and overrides the method display(). The method display() is called using the object of class C,
// from the superclass reference variable of type A or B. Why? Because the compiler doesn't know which display()
// method to call. So, it calls the display() method of the superclass reference variable. This is called dynamic
// method dispatch. This is how interface overcomes the problem of multiple inheritance partially.