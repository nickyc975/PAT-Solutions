import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class PAT1004 {
    private static int depth = 0;
    private static int[] count = new int[100];
    private static Person[] family = new Person[100];

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        for (int i = 0; i < 100; i++) {
            family[i] = new Person();
        }
        int total = scanner.nextInt();
        int lineNum = scanner.nextInt();
        for (int i = 0; i < lineNum; i++) {
            int id = scanner.nextInt();
            int numChildren = scanner.nextInt();
            for (int j = 0; j < numChildren; j++) {
                family[id].children.add(scanner.nextInt());
            }
        }

        countLeaves(1, 0);

        System.out.print(count[0]);
        for (int i = 1; i <= depth; i++) {
            System.out.print(" " + count[i]);
        }
        scanner.close();
    }

    private static void countLeaves(int id, int level) {
        if (family[id].children.isEmpty()) {
            depth = Math.max(level, depth);
            count[level]++;
        } else {
            for (int childId : family[id].children) {
                countLeaves(childId, level + 1);
            }
        }
    }

    private static class Person {
        public Set<Integer> children = new HashSet<>();
    }
}