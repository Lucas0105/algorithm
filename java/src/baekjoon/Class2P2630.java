package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2P2630 {
	static char [][]paper;
	static int [] blackAndWhite;
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		paper = new char[N][N];
		blackAndWhite = new int[2];
		
		for (int i = 0; i < N; i++) {
			String [] data = br.readLine().split(" ");
			for (int j = 0; j < N; j++) {
				paper[i][j] = data[j].charAt(0);
			}
		}
		
		search(0, 0, N);
		
		System.out.println(blackAndWhite[0]);
		System.out.println(blackAndWhite[1]);
	}
	
	static void search(int s_r, int s_c, int N) {

		char initV = paper[s_r][s_c];
		
		for (int i = s_r; i < s_r + N; i++) {
			for (int j = s_c; j < s_c + N; j++) {
				if (initV != paper[i][j]) {
					search(s_r, s_c, N / 2);
					search(s_r, s_c + (N / 2), N / 2);
					search(s_r  + (N / 2), s_c, N / 2);
					search(s_r  + (N / 2), s_c + (N / 2), N / 2);
					return;
				}				
			}
		}
		
		
		blackAndWhite[initV - '0'] += 1;
		
		
	}

}
