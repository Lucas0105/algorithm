package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class5P6549 {
    static int N;
    static int[] bars;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        while(true){
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());

            if(N == 0)
                break;

            bars = new int[N];
            for(int i = 0; i < N; i++) {
                bars[i] = Integer.parseInt(st.nextToken());
            }

            
        }
    }
}
