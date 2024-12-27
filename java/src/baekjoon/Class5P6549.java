package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Class5P6549 {
    static int N;
    static long[] bars;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        while(true){
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());

            if(N == 0)
                break;

            bars = new long[N + 1];
            for(int i = 0; i < N; i++) {
                bars[i] = Long.parseLong(st.nextToken());
            }
            bars[N] = -1;

            long res = searchMaxBar();
            System.out.println(res);
        }
    }

    public static long searchMaxBar() {
        Stack<Integer> stack = new Stack<>();
        long maxValue = 0;

        for(int i = 0; i <= N; i++) {

            while(!stack.isEmpty() && bars[stack.peek()] >= bars[i]){
                long height = bars[stack.pop()];

                int width = stack.isEmpty() ? i : i - 1 - stack.peek();
                maxValue = Math.max(maxValue, height * width);
            }

            stack.push(i);
        }

        return maxValue;
    }

}
