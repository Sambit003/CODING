public class FactorialException {
    public static class NegativeInputException extends Exception {
      public NegativeInputException(String message) {
        super(message);
      }
    }
    public static long calculateFactorial(int number) throws NegativeInputException {
      if (number < 0) {
        throw new NegativeInputException("Factorial is not defined for negative numbers.");
      }
      long result = 1;
      for (int i = 2; i <= number; i++) {
        result *= i;
      }
      return result;
    }
    public static void main(String[] args) {
      int num;
      try {
        System.out.print("Enter a non-negative number: ");
        num = Integer.parseInt(System.console().readLine());
        long factorial = calculateFactorial(num);
        System.out.println("Factorial of " + num + " is " + factorial);
      } catch (NegativeInputException e) {
        System.err.println("Error: " + e.getMessage());
      } catch (NumberFormatException e) {
        System.err.println("Error: Please enter a valid number.");
      }
    }
  }
  