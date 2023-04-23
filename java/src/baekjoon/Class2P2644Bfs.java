package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Class2P2644Bfs {
	static int N, x, y, M;
	static LinkedList<Integer> [] graph;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine());
		x = Integer.parseInt(st.nextToken());
		y = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(br.readLine());
		graph = new LinkedList [N+1];
		
		for (int i = 0 ; i <= N; i++) graph[i] = new LinkedList<Integer>();
		
		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			int n_x = Integer.parseInt(st.nextToken());
			int n_y = Integer.parseInt(st.nextToken());
			graph[n_x].add(n_y);
			graph[n_y].add(n_x);
		}
		
		System.out.println(bfs());
	}
	
	static int bfs() {
		boolean[] visited = new boolean[N+1];
		Queue<Integer []> queue = new LinkedList<Integer []>();
		queue.offer(new Integer [] {x, 1});
		visited[x] = true;
		
		while (!queue.isEmpty()) {
			Integer cur_value[] = queue.poll();
			
			for (Integer next_value : graph[cur_value[0]]) {
				if (next_value == y) return cur_value[1];
				
				if (!visited[next_value]) {
					visited[next_value] = true;
					queue.offer(new Integer [] {next_value, cur_value[1] + 1});
				}
			}
		}
		
		return -1;
	}

}
