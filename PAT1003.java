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
                // System.out.print(city + " ");
            }
            // System.out.println();
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
            if (i != source) {
                left.add(i);
            }
            paths[i] = new HashSet<>();
            distances[i] = roads[source][i];
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
                    distances[city] = distances[nearestCity] + roads[nearestCity][city];
                    paths[city].clear();
                    paths[city].add(nearestCity);
                } else if (newDistance == distances[city] && Double.isFinite(distances[city])) {
                    paths[city].add(nearestCity);
                }
            }
        } while (!left.isEmpty() && nearestCity != source);
        
        List<List<Integer>> result = findPaths(paths, source, target);
        if (distances[target] == roads[source][target]) {
            List<Integer> path = new ArrayList<>();
            path.add(source);
            path.add(target);
            result.add(path);
        }
        return result;
    }

    private static List<List<Integer>> findPaths(Set<Integer>[] paths, int source, int target) {
        List<List<Integer>> result = new ArrayList<>();
        if (paths[target] != null && paths[target].isEmpty()) {
            List<Integer> path = new ArrayList<>();
            path.add(source);
            result.add(path);
        } else {
            for (int inter : paths[target]){
                List<List<Integer>> foundPaths = findPaths(paths, source, inter);
                result.addAll(foundPaths);
            }
        }

        for (List<Integer> path : result) {
            path.add(target);
        }

        return result;
    }
}