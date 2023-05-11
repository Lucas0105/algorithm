package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Class3P1011 {
	static ArrayList<Integer> distance_arr;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		StringTokenizer st;
		distance_arr = new ArrayList<Integer>();
		

		for (int t = 0; t < T; t++) {
			int result = 0;
			long curNum = 0;
			
			st = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			int distance = y - x;
						
			while(curNum < distance) {
				result += 1;
				curNum += (int) Math.ceil(result / 2.0);
			}
			
			System.out.println(result);
		}
	}

}
