package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Class2P2309 {
	static int[] person;
	static int[] result;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		person = new int[9];
		result = new int[7];
		
		for (int i = 0; i < 9; i++) {
			int p = Integer.parseInt(br.readLine());
			person[i] = p;
		}
		
		nCr(0, 0);
		
		Arrays.sort(result);
		for (int i = 0; i < 7; i++) {
			System.out.println(result[i]);
		}
	}
	
	static boolean nCr(int start, int cnt) {
		if (cnt == 7) {
			int cal = 0;
			for (int i = 0; i < 7; i++) {
				cal += result[i];
			}
			
			if (cal == 100) return true;

			return false;
		}
		
		for (int i = start; i < 9; i++) {
			result[cnt] = person[i];
			if (nCr(i+1, cnt+1)) {
				return true;
			}
		}
		return false;
	}
	
}
