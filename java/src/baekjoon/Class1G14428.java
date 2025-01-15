package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Class1G14428 {
    static int N, M;
    static int[] arr;
    static int[] tree;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        arr = new int[N + 1];

        StringTokenizer st= new StringTokenizer(br.readLine());
        arr[0] = (int)2e10;
        for(int i = 1; i <= N; i++){
            arr[i]  = Integer.parseInt(st.nextToken());
        }
        int h = (int)Math.ceil(Math.log(N) / Math.log(2)) + 1;
        h = (int)Math.pow(2, h);

        tree = new int[h];

        init(1, N, 1);

        M = Integer.parseInt(br.readLine());
        for(int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            if(a == 1){
                arr[b] = c;
                update(1, N, 1, b);
            } else {
                System.out.println(query(1, N, 1, b, c));
            }

        }
    }

    public static void init(int start, int end, int node) {
        if (start == end) {
            tree[node] = start;
            return;
        }
        int mid = (start + end) / 2;
        init(start, mid, node * 2);
        init(mid + 1, end, node * 2 + 1);

        tree[node] = getMinIdx(tree[node * 2], tree[node * 2 + 1]);
    }


    public static void update(int start, int end, int node, int idx){
        if(start == end){
            tree[node] = idx;
            return;
        }

        int mid = (start + end) / 2;

        if(idx <= mid)
            update(start, mid, node * 2, idx);
        else
            update(mid + 1, end, node * 2 + 1, idx);

        tree[node] = getMinIdx(tree[node * 2], tree[node * 2 + 1]);
    }

    public static int query(int start, int end, int node, int left, int right) {
        if (start > right || end < left) {
            return 0;
        }

        if (start >= left && end <= right) {
            return tree[node];
        }
        int mid = (start + end) / 2;

        int leftV = query(start, mid, node * 2, left, right);
        int rightV = query(mid + 1, end, node * 2 + 1, left, right);

        return getMinIdx(leftV, rightV);
    }

    public static int getMinIdx(int n1, int n2) {
        if(arr[n1] < arr[n2]){
            return n1;
        } else if(arr[n1] == arr[n2]){
            return Math.min(n1, n2);
        }else {
            return n2;
        }
    }
}
