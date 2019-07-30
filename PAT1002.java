import java.util.Scanner;

public class PAT1002 {
    public static void main(String[] args) {
        int nodeCount = 0;
        Node head = new Node(), tail = head;

        Scanner scanner = new Scanner(System.in);
        int K1 = scanner.nextInt();
        for (int i = 0; i < K1; i++) {
            tail.next = new Node();
            tail = tail.next;
            tail.exponent = scanner.nextInt();
            tail.coefficient = scanner.nextDouble();
            nodeCount++;
        }

        Node cursor = head;
        int K2 = scanner.nextInt();
        for (int i = 0; i < K2; i++) {
            int exponent = scanner.nextInt();
            double coefficient = scanner.nextDouble();
            while (cursor.next != null && cursor.next.exponent > exponent) {
                cursor = cursor.next;
            }

            if (cursor.next == null) {
                cursor.next = new Node();
                cursor.next.exponent = exponent;
                cursor.next.coefficient = coefficient;
                nodeCount++;
            } else if (cursor.next.exponent == exponent) {
                cursor.next.coefficient += coefficient;
                if (cursor.next.coefficient == 0.0D) {
                    cursor.next = cursor.next.next;
                    nodeCount--;
                }
            } else {
                Node node = new Node();
                node.next = cursor.next;
                node.exponent = exponent;
                node.coefficient = coefficient;
                cursor.next = node;
                nodeCount++;
            }
        }

        cursor = head;
        System.out.print(nodeCount);
        while (cursor.next != null) {
            System.out.printf(" %d %.1f", cursor.next.exponent, cursor.next.coefficient);
            cursor = cursor.next;
        }
        scanner.close();
    }

    private static class Node {
        public int exponent = 0;
        public double coefficient = 0.0D;
        public Node next = null;
    }
}