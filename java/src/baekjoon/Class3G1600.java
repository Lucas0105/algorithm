package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Class3G1600 {
    public static class Monkey {
        int row, col;
        int horseMoving;
        int moveCnt;

        public Monkey(int row, int col, int horsMoving, int moveCnt){
            this.row = row;
            this.col = col;
            this.horseMoving = horsMoving;
            this.moveCnt = moveCnt;
        }
    }

    static int K, W, H;
    static int[] dr = new int[]{-1, 0, 1, 0};
    static int[] dc = new int[]{0, 1, 0, -1};
    static int[] hr = new int[]{-1, -2, -2, -1, 1, 2, 2, 1};
    static int[] hc = new int[]{-2, -1, 1, 2, 2, 1, -1, -2};

    static int[][] chessboard = new int[200][200];
    static Queue<Monkey> queue = new LinkedList<>();
    static Monkey[][] visited = new Monkey[200][200];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        K = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(br.readLine());
        W = Integer.parseInt(st.nextToken());
        H = Integer.parseInt(st.nextToken());

        for(int i = 0; i < H; i++){
            st = new StringTokenizer(br.readLine());
            int j = 0;
            while(st.hasMoreTokens()){
                chessboard[i][j] = Integer.parseInt(st.nextToken());
                j++;
            }
        }

        queue.add(new Monkey(0, 0, K, 0));
        Monkey res = bfsSearch();
        if(res == null)
            System.out.println(-1);
        else
            System.out.println(res.moveCnt);
    }

    public static Monkey bfsSearch() {
        while(!queue.isEmpty()) {
            Monkey monkey = queue.poll();

            if(monkey.row == H - 1 && monkey.col == W - 1)
                return monkey;

            if(visited[monkey.row][monkey.col] != null){
                if(visited[monkey.row][monkey.col].horseMoving >= monkey.horseMoving){
                    continue;
                }
            }

            visited[monkey.row][monkey.col] = monkey;

            for(int i = 0; i < 4; i++){
                Monkey newMonkey = isValid(monkey, dr[i], dc[i], 0);
                if(newMonkey == null)
                    continue;
                queue.add(newMonkey);
            }

            for(int i = 0; i < 8; i++){
                Monkey newMonkey = isValid(monkey, hr[i], hc[i], -1);
                if(newMonkey == null)
                    continue;
                queue.add(newMonkey);
            }
        }

        return null;
    }

    public static Monkey isValid(Monkey monkey, int row, int col, int horseMoving) {
        Monkey newMonkey = new Monkey(
                monkey.row + row,
                monkey.col + col,
                monkey.horseMoving + horseMoving,
                monkey.moveCnt + 1
        );

        if(newMonkey.horseMoving < 0)
            return null;

        if(newMonkey.row <= -1 || newMonkey.col <= -1 ||
                newMonkey.row >= H || newMonkey.col >= W){
                return null;
        }

        if(chessboard[newMonkey.row][newMonkey.col] == 1){
            return null;
        }

        return newMonkey;
    }
}
