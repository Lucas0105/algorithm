package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class5G14728 {
    static int N, T;
    static int[] time, score;
    static int[][] dp;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());

        dp = new int[N+1][T + 1];
        time = new int[N+1];
        score = new int[N+1];

        for(int i = 1; i <= N; i++){
            st = new StringTokenizer(br.readLine());
            int a, b;
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            time[i] = a;
            score[i] = b;
        }

        for(int i = 1; i <= N; i++){
            int t = time[i];
            int s = score[i];

            for(int j = 1; j <= T; j++){
                if(j >= t){
                    dp[i][j] = Math.max(dp[i-1][j], dp[i-1][j-t] + s);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        System.out.println(dp[N][T]);
    }
}
