import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class PrimeOddThreads {

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        executor.execute(new PrimeThread());
        executor.execute(new OddThread());
        executor.shutdown();
    }

    static class PrimeThread implements Runnable {
        @Override
        public void run() {
            int count = 0;
            int num = 2;
            while (count < 5) {
                if (isPrime(num)) {
                    System.out.println("Prime Number: " + num);
                    count++;
                    try {
                        Thread.sleep(100); 
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
                num++;
            }
        }

        private boolean isPrime(int num) {
            if (num <= 1) return false;
            for (int i = 2; i <= Math.sqrt(num); i++) {
                if (num % i == 0) return false;
            }
            return true;
        }
    }

    static class OddThread implements Runnable {
        @Override
        public void run() {
            int count = 0;
            int num = 1;
            while (count < 5) {
                System.out.println("Odd number: " + num);
                count++;
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
                num += 2;
            }
        }
    }
}