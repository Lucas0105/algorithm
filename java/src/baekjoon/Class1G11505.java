package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class1G11505 {
    static int N, M, K;
    static long[] numArr;
    static long[] tree;
    static int div = 1000000007;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        numArr = new long[N];
        for(int i = 0; i < N; i++){
            numArr[i] = Long.parseLong(br.readLine());
        }

        int h = (int)Math.ceil(Math.log(N) / Math.log(2));
        h = (int)Math.pow(2, h+1);
        tree = new long[h];

        init(0, N - 1, 1);

        for(int i = 0; i < M + K; i++){
            int a, b, c;
            st = new StringTokenizer(br.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            c = Integer.parseInt(st.nextToken());
            b-=1;
            if(a == 1){
                update(0, N-1, 1, b, c);
            } else {
                c-=1;
                System.out.println(calc(0, N-1, 1, b, c));
            }
        }
    }

    public static void init(int start, int end, int node) {
        if(start == end){
            tree[node] = numArr[start];
            return;
        }

        int mid = (start + end) / 2;

        init(start, mid, node * 2);
        init(mid + 1, end, node * 2 + 1);
        tree[node] = (tree[node * 2] * tree[node * 2 + 1]) % div;
    }

    public static void update(int start, int end, int node, int index, long num) {
        if(start == end){
            tree[node] = num;
            return;
        }

        int mid = (start + end) / 2;
        if(start <= index && index <= mid){
            update(start, mid, node * 2, index, num);
        } else {
            update(mid + 1, end, node * 2 + 1, index, num);
        }
        tree[node] = (tree[node * 2] * tree[node * 2 + 1]) % div;
    }

    public static long calc(int start, int end, int node, int left, int right) {
        if(end < left || start >right) {
            return 1;
        }

        if(start >= left && end <= right){
            return tree[node];
        }

        int mid = (start + end) / 2;
        long leftValue = calc(start, mid, node * 2, left, right) % div;
        long rightValue = calc(mid + 1, end, node * 2 + 1, left, right) % div;

        return leftValue * rightValue % div;
    }
}
