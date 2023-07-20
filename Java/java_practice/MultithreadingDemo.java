// Program to demonstrate multithreading in Java

public class MultithreadingDemo {
    public static void main(String[] args) {
        // Create two threads
        Thread thread1 = new Thread(new Runnable() {
            @Override
            public void run() {
                // Do something in thread 1
                for (int i = 0; i < 10; i++) {
                    System.out.println("Thread 1 is running: " + i);
                    try {
                        Thread.sleep(2000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        Thread thread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                // Do something in thread 2
                for (int i = 0; i < 10; i++) {
                    System.out.println("Thread 2 is running: " + i);
                    try {
                        Thread.sleep(2000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        // Start the two threads
        thread1.start();
        thread2.start();

        // Stop the threads after 5 seconds
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        thread1.interrupt();
        thread2.interrupt();
    }
}