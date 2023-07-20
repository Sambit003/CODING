// Program to demonstrate synchronization in Java

class Counter {
    private int count = 0;

    public synchronized void increment() {
        count++;
    }

    public synchronized int getCount() {
        return count;
    }
}

class Thread1 extends Thread {
    private Counter counter;

    public Thread1(Counter counter) {
        this.counter = counter;
    }

    public void run() {
        for (int i = 0; i < 1000; i++) {
            counter.increment();
        }
    }
}

class Thread2 extends Thread {
    private Counter counter;

    public Thread2(Counter counter) {
        this.counter = counter;
    }

    public void run() {
        for (int i = 0; i < 1000; i++) {
            counter.increment();
        }
    }
}

public class SynchronizationDemo {
    public static void main(String[] args) {
        Counter counter = new Counter();
        Thread1 thread1 = new Thread1(counter);
        Thread2 thread2 = new Thread2(counter);
        thread1.start();
        thread2.start();
        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println(counter.getCount()); // Should print 2000
    }
}
