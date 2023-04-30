package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class2P1946 {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		StringTokenizer st;
		
		for (int testCase = 0; testCase < T; testCase++) {
			int N = Integer.parseInt(br.readLine());
			int result = 1;
			int grade[] = new int[N+1];
			
			for (int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				grade[x] = y;
			}
			// 이전의 값 중 가장 작은 값만 비교
			// 가장 작은 것보다 작으면 회사에 들어 갈 수 있음
			int minimum = grade[1];

			for (int i = 2; i <= N; i++) {
				if (grade[i] < minimum) {
					result++;
					minimum = grade[i];
				}
				
			}
			
			System.out.println(result);
		}
	}

}
