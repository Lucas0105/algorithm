package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class1G14438 {
    static int N, M;
    static int[] arr;
    static int[] tree;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        StringTokenizer st = new StringTokenizer(br.readLine());

        int h = (int)Math.ceil(Math.log(N) / Math.log(2)) + 1;
        h = (int)Math.pow(2, h);
        tree = new int[h];
        arr = new int[N + 1];


        for(int i = 1; i <= N; i++){
            arr[i] = Integer.parseInt(st.nextToken());
        }

        M = Integer.parseInt(br.readLine());

        init(1, N, 1);
        for(int i = 0; i < M; i++){
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            if(a == 1){
                update(1, N, 1, b, c);
            } else if(a == 2){
                System.out.println(query(1, N, 1, b, c));
            }
        }
    }
    public static void init(int start, int end, int node) {
        if(start == end){
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        init(start, mid, node * 2);
        init(mid + 1, end, node * 2 + 1);
        tree[node] = Math.min(tree[node * 2], tree[node * 2 + 1]);
    }

    public static void update(int start, int end, int node, int idx, int diff) {
        if (start == end){
            tree[node] = diff;
            return;
        }
        int mid = (start + end) / 2;

        if(idx <= mid) {
            update(start, mid, node * 2, idx, diff);
        } else {
            update(mid + 1, end, node * 2 + 1, idx, diff);
        }
        tree[node] = Math.min(tree[node * 2], tree[node * 2 + 1]);
    }

    public static int query(int start, int end, int node, int left, int right) {
        if(start > right || end < left){
            return (int)2e10;
        }
        int mid = (start + end) / 2;

        if(start >= left && end <= right)
            return tree[node];

        int leftV = query(start, mid, node * 2, left, right);
        int rightV = query(mid + 1, end, node * 2 + 1, left, right);

        return Math.min(leftV, rightV);
    }
}
