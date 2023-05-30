package softeer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class 성적평균 {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int N = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());
		
		int[] subject = new int[N+1];
		
		String[] input = br.readLine().split(" ");
		
		for (int i = 0; i < N; i++) {
			subject[i+1] = Integer.parseInt(input[i]);
		}
		
		for (int i = 2; i <= N; i++) {
			subject[i] += subject[i-1];
		}
		
		for (int i = 0; i <K; i++) {
			input = br.readLine().split(" ");
			int a = Integer.parseInt(input[0]);
			int b = Integer.parseInt(input[1]);
			
			double result = (subject[b] - subject[a-1]) / (double)(b - a + 1);
			result *= 100;
			result = Math.round(result) / 100.0;
			
			System.out.printf("%.2f\n", result);
		}
		
	}

}
