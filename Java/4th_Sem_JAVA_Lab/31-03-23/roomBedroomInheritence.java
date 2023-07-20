/*
 * Create a super class Room which will have area as its method, and a subclass Bedroom 
 * which will have volume as its method. Calculate area and volume of bedroom
 */

import java.util.Scanner;

class Room{
    float length, breadth;
    Room (Float l, Float b){
        length = l;
        breadth = b;
    }
    float area(){
        return (length * breadth);
    }
}
class Bedroom extends Room{
    float height;
    Bedroom(float l, float b, float h){
        super(l, b);
        height = h;
    }
    float volume(){
        return (length * breadth * height);
    }
}

public class roomBedroomInheritence {
    public static void main(String[] args) {
       try(Scanner sc = new Scanner(System.in)) {
        System.out.println("Enter the length, breadth and height of the room");
        float l = sc.nextFloat();
        float b = sc.nextFloat();
        float h = sc.nextFloat();
        Bedroom br = new Bedroom(l, b, h);
        System.out.println("Area of the bedroom is " + br.area() + " & volume is " + br.volume());
       }
       catch (Exception e) {
           System.out.println("Keyboard error " + e);
       } 
    }
}