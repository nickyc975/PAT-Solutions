import java.util.Scanner;

public class PAT1001 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int sum = scanner.nextInt() + scanner.nextInt();

        String sumStr = Math.abs(sum) + "";
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < sumStr.length(); i++) {
            if (i > 0 && i % 3 == 0) {
                builder.append(",");
            }
            builder.append(sumStr.charAt(sumStr.length() - i - 1));
        }
        if (sum < 0) {
            builder.append("-");
        }
        System.out.println(builder.reverse().toString());
        scanner.close();
    }
}