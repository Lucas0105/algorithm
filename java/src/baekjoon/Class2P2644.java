package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;

public class Class2P2644 {
	static int n, x, y, m;
	static ArrayList<LinkedList<Integer>> graph;
	static int answer;
	
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		n = Integer.parseInt(br.readLine());
		String [] target = br.readLine().split(" ");
		x = Integer.parseInt(target[0]);
		y = Integer.parseInt(target[1]);
		m = Integer.parseInt(br.readLine());
		graph = new ArrayList<LinkedList<Integer>>();
		boolean [] visited = new boolean[n+1];
		
		for(int i = 0; i <= n; i++)graph.add(new LinkedList<>());
		
		
		answer = -1;
		
		for (int i = 0; i < m; i++) {
			String [] n_target = br.readLine().split(" ");
			int n_x = Integer.parseInt(n_target[0]);
			int n_y = Integer.parseInt(n_target[1]);
			
			graph.get(n_x).add(n_y);
			graph.get(n_y).add(n_x);
		}
		
		dfs(visited, x, y, 1);
		
		System.out.println(answer);
		
	}
	
	static void dfs(boolean[] visited, int start, int end, int cnt) {
		LinkedList<Integer> curNode = graph.get(start);
		
		for (int i = 0; i < curNode.size(); i++) {
			int curNum = curNode.get(i);
			
			if (visited[curNum]) continue;			
			
			visited[curNum] = true;
			
			if (curNum == end) answer = cnt;
			if (answer != -1) return;
			
			dfs(visited, curNum, end, cnt + 1);
		}
	}
}
