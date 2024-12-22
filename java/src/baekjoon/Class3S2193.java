package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class3S2193 {
    static int N;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());

        long lastNum1 = 1;
        long lastNum0 = 0;
        long prevTot = 1;

        for(int i = 2; i <= N; i++){
            lastNum1 = lastNum0;
            lastNum0 = prevTot;

            prevTot = lastNum0 + lastNum1;
        }

        System.out.println(prevTot);
    }
}
