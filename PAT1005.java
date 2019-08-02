import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class PAT1005 {
    private static String[] DIGITS = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String integer = scanner.nextLine();
        int sum = (int) integer.chars()
            .filter(ch -> Character.isDigit((char) ch))
            .mapToLong(ch -> Long.valueOf((char) ch + ""))
            .sum();
        printInt(sum);
        scanner.close();
    }

    private static void printInt(int value) {
        if (value == 0) {
            System.out.print(DIGITS[0]);
        } else {
            List<String> result = new ArrayList<>();
            while (value > 0) {
                result.add(0, DIGITS[value % 10]);
                value /= 10;
            }
            System.out.print(String.join(" ", result));
        }
    }
}