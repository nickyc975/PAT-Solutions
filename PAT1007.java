import java.util.Scanner;

public class PAT1007 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Interval[] numbers = new Interval[scanner.nextInt()];
        for (int i = 0; i < numbers.length; i++) {
            int value = scanner.nextInt();
            numbers[i] = new Interval(value, value, value);
        }

        int valueNum = 0;
        for (int i = 0; i < numbers.length; ) {
            int j = i + 1;
            if (numbers[i].sum >= 0) {
                while (j < numbers.length && numbers[j].sum >= 0) {
                    numbers[i].sum += numbers[j].sum;
                    numbers[i].right = numbers[j].right;
                    j++;
                }
            } else {
                while (j < numbers.length && numbers[j].sum < 0) {
                    numbers[i].sum += numbers[j].sum;
                    numbers[i].right = numbers[j].right;
                    j++;
                }
            }
            numbers[valueNum] = numbers[i];
            valueNum++;
            i = j;
        }

        for (int i = 0; i < valueNum; i++) {
            System.out.println(numbers[i]);
        }

        scanner.close();
    }

    private static class Interval {
        public int sum;
        public int left;
        public int right;

        private Interval(int sum, int left, int right) {
            this.sum = sum;
            this.left = left;
            this.right = right;
        }

        @Override
        public String toString() {
            return sum + " " + left + " " + right;
        }
    }
}