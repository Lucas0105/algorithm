package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Class5P6549_DivideAndConquer {
    static int N;
    static long res;
    static long[] bars;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        while (true) {
            long res = 0;
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());

            if (N == 0)
                break;

            bars = new long[N + 1];
            for (int i = 0; i < N; i++) {
                bars[i] = Long.parseLong(st.nextToken());
            }

            System.out.println(divideAndConquer(0, N-1));
        }
    }
    public static long divideAndConquer(int start, int end) {

        if(start >= end) {
            return bars[start];
        }

        int mid = (start + end) / 2;
        long midV = findMaxV(start, mid, end);

        long left = divideAndConquer(start, mid - 1);
        long right = divideAndConquer(mid + 1, end);

        return Math.max(Math.max(left, right), midV);
    }

    public static long findMaxV(int start, int mid, int end) {
        long maxV = bars[mid];
        int stIdx = mid - 1;
        int endIdx = mid + 1;
        int width = 2;
        long height = bars[mid];

        while (stIdx >= start && endIdx <= end) {
            if(bars[stIdx] > bars[endIdx]) {
                height = Math.min(height, bars[stIdx]);
                maxV = Math.max(maxV, height * width);
                stIdx--;
            } else {
                height = Math.min(height, bars[endIdx]);
                maxV = Math.max(maxV, height * width);
                endIdx++;
            }

            width++;
        }

        for(; stIdx >= start; stIdx--) {
            height = Math.min(height, bars[stIdx]);
            maxV = Math.max(maxV, height * width);
            width++;
        }

        for(; endIdx <= end; endIdx++) {
            height = Math.min(height, bars[endIdx]);
            maxV = Math.max(maxV, height * width);
            width++;
        }
        return maxV;
    }
}
