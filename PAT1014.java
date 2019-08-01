import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;

public class PAT1014 {
    private static int capacity;
    private static int queryNum;
    private static Line[] windows;
    private static int[] customers;
    private static int[] customerTrans;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        windows = new Line[scanner.nextInt()];
        Arrays.fill(windows, null);
        capacity = scanner.nextInt();
        customers = new int[scanner.nextInt()];
        customerTrans = new int[customers.length];
        Arrays.fill(customers, 0);
        queryNum = scanner.nextInt();

        int totalCapacity = windows.length * capacity;
        for (int i = 0; i < customers.length; i++) {
            int index, time = scanner.nextInt();
            if (i < totalCapacity) {
                index = findPeopleNumMin(windows);
            } else {
                index = findWaitTimeMin(windows);
            }

            windows[index].push(i);
            windows[index].totalTime += time;
            customers[i] = windows[index].totalTime;
            customerTrans[i] = time;
        }

        for (int i = 0; i < queryNum; i++) {
            int index = scanner.nextInt() - 1;
            int time = customers[index];
            if (time - customerTrans[index] < 540) {
                int minutes = time % 60;
                int hours = 8 + (time - minutes) / 60;
                System.out.println(String.format("%2d:%2d", hours, minutes).replace(" ", "0"));
            } else {
                System.out.println("Sorry");
            }
        }

        scanner.close();
    }

    private static int findPeopleNumMin(Line[] windows) {
        int minIndex = 0;
        Line minValue = windows[minIndex];
        for (int i = 0; i < windows.length; i++) {
            if (windows[i] == null) {
                minIndex = i;
                windows[i] = new Line();
                break;
            } else if (windows[i].size() < minValue.size()) {
                minIndex = i;
                minValue = windows[i];
            }
        }
        return minIndex;
    }

    private static int findWaitTimeMin(Line[] windows) {
        int minIndex = 0;
        Line minValue = windows[minIndex];
        for (int i = 0; i < windows.length; i++) {
            if (windows[i] == null) {
                minIndex = i;
                windows[i] = new Line();
                break;
            } else if (customers[windows[i].peek()] < customers[minValue.peek()]) {
                minIndex = i;
                minValue = windows[i];
            }
        }

        minValue.poll();

        return minIndex;
    }

    private static class Line {
        private int totalTime = 0;
        private LinkedList<Integer> queue = new LinkedList<>();

        public int peek() {
            return queue.isEmpty() ? 0 : queue.getFirst();
        }

        public int poll() {
            return queue.isEmpty() ? 0 : queue.remove();
        }

        public int size() {
            return queue.size();
        }

        public void push(int e) {
            queue.add(e);
        }
    }
}