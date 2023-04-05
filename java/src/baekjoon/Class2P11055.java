package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2P11055 {

	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		String data[] = br.readLine().split(" ");
		int result = 0;
		int [] numbers = new int [N];
		int [] dp = new int [N];
		
		for (int i = 0; i < N; i++) {
			numbers[i] = Integer.parseInt(data[i]);
		}
		
		dp[0] = numbers[0];
		
		for (int i = 1; i < N; i++) {
			for (int j = 0; j < i; j ++) {
				if (numbers[i] > numbers[j]) {
					if (dp[i] < dp[j]) {
						dp[i] = dp[j];
					}
				}
				
			}
			dp[i] += numbers[i];
		}	
		
		
		for (int num : dp) {
			if (result < num) result = num;
		}
		
		System.out.println(result);
	}

}
