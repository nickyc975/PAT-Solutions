import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public class PAT1003 {
    public static int[] cities;
    public static double[][] roads;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numCities = scanner.nextInt();
        int numRoads = scanner.nextInt();
        int source = scanner.nextInt();
        int target = scanner.nextInt();

        cities = new int[numCities];
        roads = new double[numCities][numCities];
        for (int i = 0; i < numCities; i++) {
            cities[i] = scanner.nextInt();
            Arrays.fill(roads[i], Double.POSITIVE_INFINITY);
        }

        for (int i = 0; i < numRoads; i++) {
            int s = scanner.nextInt(), t = scanner.nextInt();
            roads[s][t] = scanner.nextDouble();
            roads[t][s] = roads[s][t];
        }

        List<List<Integer>> paths = dijkstra(source, target);

        int maxSum = 0;
        for (List<Integer> path : paths) {
            int sum = 0;
            for (int city : path) {
                sum += cities[city];
            }
            maxSum = Math.max(sum, maxSum);
        }

        System.out.print(paths.size() + " " + maxSum);

        scanner.close();
    }

    private static List<List<Integer>> dijkstra(int source, int target) {
        Set<Integer> left = new HashSet<>();
        double[] distances = new double[cities.length];
        Set<Integer>[] paths = (Set<Integer>[]) new Set<?>[cities.length];

        for (int i = 0; i < cities.length; i++) {
            if (i == source) {
                distances[i] = 0;
            } else {
                distances[i] = Double.POSITIVE_INFINITY;
            }

            left.add(i);
            paths[i] = new HashSet<>();
        }

        int nearestCity;
        double minDistance;
        do {
            nearestCity = source;
            minDistance = Double.POSITIVE_INFINITY;
            for (int city : left) {
                if (distances[city] < minDistance) {
                    nearestCity = city;
                    minDistance = distances[city];
                }
            }

            left.remove(nearestCity);

            for (int city : left) {
                double newDistance = distances[nearestCity] + roads[nearestCity][city];
                if (newDistance < distances[city]) {
                    distances[city] = newDistance;
                    paths[city].clear();
                    paths[city].add(nearestCity);
                } else if (newDistance == distances[city] && Double.isFinite(newDistance)) {
                    paths[city].add(nearestCity);
                }
            }
        } while (!left.isEmpty() && minDistance != Double.POSITIVE_INFINITY);
        
        return findPaths(paths, source, target);
    }

    private static List<List<Integer>> findPaths(Set<Integer>[] paths, int source, int target) {
        List<List<Integer>> result = new ArrayList<>();
        if (source == target) {
            result.add(new ArrayList<>());
        } else {
            for (int inter : paths[target]) {
                result.addAll(findPaths(paths, source, inter));
            }
        }

        for (List<Integer> path : result) {
            path.add(target);
        }

        return result;
    }
}