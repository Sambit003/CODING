/*
 * A couple has decided to divide 40% of their amount to their two sons and
 * rest of the amount to their two daughters equally.
 * Print the name and amount received by each of the four children through main method.
*/

import java.util.Scanner;

class Couple{
    float amount = 100000;
    
    float divideToSons(){
        return (amount * 0.4f);
    }

    float divideToDaughters(){
        return (amount * 0.6f);
    }

}

class Son extends Couple{
    String name;
    Son(String n){
        name = n;
    }
    float receivedBySon(){
        return (divideToSons() / 2);
    }

    String getName(){
        return name;
    }
}

class Daughter extends Couple{
    String name;
    Daughter(String n){
        name = n;
    }
    float receivedByDaughter(){
        return (divideToDaughters() / 2);
    }

    String getName(){
        return name;
    }
}

public class CoupleSonDaughterProperty {
    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)) {
            System.out.println("Enter the name of the first son: ");
            String n1 = sc.next();
            System.out.println("Enter the name of the second son: ");
            String n2 = sc.next();
            System.out.println("Enter the name of the first daughter: ");
            String n3 = sc.next();
            System.out.println("Enter the name of the second daughter: ");
            String n4 = sc.next();
            Son s1 = new Son(n1);
            Son s2 = new Son(n2);
            Daughter d1 = new Daughter(n3);
            Daughter d2 = new Daughter(n4);
            System.out.println("The amount received by " + s1.getName() + " is " + s1.receivedBySon());
            System.out.println("The amount received by " + s2.getName() + " is " + s2.receivedBySon());
            System.out.println("The amount received by " + d1.getName() + " is " + d1.receivedByDaughter());
            System.out.println("The amount received by " + d2.getName() + " is " + d2.receivedByDaughter());
        }
        catch (Exception e) {
            System.out.println("Keyboard error " + e);
        }
    }
}