package jdk_24_update_demo;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Gatherer;
import java.util.stream.Gatherers;

public class StreamGathererDemo {

    /**
     * Represents a blog post with a title, category, and publish date.
     */
    public static class Blog {
        private final String title;
        private final String category;
        private final LocalDate publishDate;

        public Blog(final String title, final String category, final LocalDate publishDate) {
            this.title = title;
            this.category = category;
            this.publishDate = publishDate;
        }

        public String getTitle() {
            return title;
        }

        public String getCategory() {
            return category;
        }

        public LocalDate getPublishDate() {
            return publishDate;
        }

        @Override
        public String toString() {
            return "Blog{" +
                    "title='" + title + '\'' +
                    ", category='" + category + '\'' +
                    ", publishDate=" + publishDate +
                    '}';
        }
    }

    /**
     * Contains custom Gatherer implementations.
     */
    public static class CustomGatherers {

        /**
         * Returns a Gatherer that groups elements by a key and limits the number of elements
         * in each group.
         *
         * @param keyExtractor  Function to extract the grouping key from each element.
         * @param limit         Maximum number of elements to include in each group.
         * @param <T>           Type of the input element.
         * @param <K>           Type of the grouping key.
         * @return A Gatherer that performs group-by-limit operation.
         */
        public static <T, K> Gatherer<T, Map<K, List<T>>, Map<K, List<T>>> groupByLimit(
                final Function<T, K> keyExtractor, final int limit) {
            return Gatherer.ofSequential(
                    HashMap::new,
                    (Map<K, List<T>> state, T element, Gatherer.Downstream<? super Map<K, List<T>>> downstream) -> {
                        K key = keyExtractor.apply(element);
                        List<T> list = state.computeIfAbsent(key, k -> new ArrayList<>());
                        if (list.size() < limit) {
                            list.add(element);
                        }
                        return true;
                    },
                    (map, downstream) -> downstream.push(map)
            );
        }

        /**
         * Returns a Gatherer that groups elements by a key and keeps only the most recent N elements
         * in each group based on a provided comparator.
         *
         * @param keyExtractor Function to extract the grouping key from each element.
         * @param limit        Maximum number of recent elements to keep in each group.
         * @param comparator   Comparator to determine the order of elements (most recent first).
         * @param <T>          Type of the input element.
         * @param <K>          Type of the grouping key.
         * @return A Gatherer that performs group-by-recent-limit operation.
         */
        public static <T, K> Gatherer<T, Map<K, List<T>>, Map<K, List<T>>> groupByRecentLimit(
                final Function<T, K> keyExtractor, final int limit, final Comparator<T> comparator) {
            return Gatherer.ofSequential(
                    HashMap::new,
                    (Map<K, List<T>> state, T element, Gatherer.Downstream<? super Map<K, List<T>>> downstream) -> {
                        final K key = keyExtractor.apply(element);
                        List<T> list = state.computeIfAbsent(key, k -> new ArrayList<>());
                        list.add(element);
                        
                        // Sort and trim the list only if it exceeds the limit
                        if (list.size() > limit) {
                            list.sort(comparator);
                            while (list.size() > limit) {
                                list.remove(list.size() - 1); // Remove the least recent
                            }
                        }
                        return true;
                    },
                    (map, downstream) -> {
                        // Ensure all lists are properly sorted before returning
                        map.forEach((key, list) -> list.sort(comparator));
                        downstream.push(map);
                    }
            );
        }

        /**
         * Creates a sliding window gatherer that produces lists of consecutive elements.
         *
         * @param windowSize The size of the sliding window
         * @param <T>        The type of elements in the stream
         * @return A gatherer that produces sliding windows of elements
         */
        public static <T> Gatherer<T, List<T>, List<T>> sliding(int windowSize) {
            if (windowSize <= 0) {
                throw new IllegalArgumentException("Window size must be positive");
            }
            
            return Gatherer.ofSequential(
                    ArrayList::new,
                    (List<T> state, T element, Gatherer.Downstream<? super List<T>> downstream) -> {
                        state.add(element);  // Add the current element to our buffer
                        
                        // If we have enough elements to form a window, emit it
                        if (state.size() >= windowSize) {
                            List<T> window = new ArrayList<>(state.subList(0, windowSize));
                            downstream.push(window);
                            state.remove(0);  // Remove the oldest element
                        }
                        return true;  // Continue processing
                    },
                    // Optional finisher to handle any remaining elements if needed
                    (state, downstream) -> {
                        // We could push remaining elements as a partial window if desired
                    }
            );
        }
    }

    public static void main(final String[] args) {
        // Sample blog posts
        final List<Blog> blogs = List.of(
                new Blog("Introduction to Gatherers", "Java", LocalDate.of(2025, 3, 20)),
                new Blog("Understanding Streams", "Java", LocalDate.of(2025, 3, 15)),
                new Blog("Functional Programming in Java", "Java", LocalDate.of(2025, 3, 10)),
                new Blog("Spring Boot Basics", "Spring", LocalDate.of(2025, 3, 22)),
                new Blog("Dependency Injection", "Spring", LocalDate.of(2025, 3, 18)),
                new Blog("RESTful APIs with Spring", "Spring", LocalDate.of(2025, 3, 12)),
                new Blog("Getting Started with Project Loom", "Java", LocalDate.of(2025, 3, 25)),
                new Blog("Virtual Threads Deep Dive", "Java", LocalDate.of(2025, 3, 5)),
                new Blog("AOP with Spring", "Spring", LocalDate.of(2025, 3, 28))
        );

        System.out.println("--- Grouping blogs by category with a limit of 2 per category ---");
        final Map<String, List<Blog>> limitedCategoryBlogs = blogs.stream()
                .gather(CustomGatherers.groupByLimit(Blog::getCategory, 2))
                .findFirst() // Gatherer returns a stream, so we typically take the first (and only) result.
                .orElse(Map.of());

        limitedCategoryBlogs.forEach((category, blogList) -> {
            System.out.println("Category: " + category);
            blogList.forEach(blog -> System.out.println("  - " + blog));
        });

        System.out.println("\n--- Getting the 2 most recent blogs per category ---");
        final Map<String, List<Blog>> recentCategoryBlogs = blogs.stream()
                .gather(CustomGatherers.groupByRecentLimit(
                        Blog::getCategory,
                        2,
                        Comparator.comparing(Blog::getPublishDate).reversed()
                ))
                .findFirst()
                .orElse(Map.of());

        recentCategoryBlogs.forEach((category, blogList) -> {
            System.out.println("Category: " + category);
            blogList.forEach(blog -> System.out.println("  - " + blog));
        });
        
        // New examples showcasing additional Gatherer features
        
        // Example 1: Using sliding window gatherer
        System.out.println("\n--- Using sliding window gatherer (window size = 3) ---");
        blogs.stream()
            .sorted(Comparator.comparing(Blog::getPublishDate))
            .gather(CustomGatherers.sliding(3))
            .forEach(window -> {
                System.out.println("Window:");
                window.forEach(blog -> System.out.println("  - " + blog.getTitle() + " (" + blog.getPublishDate() + ")"));
                System.out.println();
            });
            
        // Example 2: Using built-in fold gatherer (summing the lengths of all blog titles)
        System.out.println("\n--- Using built-in Gatherers.fold (calculate average blog title length) ---");
        double averageTitleLength = blogs.stream()
            .map(blog -> blog.getTitle().length())  // Extract title lengths first
            .gather(Gatherers.fold(
                () -> 0,
                (sum, length) -> sum + length
            ))
            .findFirst()
            .orElse(0) / (double) blogs.size();
        
        System.out.printf("Average blog title length: %.2f characters%n", averageTitleLength);
        
        // Example 3: Comparison between traditional stream operations and gatherers
        System.out.println("\n--- Traditional Stream vs Gatherer approach for category grouping ---");
        
        // Traditional approach with collectors
        System.out.println("Using traditional Stream collectors:");
        Map<String, List<Blog>> traditionalGrouping = blogs.stream()
            .collect(java.util.stream.Collectors.groupingBy(Blog::getCategory));
        
        // Filter to limit 2 per category after collection (less efficient)
        traditionalGrouping.forEach((category, list) -> {
            System.out.println("Category: " + category + " (showing 2 of " + list.size() + " entries)");
            list.stream()
                .limit(2)
                .forEach(blog -> System.out.println("  - " + blog.getTitle()));
        });
        
        // Gatherer approach - more efficient as it limits during processing
        System.out.println("\nUsing Gatherer (more efficient):");
        blogs.stream()
            .gather(CustomGatherers.groupByLimit(Blog::getCategory, 2))
            .findFirst()
            .orElse(Map.of())
            .forEach((category, list) -> {
                System.out.println("Category: " + category);
                list.forEach(blog -> System.out.println("  - " + blog.getTitle()));
            });
    }
}
