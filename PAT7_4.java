import java.util.HashMap;
import java.util.Scanner;

public class PAT7_4 {
    private static boolean isFull = true;
    private static int[] inOrder = new int[32];
    private static int[] postOrder = new int[32];
    private static HashMap<Integer, Integer> indexOf = new HashMap<>();
    private static HashMap<Integer, Node> nodes = new HashMap<>();

    private static Node buildTree(int inL, int inR, int postRoot) {
        Node node = new Node(postOrder[postRoot]);
        nodes.put(postOrder[postRoot], node);

        if (inL >= inR) {
            return node;
        }
        int inRoot = indexOf.get(postOrder[postRoot]);
        if (inL < inRoot) {
            node.lchild = buildTree(inL, inRoot - 1, postRoot - inR + inRoot - 1);
            node.lchild.parent = node;
        }

        if (inR > inRoot) {
            node.rchild = buildTree(inRoot + 1, inR, postRoot - 1);
            node.rchild.parent = node;
        }

        if (isFull && (node.lchild == null || node.rchild == null)) {
            isFull = false;
        }
        return node;
    }

    private static int getLevel(Node node) {
        if (node == null) {
            return 0;
        } else {
            return getLevel(node.parent) + 1;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int nodeNum = scanner.nextInt();
        for (int i = 0; i < nodeNum; i++)
        {
            postOrder[i] = scanner.nextInt();
        }
        for (int i = 0; i < nodeNum; i++)
        {
            inOrder[i] = scanner.nextInt();
            indexOf.put(inOrder[i], i);
        }
        
        buildTree(0, nodeNum - 1, nodeNum - 1);

        int queryNum = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < queryNum; i++)
        {
            boolean flag = false;
            String line = scanner.nextLine();
            String[] parts = line.split(" ");
            if (line.contains("root")) {
                int node = Integer.parseInt(parts[0]);
                flag = nodes.get(node).parent == null;
            } else if (line.contains("siblings")) {
                int a = Integer.parseInt(parts[0]);
                int b = Integer.parseInt(parts[2]);
                flag = a != b && nodes.get(a).parent == nodes.get(b).parent;
            } else if (line.contains("parent")) {
                int a = Integer.parseInt(parts[0]);
                int b = Integer.parseInt(parts[5]);
                flag = nodes.get(b).parent == nodes.get(a);
            } else if (line.contains("left")) {
                int a = Integer.parseInt(parts[0]);
                int b = Integer.parseInt(parts[6]);
                flag = nodes.get(b).lchild == nodes.get(a);
            } else if (line.contains("right")) {
                int a = Integer.parseInt(parts[0]);
                int b = Integer.parseInt(parts[6]);
                flag = nodes.get(b).rchild == nodes.get(a);
            } else if (line.contains("same")) {
                int a = Integer.parseInt(parts[0]);
                int b = Integer.parseInt(parts[2]);
                flag = getLevel(nodes.get(a)) == getLevel(nodes.get(b));
            } else if (line.contains("full")) {
                flag = isFull;
            }
            System.out.println(flag ? "Yes" : "No");
        }
        scanner.close();
    }
}

class Node {
    public int value;
    public Node parent, lchild, rchild;

    public Node(int value) {
        this.value = value;
        this.parent = null;
        this.lchild = null;
        this.rchild = null;
    }
}