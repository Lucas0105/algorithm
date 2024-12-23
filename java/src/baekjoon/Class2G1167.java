package baekjoon;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

class Node {
    int weight, target;

    public Node(int t, int w) {
        this.target = t; this.weight = w;
    }
}

class NodeComparator implements Comparator<Node> {

    @Override
    public int compare(Node o1, Node o2) {
        return o1.weight - o2.weight;
    }
}

public class Class2G1167 {

    static int V;
    static List<Node>[] Graph = new ArrayList[100001];
    static int[] distance;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        V = Integer.parseInt(st.nextToken());

        for(int i = 1; i <= V; i++) {
            st = new StringTokenizer(br.readLine());
            int start = Integer.parseInt(st.nextToken());
            Graph[start] = new ArrayList<Node>();

            while(st.hasMoreTokens()) {
               int target = Integer.parseInt(st.nextToken());
               if(target == -1)
                   break;
               int weight = Integer.parseInt(st.nextToken());
               Node newNode = new Node(target, weight);
               Graph[start].add(newNode);
            }
        }

        dijkstra(1);

        int maxV = 0;
        int maxN = 1;
        for(int i = 1; i <= V; i++){
            if(maxV < distance[i]){
                maxV = distance[i];
                maxN = i;
            }
        }

        dijkstra(maxN);

        for(int i = 1; i <= V; i++){
            if(maxV < distance[i]){
                maxV = distance[i];
            }
        }

        System.out.println(maxV);
    }

    public static void dijkstra(int start) {
        Queue<Node> pq = new PriorityQueue<>(new NodeComparator());
        pq.add(new Node(start, 0));
        distance = new int[V + 1];
        for(int i = 1; i <= V; i++)distance[i] = (int) 2e10;
        distance[start] = 0;
        boolean[] visited = new boolean[V + 1];

        while(!pq.isEmpty()){
            Node sNode = pq.poll();

            if(visited[sNode.target])
                continue;

            visited[sNode.target] = true;

            for(int i = 0; i < Graph[sNode.target].size(); i++) {
                Node tNode = Graph[sNode.target].get(i);

                if(visited[tNode.target])
                    continue;

                if(distance[tNode.target] > tNode.weight + sNode.weight){
                    distance[tNode.target] = tNode.weight + sNode.weight;
                    pq.add(new Node(tNode.target, distance[tNode.target]));
                }
            }
        }
    }
}
