package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2P1699 {
	static int N;
	static int dp[];
	static int maxValue;
	
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		dp = new int[N + 1];
		dp[1] = 1;
		maxValue = 100000;
		problem();
		System.out.println(dp[N]);
	}
	
	static void problem() {
		for (int i = 2; i <= N; i ++) {
			dp[i] = maxValue;
			
			for (int j = 1; j * j <= i; j++) {
				dp[i] = Math.min(dp[i], dp[i - j * j] + 1);
			}
		}
	}

}
