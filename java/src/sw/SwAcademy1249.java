package sw;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class SwAcademy1249 {
	static int T;
	static int N;
	static int map[][];
	static int dp[][];
	static int INF = 2147483647;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		T = Integer.parseInt(br.readLine());
		
		for (int t = 0; t < T; t++) {
			N = Integer.parseInt(br.readLine());
			map = new int[N][N];
			dp = new int[N][N];
			
			for (int i = 0; i < N; i++) {
				String data = br.readLine();
				for (int j = 0; j < N; j++) {
					map[i][j] = data.charAt(j) - '0';
					dp[i][j] = INF;
					System.out.println(map[i][j]);
				}
			}
		}
		
	}

}
