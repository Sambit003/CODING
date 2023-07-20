// Program to demonstrate multitasking using ExecutorService
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MultitaskingDemo {

    public static void main(String[] args) {
        // Create an executor service with 2 threads
        ExecutorService executorService = Executors.newFixedThreadPool(2);

        // Create two tasks
        Runnable task1 = () -> {
            System.out.println("Task 1 started");
            for (int i = 0; i < 10; i++) {
                System.out.println("Task 1: " + i);
            }
            System.out.println("Task 1 finished");
        };

        Runnable task2 = () -> {
            System.out.println("Task 2 started");
            for (int i = 0; i < 10; i++) {
                System.out.println("Task 2: " + i);
            }
            System.out.println("Task 2 finished");
        };

        // Submit the tasks to the executor service
        executorService.submit(task1);
        executorService.submit(task2);

        // Shutdown the executor service
        executorService.shutdown();
    }
}
