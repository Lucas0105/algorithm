package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class2S1535 {
    static int N;
    static int[] hp, sc;
    static int[][] dp;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());

        dp = new int[N + 1][101];
        hp = new int[N + 1];
        sc = new int[N + 1];
        StringTokenizer st = new StringTokenizer(br.readLine());
        StringTokenizer st2 = new StringTokenizer(br.readLine());
        for(int i = 1; i <= N; i++){
            hp[i] = Integer.parseInt(st.nextToken());
            sc[i] = Integer.parseInt(st2.nextToken());
        }

        for(int i = 1; i <= N; i++){
            int h = hp[i];
            int s = sc[i];

            for(int j = 0; j < 100; j++){
                if(j >= h){
                    dp[i][j] = Math.max(dp[i-1][j], dp[i-1][j-h] + s);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        System.out.println(dp[N][99]);
    }
}
