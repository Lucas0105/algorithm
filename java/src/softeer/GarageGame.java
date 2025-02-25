package softeer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class GarageGame {
    public static class Pair {
        int row, col;
        Pair(int r, int c){
            row = r;
            col = c;
        }
    }
    static int N;
    static int[][] garage;
    static int[][] box;
    static int[] pointers;
    static int res = 0;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        garage = new int[N * 3][N * 3];
        box = new int[N][N];
        pointers = new int[N];

        for(int i = 0; i < N * 3; i++){
            StringTokenizer st = new StringTokenizer(br.readLine());

            for(int j = 0; j < N * 3; j++){
                garage[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        for(int i = 0; i < N; i++){
            System.arraycopy(garage[i], 0, box[i], 0, N);
        }

        // 재귀 모든 경우 확인
        // depth
        recur(1, 0, pointers, box);

    }

    public static int bfs(int sRow, int sCol, boolean[][] visited, int[][] box){
        Queue<Pair> q = new LinkedList<Pair>();
        q.add(new Pair(sRow, sCol));

        int minR = 0, minC = 0, maxR = sRow, maxC = sCol;
        int color = box[sRow][sCol];

        while(!q.isEmpty()){
            Pair node = q.poll();
            int r = node.row;
            int c = node.col;

            if(visited[r][c])
                continue;

            visited[r][c] = true;

 
        }

        return 0;
    }

    public static void dropCar(int[][] box, int[] pointers){

    }

    public static void recur(int depth, int score, int[] pointers, int[][] box) {

        res = Math.max(score, res);
        // 4번 실행되면 종료
        if(depth == 4)
            return;

        boolean[][] visited = new boolean[N][N];
        // 시작 위치
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++){
                // 방문 했으면 skip
                if(visited[i][j])
                    continue;

                int[] newPointers = new int[N];
                System.arraycopy(newPointers, 0, pointers, 0, N);

                int[][] newBox = new int[N][N];
                for(int c = 0; c < N; c++){
                    System.arraycopy(newBox[i],0,box[i],0, N);
                }

                // 같은 색상 자동차 삭제
                int plus = bfs(i, j, visited, newBox);

                dropCar(newBox, newPointers);

                // 다음 차고지 진행
                recur(depth + 1, score + plus, newPointers, newBox);
            }
        }


    }
}
