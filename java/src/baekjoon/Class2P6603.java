package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2P6603 {
	static int chk[];

	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		while (true) {
			String [] data = br.readLine().split(" ");
			if (data[0].equals("0")) break;
			
			int k = Integer.parseInt(data[0]);
			
			int [] lotto = new int[k];
			chk = new int[6];
			for (int i = 0; i < k; i++) {
				lotto[i] = Integer.parseInt(data[i+1]);
			}
			
			search(lotto, 0, 0, k);
			System.out.println();
		}
	}
	
	static void search(int[] lotto, int s, int cnt, int e) {
		if (cnt == 6) {
			for (int i = 0; i < 6; i++){
				System.out.print(chk[i]+" ");
			}
			System.out.println();
		}
		else {
			for (int i = s; i < e; i++) {
				if (6 - cnt > e - i) return;
				chk[cnt] = lotto[i];
				search(lotto, i + 1, cnt + 1, e);
			}
		}

	}
}


