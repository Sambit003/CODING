// 1. Calculate area of a rectangle and a circle using the abstract class.

import java.util.Scanner;

abstract class Shape {
    abstract void area();
}
// The above abstract class is about to be extended by classes Rectangle and Circle, having their own implementations
// of the method area(). The method area() is abstract in the superclass Shape. So, the subclasses Rectangle and Circle
// must override the method area(). Constructors can be defined in an abstract class. But, an abstract class cannot be
// instantiated. So, the constructors are called by the subclasses using the super() keyword. It is not necessary to
// override the constructor of the superclass in the subclasses. If the constructor of the superclass is not overridden
// in the subclass, the compiler will call the constructor of the superclass by default. And it's not also necessary to
// have constructor in the abstract superclass.

class Rectangle extends Shape {
    int length, breadth;

    Rectangle(int l, int b) {
        length = l;
        breadth = b;
    }

    void area() {
        System.out.println("Area of Rectangle: " + (length * breadth));
    }
}
// The above class extends the abstract class Shape and overrides the method area().

class Circle extends Shape {
    int radius;

    Circle(int r) {
        radius = r;
    }

    void area() {
        System.out.println("Area of Circle: " + (3.14 * radius * radius));
    }
}
// The above class extends the abstract class Shape and overrides the method area().

public class areaCalcUsingAbstract {
    public static void main (String args[]) {
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter length and breadth of rectangle: ");
            int l = sc.nextInt();
            int b = sc.nextInt();
            Rectangle r = new Rectangle(l, b);
            r.area();

            System.out.print("Enter radius of circle: ");
            int r1 = sc.nextInt();
            Circle c = new Circle(r1);
            c.area();
        }
        catch (Exception e) {
            System.out.println("Error: " + e);
        }
        finally {
            System.out.println("Program completed!");
        }
    }
}