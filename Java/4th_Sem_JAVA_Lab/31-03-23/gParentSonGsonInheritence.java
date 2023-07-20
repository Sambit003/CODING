/*
 * A grand parent wants to divide 40% of his amount to his son and
 * son whas decided to distribute 40% of his amount to grandson.
 * Display name, location, amount received by each person through main method only.
 */

import java.util.Scanner;

class GrandParent {
    float amount = 100000;
    
    float divideToSon(){
        return (amount * 0.4f);
    }
}

class Son extends GrandParent {
    String name, location;

    Son(String n, String l){
        name = n;
        location = l;
    }

    float receivedBySon(){
        return (divideToSon());
    }

    String getNameOfSon(){
        return name;
    }

    String getLocationOfSon(){
        return location;
    }

    float divideToGrandSon(){
        return (divideToSon() * 0.4f);
    }
}

class GrandSon extends Son {
    String name, location;

    GrandSon(String n, String l, String n1, String l1){
        super(n, l);
        name = n1;
        location = l1;
    }

    float receivedByGrandSon(){
        return (divideToGrandSon());
    }

    String getNameOfGSon(){
        return name;
    }

    String getLocationOfGSon(){
        return location;
    }
}

public class gParentSonGsonInheritence {
    public static void main (String args[]) {
        try(Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter name of Son: ");
            String Sname = sc.nextLine();
            System.out.print("Enter location of Son: ");
            String Slocation = sc.nextLine();
            System.out.print("Enter name of Grand Son: ");
            String GSname = sc.nextLine();
            System.out.print("Enter location of Grand Son: ");
            String GSlocation = sc.nextLine();

            GrandSon gs = new GrandSon(Sname, Slocation, GSname, GSlocation);
            System.out.println("Son: " + gs.getNameOfSon() + " at " + gs.getLocationOfSon() + " received amount " + gs.receivedBySon());
            System.out.println("Grand Son: " + gs.getNameOfGSon() + " at " + gs.getLocationOfGSon() + " received amount " + gs.receivedByGrandSon());
        }
        catch (Exception e) {
            System.out.println("Keyboard error: " + e);
        }
    }
}