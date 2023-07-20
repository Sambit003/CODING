/*
 * Create a 1st sem grade card, with 5 theory paper numbers.
 * NSS marks will be added by extending the super class ‘FirstSemGrade’. 
 * Now HoD will select CR by considering all these marks. 
 * Display all the marks including NSS by using the method overriding concept. 
 */

import java.util.Scanner;

class FirstSemGrade {
    double hsmc, basicEE, chemistry, maths, basicCS;

    FirstSemGrade (double h, double bEE, double c, double m, double bCS) {
        hsmc = h;
        basicEE = bEE;
        chemistry = c;
        maths = m;
        basicCS = bCS;
    }

    void display() {
        System.out.println("HSMC: " + hsmc);
        System.out.println("Basic EE: " + basicEE);
        System.out.println("Chemistry: " + chemistry);
        System.out.println("Maths: " + maths);
        System.out.println("Basic CS: " + basicCS);
    }
}

class NSS extends FirstSemGrade {
    double nss;

    NSS (double h, double bEE, double c, double m, double bCS, double n) {
        super(h, bEE, c, m, bCS);
        nss = n;
    }

    void display() {
        System.out.println("HSMC: " + hsmc);
        System.out.println("Basic EE: " + basicEE);
        System.out.println("Chemistry: " + chemistry);
        System.out.println("Maths: " + maths);
        System.out.println("Basic CS: " + basicCS);
        System.out.println("NSS: " + nss);
    }
}

class GradeCard {
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter the marks of HSMC, Basic EE, Chemistry, Maths and Basic CS: ");
            double h = sc.nextDouble();
            double bEE = sc.nextDouble();
            double c = sc.nextDouble();
            double m = sc.nextDouble();
            double bCS = sc.nextDouble();
            System.out.print("Enter the NSS marks: ");
            double n = sc.nextDouble();

            NSS nss = new NSS(h, bEE, c, m, bCS, n);
            nss.display();
        }
        catch(Exception e) {
            System.out.println("Keyboard error " + e);
        }
    }
}