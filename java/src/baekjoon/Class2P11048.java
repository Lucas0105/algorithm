package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Class2P11048 {
	static int N, M;
	static int[][] miro;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] data = br.readLine().split(" ");
		N = Integer.parseInt(data[0]);
		M = Integer.parseInt(data[1]);
		int [][] result = new int[N][M];
		boolean [][] visited = new boolean[N][M];
		LinkedList<Integer[]> queue = new LinkedList<>();
		int [][] dir = {{1, 0}, {0, 1}};
		
		
		miro = new int[N][M];
		StringTokenizer st;
		
		for (int i = 0; i < N; i++ ) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < M; j++) {
				miro[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		queue.add(new Integer[] {0, 0});
		result[0][0] = miro[0][0];
		
		while (!queue.isEmpty()) {
			Integer[] cur = queue.remove(0);
			
			for (int i = 0; i < 2; i++) {
				int n_x = dir[i][0] + cur[0];
				int n_y = dir[i][1] + cur[1];
				
				if (n_x == N || n_y == M) continue;
				
				if (result[n_x][n_y] < result[cur[0]][cur[1]] + miro[n_x][n_y]) {
					result[n_x][n_y] = result[cur[0]][cur[1]] + miro[n_x][n_y];
					visited[n_x][n_y] = true;
					queue.add(new Integer[] {n_x, n_y});
				}
				
				if (result[n_x][n_y] == result[cur[0]][cur[1]] + miro[n_x][n_y] && ! visited[n_x][n_y]) {
					queue.add(new Integer[] {n_x, n_y});
					visited[n_x][n_y] = true;
				}
			}
		}
		
		System.out.println(result[N-1][M-1]);
	}

}
