package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2P11057 {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int[][] dp = new int[N][10];
		int result = 0;
		int remain = 10007;
		
		for (int i = 0; i < 10; i ++) {
			dp[0][i] = 1;
		}
		
		for (int step = 1; step < N; step++) {
			for (int stairs = 0; stairs < 10; stairs++) {
				for (int pStairs = stairs; pStairs < 10; pStairs++) {
					dp[step][stairs] += dp[step-1][pStairs] % remain;
				}
				dp[step][stairs] %= remain;
			}
		}
		
		for (int i = 0; i < 10; i++) result += dp[N-1][i] % remain;
		
		System.out.println(result % remain);

	}

}
