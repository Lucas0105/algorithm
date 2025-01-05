package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class3G2629 {
    static int N, Q;
    static int[] weight;
    static int[][] dp;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());

        weight = new int[N];
        int wSum = 0;
        StringTokenizer st = new StringTokenizer(br.readLine());
        for(int i = 0; i < N; i++){
            weight[i] = Integer.parseInt(st.nextToken());
            wSum += weight[i];
        }

        dp = new int[N + 1][wSum + 1];

        calc(0, 0);

        Q = Integer.parseInt(br.readLine());
        st = new StringTokenizer(br.readLine());
        for(int i = 0; i < Q; i++){
            int bead = Integer.parseInt(st.nextToken());

            if(bead > wSum || dp[N][bead] == 0){
                System.out.print("N ");
            } else if(dp[N][bead] != 0){
                System.out.print("Y ");
            }
        }
    }

    public static void calc(int idx, int num){
        if(dp[idx][num] !=0)
            return;

        dp[idx][num] = 1;

        if(idx == N){
            return;
        }

        calc(idx + 1, num + weight[idx]);
        calc(idx + 1, num);
        calc(idx + 1, Math.abs(num - weight[idx]));
    }
}
