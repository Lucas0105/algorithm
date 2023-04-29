package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Class2P2583 {
	static int M, N, K;
	static boolean [][] paper;
	static int [][] delta = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		M = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		paper = new boolean [M][N];
		List<Integer> resultArr = new ArrayList<Integer>();
		
		for (int i = 0; i < K; i++) {
			st = new StringTokenizer(br.readLine());
			int x1 = Integer.parseInt(st.nextToken());
			int y1 = Integer.parseInt(st.nextToken());
			int x2 = Integer.parseInt(st.nextToken());
			int y2 = Integer.parseInt(st.nextToken());
			for (int x = x1; x < x2; x++) {
				for (int y = y1; y < y2; y++) {
					paper[y][x] = true;
				}
			}
		}
		
		for (int i = 0 ; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (!paper[i][j]) {
					resultArr.add(bfs(i, j));
				}
			}
		}
		
		Collections.sort(resultArr);
		
		System.out.println(resultArr.size());
		for (int ans : resultArr) {
			System.out.printf("%d ", ans);
		}
	}
	
	static int bfs(int x, int y) {
		int tmp = 1;
		paper[x][y] = true;
		
		Queue<Integer []> queue = new LinkedList<Integer[]>();
		queue.offer(new Integer[] {x, y} );
		
		while (!queue.isEmpty()) {
			Integer[] cur_node = queue.poll();
			int cur_x = cur_node[0];
			int cur_y = cur_node[1];
			
			for (int[] d : delta) {
				int n_x = cur_x + d[0];
				int n_y = cur_y + d[1];
				
				
				if((n_x >= 0 && n_x < M) && (n_y >= 0 && n_y < N)) {
					if (!paper[n_x][n_y]) {
						tmp ++;
						paper[n_x][n_y] = true;
						queue.offer(new Integer[] {n_x, n_y});
					}
				}
			}
			
		}
		
		return tmp;
	}

}
