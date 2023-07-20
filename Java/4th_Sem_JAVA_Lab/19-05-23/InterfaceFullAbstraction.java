// 2. WAP to prove that interface supports full abstraction in java.

import java.util.Scanner;

interface Car {
    void start();
    void stop();
}
// The above interface is equivalent to:
// abstract class Car {
//     abstract void start();
//     abstract void stop();
// }

class Maruti implements Car {
    public void start() {
        System.out.println("Maruti started!");
    }

    public void stop() {
        System.out.println("Maruti stopped!");
    }
}
// The above class supports full abstraction because it implements all the methods of the interface.
// If we remove any of the methods, the class will become abstract and we will have to declare it as abstract.
// If we remove the keyword 'public' from the methods, the compiler will throw an error because the methods
// are public by default in an interface.

class Audi implements Car {
    public void start() {
        System.out.println("Audi started!");
    }

    public void stop() {
        System.out.println("Audi stopped!");
    }
}
// Same as above. This class also supports full abstraction.

public class InterfaceFullAbstraction {
    public static void main (String args[]) {
        try (Scanner sc = new Scanner(System.in)) {
            System.out.println("1. Maruti \n2. Audi");
            System.out.print("Enter your choice: ");
            int choice = sc.nextInt();
            Car c;
            switch (choice) {
                case 1:
                    c = new Maruti();
                    break;
                case 2:
                    c = new Audi();
                    break;
                default:
                    System.out.println("Invalid choice!");
                    return;
            }
            c.start();
            c.stop();
        }
        catch (Exception e) {
            System.out.println("Error: " + e);
        }
        finally {
            System.out.println("Program completed!");
        }
    }
}

// The above program can also be written using an abstract class instead of an interface.
// The abstract class will have abstract methods start() and stop() and the Maruti and Audi classes
// will extend the abstract class and implement the methods.
// The abstract class will be equivalent to the interface in this case.
// The only difference is that a class can extend only one abstract class but can implement multiple interfaces.
// Also, the methods in an interface are public by default but in an abstract class, they are not.
// The methods in an interface are abstract by default but in an abstract class, they are not.
// The methods in an interface cannot have a body but in an abstract class, they can.
// The variables in an interface are public, static and final by default but in an abstract class, they are not.
// The variables in an interface cannot be initialized but in an abstract class, they can.
// The interface cannot have a constructor but the abstract class can.
// The interface cannot have a static method but the abstract class can.
// The interface cannot have a main method but the abstract class can.
// The interface cannot have a static block but the abstract class can.
// The interface cannot have a non-static block but the abstract class can.
// The interface cannot have a static variable but the abstract class can.