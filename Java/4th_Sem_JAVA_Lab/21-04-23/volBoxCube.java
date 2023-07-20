/*
 * Calculate volume of a rectangular box and a cube using constructor overloading method. 
 */

import java.util.Scanner;

class volume {
    double length, breadth, height;
    volume(double l, double b, double h) {
        length = l;
        breadth = b;
        height = h;
    }
    volume(double side) {
        length = side;
    }

    void rectangularVolumeDisplay() {
        System.out.println("Volume of rectangular box: " + length * breadth * height);
    }

    void cubeVolumeDisplay() {
        System.out.println("Volume of cube: " + length * length * length);
    }
}

class volBoxCube {
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            System.out.println("Enter the length, breadth and height of the rectangular box: ");
            double l = sc.nextDouble();
            double b = sc.nextDouble();
            double h = sc.nextDouble();
            System.out.println("Enter the side of the cube: ");
            double side = sc.nextDouble();

            volume v1 = new volume(l, b, h);
            volume v2 = new volume(side);

            v1.rectangularVolumeDisplay();
            v2.cubeVolumeDisplay();
        }
        catch(Exception e) {
            System.out.println("Keyboard error " + e);
        }
    }
}
