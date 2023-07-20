public class WrapperClass {
    public static void main (String args[]) {
        byte b = 10;
        short s = 20;
        int i = 30;
        long l = 40;
        float f = 50.0f;
        double d = 60.0d;
        char c = 'a';
        boolean bool = true;

        // Autoboxing: Converting primitives into objects
        Byte byteobj = b;
        Short shortobj = s;
        Integer intobj = i;
        Long longobj = l;
        Float floatobj = f;
        Double doubleobj = d;
        Character charobj = c;
        Boolean boolobj = bool;

        // Printing objects
        System.out.println("---Printing object values---");
        System.out.println("Byte object: " + byteobj);
        System.out.println("Short object: " + shortobj);
        System.out.println("Long object: " + longobj);
        System.out.println("Float object: " + floatobj);
        System.out.println("Double object: " + doubleobj);
        System.out.println("Character object: " + charobj);
        System.out.println("Boolean object: " + boolobj);

        // Unboxing: Converting Objects to Primitives
        byte bytevalue = byteobj;
        short shortvalue = shortobj;
        int intvalue = intobj;
        long longvalue = longobj;
        float floatvalue = floatobj;
        double doublevalue = doubleobj;
        char charvalue = charobj;
        boolean boolvalue = boolobj;

        //Printing primitives
        System.out.println("---Printing primitive values---");
        System.out.println("byte value: " + bytevalue);
        System.out.println("short value: " + shortvalue);
        System.out.println("int value: " + intvalue);
        System.out.println("long value: " + longvalue);
        System.out.println("float value: " + floatvalue);
        System.out.println("double value: " + doublevalue);
        System.out.println("char value: " + charvalue);
        System.out.println("boolean value: " + boolvalue);
    }
}

/* public class WrapperClass {

    public static void main(String[] args) {

        int num = 10;

        // Create a new Integer object from the primitive value num
        Integer obj1 = Integer.valueOf(num);

        // Simply assign the primitive value num to the Integer variable obj2
        Integer obj2 = num;

        // Compare the performance of the two statements
        long start = System.nanoTime();
        for (int i = 0; i < 10000000; i++) {
            Integer.valueOf(num);
        }
        long end = System.nanoTime();
        System.out.println("Time taken to create a new Integer object: " + (end - start));

        start = System.nanoTime();
        for (int i = 0; i < 10000000; i++) {
            obj2 = num;
        }
        end = System.nanoTime();
        System.out.println("Time taken to simply assign a primitive value to an Integer variable: " + (end - start));
    }
} */
