import java.util.Scanner;
import java.util.SortedMap;
import java.util.SortedSet;
import java.util.TreeMap;
import java.util.TreeSet;

public class PAT1022 {
    private static SortedMap<String, SortedSet<Integer>> Titles = new TreeMap<>();
    private static SortedMap<String, SortedSet<Integer>> Authors = new TreeMap<>();
    private static SortedMap<String, SortedSet<Integer>> Keywords = new TreeMap<>();
    private static SortedMap<String, SortedSet<Integer>> Publishers = new TreeMap<>();
    private static SortedMap<Integer, SortedSet<Integer>> Years = new TreeMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int bookNum = Integer.parseInt(scanner.nextLine());

        int id, year;
        SortedSet<Integer> books;
        String title, author, keywords[], publisher;
        for (int i = 0; i < bookNum; i++) {
            id = Integer.parseInt(scanner.nextLine());
            title = scanner.nextLine();
            author = scanner.nextLine();
            keywords = scanner.nextLine().split(" ");
            publisher = scanner.nextLine();
            year = Integer.parseInt(scanner.nextLine());

            books = Titles.getOrDefault(title, new TreeSet<>());
            Titles.putIfAbsent(title, books);
            books.add(id);

            books = Authors.getOrDefault(author, new TreeSet<>());
            Authors.putIfAbsent(author, books);
            books.add(id);

            for (String keyword : keywords) {
                books = Keywords.getOrDefault(keyword, new TreeSet<>());
                Keywords.putIfAbsent(keyword, books);
                books.add(id);
            }

            books = Publishers.getOrDefault(publisher, new TreeSet<>());
            Publishers.putIfAbsent(publisher, books);
            books.add(id);

            books = Years.getOrDefault(year, new TreeSet<>());
            Years.putIfAbsent(year, books);
            books.add(id);
        }

        int queryNum = Integer.parseInt(scanner.nextLine());
        for (int i = 0; i < queryNum; i++) {
            String query[] = scanner.nextLine().split(": ");
            switch (query[0]) {
            case "1":
                books = Titles.get(query[1]);
                break;
            case "2":
                books = Authors.get(query[1]);
                break;
            case "3":
                books = Keywords.get(query[1]);
                break;
            case "4":
                books = Publishers.get(query[1]);
                break;
            case "5":
                books = Years.get(Integer.parseInt(query[1]));
                break;
            default:
                books = null;
                break;
            }

            System.out.printf("%s: %s\n", query[0], query[1]);
            if (books == null) {
                System.out.println("Not Found");
            } else {
                for (int book : books) {
                    System.out.printf("%07d\n", book);
                }
            }
        }
        scanner.close();
    }
}