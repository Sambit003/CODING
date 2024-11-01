import java.util.Scanner;

public class ArrayReverse {

    public void reverseArray(int[] arr) {
        int start = 0;
        int end = arr.length - 1;

        while (start < end) {
            arr[start] ^= arr[end];
            arr[end] ^= arr[start];
            arr[start] ^= arr[end];

            start++;
            end--;
        }
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Enter the size of the array: ");
            int size = scanner.nextInt();

            int[] arr = new int[size];
            System.out.println("Enter the elements of the array:");
            for (int i = 0; i < size; i++) {
                arr[i] = scanner.nextInt();
            }

            ArrayReverse obj = new ArrayReverse();
            obj.reverseArray(arr);  

            System.out.println("Reversed Array:");
            for (int num : arr) {
                System.out.print(num + " ");
            }
        }
    }
}