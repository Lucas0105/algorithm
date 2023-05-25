package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Class3P2294 {

	public static void main(String[] args) throws IOException {
		 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		 
		 StringTokenizer st = new StringTokenizer(br.readLine());
		 
		 int n = Integer.parseInt(st.nextToken());
		 int k = Integer.parseInt(st.nextToken());
		 int[] money = new int[n];
		 int[] result = new int[k+1];
		 
		 for (int i = 0; i < n; i++) {
			 money[i] = Integer.parseInt(br.readLine());
		 }
		 
		 bfs(n, k, money, result);
		 
		 int answer = result[k];
		 
		 if (answer == 0) {
			 System.out.println(-1);
		 } else {			 
			 System.out.println(result[k]);
		 }
	}
	
	static void bfs(int moneyNum, int target, int[] money, int[] result) {
		Queue<Integer> q = new LinkedList<>();
		q.add(0);
		
		while(!q.isEmpty()) {
			int number = q.poll();
			
			if (number == target) return;
						
			
			for (int i = 0; i < moneyNum; i++) {
				if (number + money[i] > target) continue;
				if (result[number + money[i]] != 0) continue;
				
				result[number + money[i]] = result[number] + 1;
				q.add(number + money[i]);
			}
		}
	}
}
