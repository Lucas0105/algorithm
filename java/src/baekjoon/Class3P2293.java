package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class3P2293 {

	public static void main(String[] args) throws IOException {
		 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		 
		 StringTokenizer st = new StringTokenizer(br.readLine());
		 
		 int n = Integer.parseInt(st.nextToken());
		 int k = Integer.parseInt(st.nextToken());
		 int[] money = new int[n];
		 int[] result = new int[k+1];
		 result[0] = 1;
		 
		 for (int i = 0; i < n; i++) {
			 money[i] = Integer.parseInt(br.readLine());
		 }
		 
		 for (int money_idx = 0; money_idx < n; money_idx++) {
			 for (int m = money[money_idx]; m <= k; m++) {
				 result[m] += result[m - money[money_idx]]; 
			 }
		 }
		 System.out.println(result[k]);
	}

}
