package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class3P1759 {
	static int L, C;
	static char [] alphabet;
	static char[] result;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		L = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		
		String[] input = br.readLine().split(" ");
		boolean[] inputArr = new boolean[27];
		
		alphabet = new char[C];
		result = new char[L];
		
		for (int i = 0; i < input.length; i++) {
			inputArr[input[i].charAt(0) - 'a'] = true;
		}
		
		int idx = 0;
		for (int i = 0; i < 27; i++) {
			if (inputArr[i]) {
				alphabet[idx] = (char)(i+'a');
				idx++;
			}
		}
		
		nCr(0, 0);
	}

	static void nCr(int start, int depth) {
		if (depth == L) {

			int ja = 0;
			int mo = 0;
			
			for (int i = 0; i < L; i++) {
				char target = result[i];
				if (target == 'a' || target == 'e' || target == 'i' || target == 'o' || target =='u') {
					mo++;
				} else {
					ja++;
				}
			}
			if (mo >= 1 && ja >= 2) {
				for (int i = 0; i < L; i++) {
					System.out.print(result[i]);
				}
				System.out.println();
			}
			
			return;
		}
		
		for (int i = start; i < C; i++) {
			result[depth] = alphabet[i];
			nCr(i+1, depth+1);
		}
		
	}
}
