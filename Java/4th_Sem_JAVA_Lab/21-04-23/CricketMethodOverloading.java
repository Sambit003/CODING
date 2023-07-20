/*
 * Create a class cricket under which, the method play will be overloaded 5 times 
 * (two methods will have return type), to display various information of an 
 * Indian cricketer. 
 */

class Cricket {
    void play(String name, int age) {
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
    }

    void play(String team) {
        System.out.println("Team: " + team);
    }

    void play(int runs, int wickets) {
        System.out.println("Runs: " + runs);
        System.out.println("Wickets: " + wickets);
    }
    
    int play(int totalmatches) {
        return totalmatches;
    }

    double play (double batAvg, double bowlAvg) {
        return (batAvg + bowlAvg) / 2;
    }
}

class CricketMethodOverloading {
    public static void main (String[] args) {
        Cricket c = new Cricket();
        c.play("Virat Kohli", 32);
        c.play("India");
        c.play(12000, 4);
        System.out.println("Total matches played: " + c.play(250));
        System.out.println("Average: " + c.play(59.5, 45.2));
    }
}


