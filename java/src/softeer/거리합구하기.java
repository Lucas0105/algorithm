package softeer;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class 거리합구하기 {
	static LinkedList<Integer[]>[] graph;
	public static long [] subTree;
	public static int N;
	public static long [] distSum;
	
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
				
		N = Integer.parseInt(br.readLine());
		graph = new LinkedList[N+1];
		subTree = new long [N+1];
		distSum = new long [N+1];
		
		for(int n = 0; n < N+1; n++) graph[n] = new LinkedList<>();
		
		for (int i = 0; i <N - 1; i++) {
			st = new StringTokenizer(br.readLine());
			
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			int weight = Integer.parseInt(st.nextToken());
			
			graph[start].add(new Integer[] {end, weight});
			graph[end].add(new Integer[] {start, weight});
		}
		
		dfs(1, 1);
		dfs2(1, 1);
				
		for (int i = 1; i <= N; i++) {
			System.out.println(distSum[i]);
		}
	}
	
	public static void dfs(int current, int parent) {
		subTree[current] = 1;
		
		for (Integer[] arr : graph[current]) {
			int child = arr[0];
			int weight = arr[1];
			
			if (child != parent) {
				dfs(child, current);
				distSum[current] += distSum[child] + subTree[child] * weight;
				subTree[current] += subTree[child];
			}
		}
	}
	
	public static void dfs2(int current, int parent) {
		for (Integer[] arr : graph[current]) {
			int child = arr[0];
			int weight = arr[1];
			
			if (child != parent) {
				distSum[child] = distSum[current] + weight * (N - 2 * subTree[child]);
				dfs2(child, current);
			}
		}
	}

}
