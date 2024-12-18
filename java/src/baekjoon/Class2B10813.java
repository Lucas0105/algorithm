package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class2B10813 {
    static int N, M;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputData = br.readLine().split(" ");

        int[] dataArr = new int[101];

        N = Integer.parseInt(inputData[0]);
        M = Integer.parseInt(inputData[1]);

        for(int i = 1; i <= N; i++){
            dataArr[i] = i;
        }

        for(int i = 0 ; i < M; i++) {
            String[] ab = br.readLine().split(" ");
            int a = Integer.parseInt(ab[0]);
            int b = Integer.parseInt(ab[1]);

            int tmp = dataArr[a];
            dataArr[a] = dataArr[b];
            dataArr[b] = tmp;
        }

        for(int i = 1; i <= N; i++){
            System.out.print(dataArr[i] + " ");
        }

    }
}
