import java.util.Scanner;

public class PAT1007 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int length = scanner.nextInt();
        int left = 0, right = 0, sum = -1;
        int temp_left = 0, temp_sum = temp_left;
        int first = 0, last = 0;

        boolean updateLeft = true;
        for (int i = 0; i < length; i++) {
            int value = scanner.nextInt();
            if (i == 0) {
                first = value;
            }
            
            if (i == length - 1) {
                last = value;
            }

            if (updateLeft) {
                temp_left = value;
                updateLeft = false;
            }

            temp_sum += value;
            if (temp_sum > sum) {
                sum = temp_sum;
                right = value;
                left = temp_left;
            } else if (temp_sum <= 0) {
                temp_sum = 0;
                updateLeft = true;
            }
        }

        if (sum < 0) {
            System.out.print(0 + " " + first + " " + last);
        } else {
            System.out.print(sum + " " + left + " " + right);
        }

        scanner.close();
    }
}