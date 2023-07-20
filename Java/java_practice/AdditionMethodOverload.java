class Addition {
    int add (int a, int b) {
        return a + b;
    }

    float add (float a, float b) {
        return a + b;
    }
}

class AdditionMethodOverload {
    public static void main(String[] args) {
        Addition a = new Addition();
        System.out.println(a.add(1, 2));
        System.out.println(a.add(1.0f, 2.0f));

        // You can customize the driver code to take input from the user and call the appropriate method.
    }
}