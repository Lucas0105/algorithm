package softeer;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
	static long subTree[];
	static long [] distSum;
	static int N;
	static ArrayList<ArrayList<Integer []>> graphList;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		graphList = new ArrayList<>();
		subTree = new long[N+1];
		distSum = new long[N+1];
		
		for (int i = 0; i < N+1; i++) {
			graphList.add(new ArrayList<>());
		}
		
		
		StringTokenizer st; 
		for (int i = 0; i < N-1; i++) {
			st = new StringTokenizer(br.readLine());
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			int weight = Integer.parseInt(st.nextToken());
			
			graphList.get(start).add(new Integer[] {end, weight});
			graphList.get(end).add(new Integer[] {start, weight});
		}
		

		dfs1(1, 1);
		dfs2(1, 1);
		
		for (int i = 1; i < N+1; i++) {
			System.out.println(distSum[i]);
			
		}
	}
	
	static void dfs1(int current, int parent) {
		subTree[current] = 1;
		
		for(Integer[] arr : graphList.get(current)) {
			int child = arr[0];
			int weight = arr[1];
			
			if (child != parent) {
				dfs1(child, current);
				
				distSum[current] += distSum[child] + subTree[child] * weight;
				subTree[current] += subTree[child];
			}
		}
	}
	
	static void dfs2(int current, int parent) {
		
		for(Integer[] arr : graphList.get(current)) {
			int child = arr[0];
			int weight = arr[1];
			
			if (child != parent) {
				distSum[child] = distSum[current] + (N - subTree[child] * 2) * weight;
				
				dfs2(child, current);
			}
		}
	}
}
