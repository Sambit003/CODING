class simpleInterest {
    double p = 1000, r = 5, t = 2, si;
    public void calculate() {
        si = (p * r * t) / 100;
    }
    public void display() {
        System.out.println("Simple Interest = " + si);
    }
}

class simpleInterestUsingOOPs {
    public static void main(String[] args) {
        simpleInterest s = new simpleInterest();
        s.calculate();
        s.display();
    }
}