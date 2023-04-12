package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2P10819 {
	static int N;
	static int[] number;
	static boolean[] visited;
	static int[] resultPerm;
	static int answer;
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		number = new int[N];
		String[] st = br.readLine().split(" ");
		visited = new boolean[N];
		resultPerm = new int[N];
		answer = 0;
		
		for (int i = 0; i < N; i++) {
			number[i] = Integer.parseInt(st[i]);
		}
		
		perm(0);
		
		System.out.println(answer);
	}
	
	static void perm(int start) {
		if (start == N) {
			for(int i = 0; i < N; i++) {
				cal(resultPerm);
			}
		}
		
		for (int i = 0; i < N; i++) {
			if (visited[i])continue;
			
			visited[i] = true;
			
			resultPerm[start] = number[i];
			perm(start + 1);
			
			visited[i] = false;
		}
	}
	
	static void cal(int[] num) {
		int result = 0;
		
		for (int i = 0; i < N - 1; i++) {
			result += Math.abs(num[i] - num[i+1]);
		}
		
		answer = Math.max(result, answer);
	}

	
}
