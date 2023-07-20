class area {
    double radius = 7.5, area;
    void calculate() {
        area = 3.141 * radius * radius;
    }
    void display() {
        System.out.println("Area of circle is: " + area);
    }
}

class areaOfACircleUsingOOPs {
    public static void main(String[] args) {
        area a = new area();
        a.calculate();
        a.display();
    }
}