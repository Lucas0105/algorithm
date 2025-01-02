package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class3G7579 {
    static int N, M;
    static int[] mem;
    static int[] cost;
    static int[][] dp;
    static int ans = (int)2e10;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        mem = new int[N + 1];
        cost = new int[N + 1];

        st = new StringTokenizer(br.readLine());
        for(int i = 1; i <= N; i++){
            mem[i] = Integer.parseInt(st.nextToken());
        }

        int sumCost = 0;
        st = new StringTokenizer(br.readLine());
        for(int i = 1; i <= N; i++){
            cost[i] = Integer.parseInt(st.nextToken());
            sumCost += cost[i];
        }

        dp = new int[N+1][sumCost + 1];

        for(int i = 1; i <= N; i++) {
            int cMem = mem[i];
            int cCos = cost[i];

            for(int j = 0; j <= sumCost; j++) {
                if(cCos <= j){
                    dp[i][j] = Math.max(dp[i-1][j-cCos] + cMem, dp[i - 1][j]);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }

                if(dp[i][j] >= M){
                    ans = Math.min(ans, j);
                }
            }
        }

        System.out.println(ans);
    }
}
