package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class3P2225 {
	static int DIVIDE = 1000000000;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());
		
		long [][] dp = new long [K+1][N+1];
		
		for (int i = 0; i <= N; i++) {
			dp[1][i] = 1L;
		}
		
		for (int k = 2; k <= K; k++) {
			for (int n = 0; n <= N; n++) {
				for (int target = 0; target <= n; target++) {
					dp[k][n] += dp[k-1][target] % DIVIDE;
				}
				dp[k][n] %= DIVIDE;
			}
		}
		
		System.out.println(dp[K][N]);
	}

}
