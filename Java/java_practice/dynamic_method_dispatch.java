// Dynamic Method Dispatch

class A {
    void callme () {
        System.out.println("Inside A's callme method");
    }
}

class B extends A {
    // override callme()
    void callme () {
        System.out.println("Inside B's callme method");
    }
}

class C extends A {
    // override callme()
    void callme () {
        System.out.println("Inside C's callme method");
    }
}

class dynamic_method_dispatch {
    public static void main(String[] args) {
        A a = new A();
        B b = new B();
        C c = new C();

        A r; // obtain a reference of type A

        r = a; // r refers to an A object
        r.callme();

        r = b; // r refers to a B object
        r.callme();

        r = c; // r refers to a C object
        r.callme();
    }
}

// here the upcasting is done implicitly by the compiler, so there is no need to explicitly upcast the object reference
// For explicit upcasting, the following code can be used:
// r = (A) a; // r refers to an A object
// r = (A) b; // r refers to a B object
// r = (A) c; // r refers to a C object
// When the explicit is needed?
// When the reference is passed to a method that expects a superclass reference as one of its parameters.
// When a method overrides one of the superclass methods, an overridden version of the method is called through the superclass reference.
// When a class wants to hide the superclass version of the method.
// When a class needs to have a specific implementation of a method, even if a superclass version of the method exists.
// When a subclass needs to add new methods, instance variables, or class variables.
// When the superclass is declared abstract, and thus cannot be instantiated, but the subclass can be instantiated.