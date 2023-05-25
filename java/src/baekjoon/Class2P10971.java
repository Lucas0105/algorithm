package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class2P10971 {
	static int N;
	static int [][] graph;
	static boolean [] visited;
	static int result;
	
	public static void main(String[] args) throws  IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		graph = new int[N][N];
		visited = new boolean[N];
		StringTokenizer st;
		result = 20000000;
		
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < N; j++) {
				graph[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		

		dfs(0, 0, 0);
		
		System.out.println(result);
	}
	
	static void dfs(int status, int cur_node, int cnt) {
		
		// N-1일 때 종료
		if (cnt == N-1) {
			if (graph[cur_node][0] == 0) return;
			if (status + graph[cur_node][0] < result) result = status + graph[cur_node][0];
			return;
		}
		
		// 한 노드에서 갈 수 있는 모든 경로 재귀
		for (int next_node = 1; next_node < N; next_node++) {
			if(!visited[next_node] && graph[cur_node][next_node] != 0) {
				visited[next_node] = true;
				dfs(status+graph[cur_node][next_node], next_node, cnt+1);
				visited[next_node] = false;
			}
		}
	}

}
