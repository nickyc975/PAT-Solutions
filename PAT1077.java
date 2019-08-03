import java.util.Scanner;

public class PAT1077 {
    public static void main(String[] args) {
        Scanner scanner =  new Scanner(System.in);

        int N = Integer.parseInt(scanner.nextLine());

        String suffix = scanner.nextLine();
        for (int i = 1; i < N && suffix.length() > 0; i++) {
            String line = scanner.nextLine();

            int j, lineLength = line.length();
            int suffixLength = suffix.length();
            int minLength = Math.min(lineLength, suffixLength);
            for (j = 1; j <= minLength; j++) {
                if (line.charAt(lineLength - j) != suffix.charAt(suffixLength - j)) {
                    break;
                }
            }

            suffix = suffix.substring(suffixLength - j + 1, suffixLength);
        }

        if (suffix.length() > 0) {
            System.out.print(suffix);
        } else {
            System.out.print("nai");
        }

        scanner.close();
    }
}