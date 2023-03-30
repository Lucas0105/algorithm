package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2P11051 {
	static int dp[][];
	static int p;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String [] data = br.readLine().split(" ");
		
		int N = Integer.parseInt(data[0]);
		int K = Integer.parseInt(data[1]);
		p = 10007;
		dp = new int[N+1][K+1]; 
		
		if (N - K < K) {
			K = N - K;
		}
		
		System.out.println(search(N, K));

	}
	
	static int search(int N, int K) {
		if (dp[N][K] != 0) {
			return dp[N][K];
		}
		
		
		if (N == K || K == 0) {
			dp[N][K] = 1;
			return 1;
		}
		
		dp[N][K] = (search(N-1, K - 1) + search(N-1, K)) % p;
		return dp[N][K];
	}
}
