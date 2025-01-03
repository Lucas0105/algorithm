package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class5G9084 {
    static int T, N, M;
    static int[] moneyArr = new int[21];
    static int[] dp;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        T = Integer.parseInt(br.readLine());

        for(int tCase = 0; tCase < T; tCase++){
            N = Integer.parseInt(br.readLine());
            StringTokenizer st = new StringTokenizer(br.readLine());

            for(int i = 1; i <= N; i++){
                moneyArr[i] = Integer.parseInt(st.nextToken());
            }
            M = Integer.parseInt(br.readLine());

            dp = new int[M + 1];
            dp[0] = 1;
            for(int mIdx = 1; mIdx <= N; mIdx++) {
                int money = moneyArr[mIdx];
                for(int j = money; j <= M; j++){
                    dp[j] += dp[j-money];
                }
            }

            System.out.println(dp[M]);
        }


    }
}
