package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class1G1275 {
    static int N, Q;
    static long[] arr;
    static long[] tree;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        arr = new long[N + 1];

        int h = (int)Math.ceil(Math.log(N) / Math.log(2)) + 1;
        h = (int)Math.pow(2, h);
        tree = new long[h];

        st = new StringTokenizer(br.readLine());
        for(int i = 1; i <= N; i++){
            arr[i] = Long.parseLong(st.nextToken());
        }

        init(1, N, 1);

        for(int i = 0; i < Q; i++){
            int x, y, a, b;
            st = new StringTokenizer(br.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());

            if(x > y){
              int tmp = x;
              x = y;
              y = tmp;
            }

            System.out.println(query(1, N, 1, x, y));
            update(1, N, 1, a, b);
            arr[a] = b;
        }
    }

    public static void init(int start, int end, int node){
        if(start == end){
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        init(start, mid, node * 2);
        init(mid + 1, end, node * 2 + 1);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    public static long query(int start, int end, int node, int left, int right) {
        if(start > right || end < left){
            return 0;
        }

        if(start >= left && end <= right){
            return tree[node];
        }

        int mid = (start + end) / 2;
        long leftV = query(start, mid, node * 2, left, right);
        long rightV = query(mid + 1, end, node * 2 + 1, left, right);

        return leftV + rightV;
    }

    public static void update(int start, int end, int node, int idx, long diff) {
        if(start == end){
            tree[node] = diff;
            return;
        }

        int mid = (start + end) / 2;

        if(idx <= mid){
            update(start, mid, node * 2, idx, diff);
        } else {
            update(mid + 1, end, node * 2 + 1, idx, diff);
        }

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}
