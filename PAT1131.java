import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

public class PAT1131 {
    private static Map<Integer, Map<Integer, Integer>> map = new HashMap<>();
    private static Map<Integer, Map<Integer, Integer>> paths = new HashMap<>();
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int lineNum = scanner.nextInt();
        for (int i = 0; i < lineNum; i++) {
            int stationNum = scanner.nextInt();
            int station, lastStation = scanner.nextInt();
            for (int j = 1; j < stationNum; j++) {
                station = scanner.nextInt();
                if (!map.containsKey(lastStation)) {
                    map.put(lastStation, new HashMap<>());
                }
                map.get(lastStation).put(station, i + 1);

                if (!map.containsKey(station)) {
                    map.put(station, new HashMap<>());
                }
                map.get(station).put(lastStation, i + 1);

                lastStation = station;
            }
        }

        buildPath();

        int queryNum = scanner.nextInt();
        for (int i = 0; i < queryNum; i++) {
            printPath(scanner.nextInt(), scanner.nextInt());
        }

        scanner.close();
    }

    private static void buildPath() {
        Set<Integer> stations = map.keySet();
        Map<Integer, Map<Integer, Pair>> distance = new HashMap<>();
        for (int source : stations) {
            Map<Integer, Pair> dis = new HashMap<>();
            for (int target : stations) {
                if (source == target) {
                    dis.put(target, new Pair(0, 0.0));
                } else {
                    dis.put(target, new Pair(0, Double.POSITIVE_INFINITY));
                }
                paths.put(source, new HashMap<>());
            }
            distance.put(source, dis);
        }

        for (int inter : stations) {
            for (int source : stations) {
                for (int target : stations) {
                    if (source != inter && target != inter) {
                        if (map.get(source).get(target) != null) {
                            distance.get(source).get(target)._2 = 1.0;
                            paths.get(source).put(target, source);
                        } else if (distance.get(source).get(inter)._2 + distance.get(inter).get(target)._2 < distance.get(source).get(target)._2) {
                            distance.get(source).get(target)._1 = distance.get(source).get(inter)._1 + distance.get(inter).get(target)._1;
                            distance.get(source).get(target)._2 = distance.get(source).get(inter)._2 + distance.get(inter).get(target)._2;
                            if (map.get(source).get(inter) != null && map.get(inter).get(target) != null && map.get(source).get(inter) != map.get(inter).get(target)) {
                                distance.get(source).get(target)._1 = 1;
                            }
                            paths.get(source).put(target, inter);
                        } else if (distance.get(source).get(inter)._2 + distance.get(inter).get(target)._2 == distance.get(source).get(target)._2) {
                            if (Double.isFinite(distance.get(source).get(target)._2) && distance.get(source).get(inter)._1 + distance.get(inter).get(target)._1 < distance.get(source).get(target)._1) {
                                distance.get(source).get(target)._1 = distance.get(source).get(inter)._1 + distance.get(inter).get(target)._1;
                                paths.get(source).put(target, inter);
                            }
                        }
                    }
                }
            }
        }
    }

    private static void printPath(int source, int target) {
        List<Integer> path = new LinkedList<>();
        path.add(source); path.add(target);
        int inter = paths.get(source).get(target);
        path.add(path.indexOf(target), inter);
        findPath(source, inter, path);
        findPath(inter, target, path);

        System.out.println(path.size() - 1);
        Iterator<Integer> iterator = path.iterator();
        int lastStop = iterator.next();
        int lastStation = lastStop, station = iterator.next(), nextStation;
        while (iterator.hasNext()) {
            nextStation = iterator.next();
            if (map.get(lastStation).get(station) != map.get(station).get(nextStation)) {
                System.out.println(String.format("Take Line#%d from %4d to %4d.", map.get(lastStation).get(station), lastStop, station));
                lastStop = station;
            }
            lastStation = station;
            station = nextStation;
        }
        System.out.println(String.format("Take Line#%d from %4d to %4d.", map.get(lastStation).get(station), lastStop, station));
    }

    private static void findPath(int source, int target, List<Integer> path) {
        int inter = paths.get(source).get(target);
        if (source != inter) {
            path.add(path.indexOf(target), inter);
            findPath(source, inter, path);
            findPath(inter, target, path);
        }
    }
}

class Pair {
    public int _1;
    public double _2;

    public Pair(int _1, double _2) {
        this._1 = _1;
        this._2 = _2;
    }
}

/**
4
6 1001 3212 1003 1204 1306 7797
9 9988 2333 1204 2006 2005 2004 2003 2302 2001
13 3011 3812 3013 3001 1306 3003 2333 3066 3212 3008 2302 3010 3011
4 6666 8432 4011 1306
3
7797 9988
3001 9988
4011 9988
 */