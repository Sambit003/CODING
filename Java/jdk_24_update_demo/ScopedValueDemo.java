/**
 * ScopedValueDemo.java
 *
 * This demo showcases the Scoped Values feature introduced in JDK 20 and refined in subsequent releases,
 * currently in its fourth preview in JDK 24 (JEP 487).
 *
 * Scoped Values in Java:
 * -----------------------
 * Scoped Values provide a mechanism for sharing immutable data within a limited scope,
 * specifically among methods in a call stack within a thread. They offer a safer and more
 * efficient alternative to ThreadLocal variables for many use cases.
 *
 * Key Characteristics:
 * - Immutability: Scoped Values are designed to hold immutable data, ensuring that the
 *   data cannot be modified once bound within a scope.
 * - Bounded Lifetime: The binding of a Scoped Value is limited to the execution of a
 *   specific code block (the scope), ensuring automatic cleanup and preventing memory leaks.
 * - One-Way Data Flow: Data flows in one direction, from the caller to the callees,
 *   simplifying reasoning about data flow and preventing unintended side effects.
 *
 * Benefits over ThreadLocal:
 * - Improved Safety: Immutability and bounded lifetime reduce the risk of data corruption
 *   and memory leaks.
 * - Enhanced Performance: Scoped Values can be more efficient than ThreadLocal variables,
 *   especially in scenarios with a large number of threads.
 * - Seamless Integration with Concurrency: Scoped Values work well with modern concurrency
 *   constructs like virtual threads.
 *
 * Usage:
 * Scoped Values are bound to a specific scope using the ScopedValue.where(...).run(...) or
 * ScopedValue.where(...).call(...) methods.  The value is then accessible within that scope
 * via the ScopedValue.get() method.
 *
 * Rebinding:
 * Scoped Values can be rebound in nested scopes, allowing for context-specific modifications
 * of the shared data without affecting the outer scope.
 *
 * Future Plans and Stabilization:
 * Scoped Values are currently in preview and are subject to change based on community feedback.
 * The goal is to refine and stabilize the API for a future standard release of Java.  The
 * feature has undergone multiple preview rounds (JEP 429, JEP 446, JEP 464, JEP 481, JEP 487)
 * to ensure it meets the needs of the Java ecosystem. The removal of callWhere and runWhere
 * methods in favor of a fluent API using ScopedValue.Carrier.call and ScopedValue.Carrier.run
 * demonstrates the ongoing evolution of the API. The feature is expected to be finalized
 * in a future JDK release, pending further review and feedback.
 */
package jdk_24_update_demo;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.lang.ThreadLocal;
import java.util.NoSuchElementException;

public class ScopedValueDemo {
    // ANSI color codes
    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_RED = "\u001B[31m";
    private static final String ANSI_GREEN = "\u001B[32m";
    private static final String ANSI_YELLOW = "\u001B[33m";
    private static final String ANSI_BLUE = "\u001B[34m";
    private static final String ANSI_PURPLE = "\u001B[35m";
    private static final String ANSI_CYAN = "\u001B[36m";
    private static final String ANSI_BOLD = "\u001B[1m";

    // Helper methods for colored output
    private static String info(String text) {
        return ANSI_BLUE + text + ANSI_RESET;
    }
    
    private static String success(String text) {
        return ANSI_GREEN + text + ANSI_RESET;
    }
    
    private static String error(String text) {
        return ANSI_RED + text + ANSI_RESET;
    }
    
    private static String warning(String text) {
        return ANSI_YELLOW + text + ANSI_RESET;
    }
    
    private static String highlight(String text) {
        return ANSI_PURPLE + text + ANSI_RESET;
    }
    
    private static String transaction(String text) {
        return ANSI_CYAN + text + ANSI_RESET;
    }
    
    private static String header(String text) {
        return ANSI_BOLD + text + ANSI_RESET;
    }

    // Define a ScopedValue for a User ID. It's typically static and final.
    private static final ScopedValue<String> USER_ID = ScopedValue.newInstance();

    // Define a ScopedValue for a Request ID.
    private static final ScopedValue<String> REQUEST_ID = ScopedValue.newInstance();
    
    // Define a ScopedValue for transaction context
    private static final ScopedValue<TransactionContext> TX_CONTEXT = ScopedValue.newInstance();
    
    // ThreadLocal for comparison
    private static final ThreadLocal<String> THREAD_LOCAL_USER_ID = new ThreadLocal<>();

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        // Simulate an initial request with a specific User ID.
        String initialUserId = "user123";
        String initialRequestId = "req001";
        System.out.println(header("Starting request with User ID: ") + highlight(initialUserId) + 
                header(", Request ID: ") + highlight(initialRequestId));

        // Bind the User ID and Request ID to the current scope and execute the processing logic.
        ScopedValue.where(USER_ID, initialUserId)
                .where(REQUEST_ID, initialRequestId)
                .run(() -> {
                    processRequest();
                });

        // After the scope ends, the USER_ID and REQUEST_ID are no longer bound.
        try {
            // Check if bound before getting the value
            if (USER_ID.isBound()) {
                System.out.println(info("USER_ID is bound: ") + highlight(USER_ID.get()));
            } else {
                System.out.println(info("USER_ID is not bound"));
            }
            
            // Or handle the correct exception type
            System.out.println(warning("Attempting to access USER_ID outside the scope: ") + USER_ID.get());
        } catch (NoSuchElementException e) {
            System.out.println(success("Successfully caught NoSuchElementException: ") + error(e.getMessage()));
        }

        System.out.println("\n" + header("Starting another request with a different User ID."));
        String anotherUserId = "admin456";
        String anotherRequestId = "req002";

        // Demonstrate using call() which can return a result.
        String result = ScopedValue.where(USER_ID, anotherUserId)
                .where(REQUEST_ID, anotherRequestId)
                .call(ScopedValueDemo::processTask);
        System.out.println("Task result for User ID " + anotherUserId + ": " + result);

        // Demonstrate rebinding in a nested scope.
        System.out.println("\nDemonstrating rebinding in a nested scope.");
        ScopedValue.where(USER_ID, "user789")
                .where(REQUEST_ID, "req003")
                .run(() -> {
                    System.out.println("Outer scope - User ID: " + USER_ID.get() + ", Request ID: " + REQUEST_ID.get());
                    // Rebind the Request ID in a nested scope.
                    ScopedValue.where(REQUEST_ID, "req004").run(() -> {
                        System.out.println("Inner scope - User ID: " + USER_ID.get() + ", Request ID: " + REQUEST_ID.get());
                        performDataAccess(); // Calls auditLog which will show the inner scope's Request ID
                    });
                    System.out.println("Outer scope after inner scope - User ID: " + USER_ID.get() + ", Request ID: " + REQUEST_ID.get());
                });

        // Demonstrate complex rebinding scenarios
        System.out.println("\n==== DEMONSTRATING COMPLEX REBINDING SCENARIOS ====");
        demoComplexRebinding();
        
        // Demonstrate error handling
        System.out.println("\n==== DEMONSTRATING ERROR HANDLING ====");
        demoErrorHandling();
        
        // Demonstrate comparison with ThreadLocal
        System.out.println("\n==== COMPARING WITH THREADLOCAL ====");
        demoThreadLocalComparison();
    }

    private static void processRequest() {
        System.out.println(info("Processing request..."));
        // Access the User ID and Request ID within the current scope.
        String currentUserId = USER_ID.get();
        String currentRequestId = REQUEST_ID.get();
        System.out.println(info("Current User ID in processRequest: ") + highlight(currentUserId) + 
                info(", Request ID: ") + highlight(currentRequestId));
        performDataAccess();
    }

    private static void performDataAccess() {
        System.out.println(info("Performing data access..."));
        // Access the User ID and Request ID further down the call stack.
        String currentUserId = USER_ID.get();
        String currentRequestId = REQUEST_ID.get();
        System.out.println(info("Current User ID in performDataAccess: ") + highlight(currentUserId) + 
                info(", Request ID: ") + highlight(currentRequestId));
        auditLog();
    }

    private static void auditLog() {
        // Access the User ID and Request ID even deeper in the call stack.
        String currentUserId = USER_ID.get();
        String currentRequestId = REQUEST_ID.get();
        System.out.println(info("Logging audit trail for User ID: ") + highlight(currentUserId) + 
                info(", Request ID: ") + highlight(currentRequestId));
    }

    private static String processTask() {
        System.out.println(info("Processing a task..."));
        String currentUserId = USER_ID.get();
        String currentRequestId = REQUEST_ID.get();
        System.out.println(info("Current User ID in processTask: ") + highlight(currentUserId) + 
                info(", Request ID: ") + highlight(currentRequestId));
        return "Task completed by user: " + currentUserId + ", Request ID: " + currentRequestId;
    }
    
    /**
     * Demonstrates more complex rebinding scenarios with nested scopes
     */
    private static void demoComplexRebinding() {
        // Create an immutable transaction context
        var initialTx = new TransactionContext("TX001", "READ_ONLY");
        
        ScopedValue.where(USER_ID, "txuser")
                .where(TX_CONTEXT, initialTx)
                .run(() -> {
                    System.out.println(info("Initial transaction: ") + transaction(TX_CONTEXT.get().toString()));
                    
                    // First level of rebinding for an operation that needs write access
                    ScopedValue.where(TX_CONTEXT, new TransactionContext("TX002", "READ_WRITE"))
                            .run(() -> {
                                System.out.println(info("Elevated transaction: ") + 
                                        transaction(TX_CONTEXT.get().toString()));
                                
                                // Simulate some data modification
                                System.out.println(warning("Performing data modification with elevated privileges"));
                                
                                // Second level of rebinding for an auditing operation
                                ScopedValue.where(USER_ID, "admin")
                                        .where(TX_CONTEXT, new TransactionContext("TX003", "AUDIT"))
                                        .run(() -> {
                                            System.out.println(info("Audit transaction: User=") + 
                                                    highlight(USER_ID.get()) + info(", Context=") + 
                                                    transaction(TX_CONTEXT.get().toString()));
                                        });
                                
                                // Back to first rebinding level
                                System.out.println(info("Back to elevated transaction: ") + 
                                        transaction(TX_CONTEXT.get().toString()) +
                                        info(" with user: ") + highlight(USER_ID.get()));
                            });
                    
                    // Back to original binding
                    System.out.println(info("Back to initial transaction: ") + 
                            transaction(TX_CONTEXT.get().toString()) + 
                            info(" with user: ") + highlight(USER_ID.get()));
                });
    }
    
    /**
     * Demonstrates error handling with ScopedValues
     */
    private static void demoErrorHandling() {
        // Using call() to handle exceptions and return values
        try {
            String result = ScopedValue.where(USER_ID, "error-user")
                    .where(REQUEST_ID, "error-req")
                    .call(() -> {
                        if (USER_ID.get().equals("error-user")) {
                            throw new RuntimeException("Simulated error in processing");
                        }
                        return "This won't be returned";
                    });
            
            System.out.println("Result: " + result + " (This won't be printed)");
        } catch (Exception e) {
            System.out.println(success("Successfully caught exception: ") + error(e.getMessage()));
        }
        
        // Demonstrating that scoped values are properly cleaned up even when exceptions occur
        try {
            ScopedValue.where(USER_ID, "recovery-user").run(() -> {
                System.out.println(info("Current user before exception: ") + highlight(USER_ID.get()));
                try {
                    throw new RuntimeException("Another simulated error");
                } catch (RuntimeException e) {
                    System.out.println(warning("Caught exception inside scope: ") + error(e.getMessage()));
                    System.out.println(info("User ID still accessible: ") + highlight(USER_ID.get()));
                }
                System.out.println(success("Execution continues in the same scope"));
            });
            
            // Try to access outside the scope
            try {
                String userId = USER_ID.get(); // This should throw NoSuchElementException
                System.out.println("This shouldn't print: " + userId);
            } catch (NoSuchElementException e) {
                System.out.println(success("Verified scoped value was properly cleaned up: ") + 
                        error(e.getMessage()));
            }
        } catch (Exception e) {
            System.out.println(error("Unexpected error: " + e.getMessage()));
        }
    }
    
    /**
     * Demonstrates comparison between ThreadLocal and ScopedValue
     */
    private static void demoThreadLocalComparison() {
        String userId = "comparison-user";
        
        // Using ThreadLocal
        System.out.println(header("Using ThreadLocal:"));
        THREAD_LOCAL_USER_ID.set(userId);
        System.out.println(info("ThreadLocal value set: ") + highlight(THREAD_LOCAL_USER_ID.get()));
        
        // Create child thread with ExecutorService
        ExecutorService executor = Executors.newSingleThreadExecutor();
        try {
            executor.submit(() -> {
                System.out.println(info("Child thread - ThreadLocal value: ") + 
                        (THREAD_LOCAL_USER_ID.get() != null ? // Will be null unless InheritableThreadLocal is used
                                highlight(THREAD_LOCAL_USER_ID.get()) : 
                                warning("null")));
                THREAD_LOCAL_USER_ID.set("modified-by-child");
                System.out.println(info("Child thread - Modified ThreadLocal: ") + 
                        highlight(THREAD_LOCAL_USER_ID.get()));
            }).get();
        } catch (Exception e) {
            System.out.println(error("Error: " + e.getMessage()));
        } finally {
            executor.shutdown();
        }
        
        System.out.println(info("Main thread after child - ThreadLocal value: ") + 
                highlight(THREAD_LOCAL_USER_ID.get())); // Still original value
        THREAD_LOCAL_USER_ID.remove();  // Cleanup is mandatory
        System.out.println(warning("After remove - ThreadLocal value: ") + 
                (THREAD_LOCAL_USER_ID.get() != null ? // Will be null after remove
                        highlight(THREAD_LOCAL_USER_ID.get()) : 
                        warning("null")));
        
        // Using ScopedValue with regular thread instead of StructuredTaskScope
        System.out.println("\n" + header("Using ScopedValue:"));
        ScopedValue.where(USER_ID, userId).run(() -> {
            System.out.println(info("Main scope - ScopedValue: ") + highlight(USER_ID.get()));
            
            // Create a regular thread instead of using StructuredTaskScope
            Thread childThread = new Thread(() -> {
                try {
                    // This will fail - ScopedValue not inherited by regular threads
                    System.out.println(info("Child thread - ScopedValue: ") + 
                            (USER_ID.isBound() ? highlight(USER_ID.get()) : warning("not bound")));
                } catch (IllegalStateException e) {
                    System.out.println(error("Child thread - ScopedValue not inherited: " + e.getMessage()));
                }
            });
            
            childThread.start();
            try {
                childThread.join();
            } catch (InterruptedException e) {
                System.out.println(error("Thread interrupted: " + e.getMessage()));
            }
            
            System.out.println(info("Main scope after child - ScopedValue: ") + highlight(USER_ID.get())); // Still bound and value is unchanged
        });
        
        // No cleanup needed, and value is automatically unavailable outside the scope
        try {
            System.out.println(warning("After scope - ScopedValue: ") + USER_ID.get()); // This will throw NoSuchElementException
        } catch (NoSuchElementException e) {
            System.out.println(success("ScopedValue automatically cleaned up: ") + error(e.getMessage()));
        }
    }
    
    /**
     * Immutable class representing transaction context
     */
    private static class TransactionContext {
        private final String id;
        private final String mode;
        
        public TransactionContext(String id, String mode) {
            this.id = id;
            this.mode = mode;
        }
        
        @Override
        public String toString() {
            return "TransactionContext{id='" + id + "', mode='" + mode + "'}";
        }
    }
}