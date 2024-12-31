package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class1G10868 {
    static int N, M;
    static int[] arr;
    static int[] tree;
    static int maxV = (int)2e10;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        arr = new int[N + 1];

        for(int i = 1; i <= N; i++){
            arr[i] = Integer.parseInt(br.readLine());
        }

        int h = (int)Math.ceil(Math.log(N) / Math.log(2));
        h = (int)Math.pow(2, h+1);
        tree = new int[h];
        init(1, N, 1);

        for(int i = 0; i < M; i++){
            int a, b;
            st = new StringTokenizer(br.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());

            int res = query(1, N, 1, a, b);

            System.out.println(res);
        }
    }

    public static void init(int start, int end, int node){
        if(start == end){
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        init(start, mid, node * 2);
        init(mid+1, end, node * 2+1);
        tree[node] = Math.min(tree[node * 2], tree[node * 2 + 1]);
    }

    public static int query(int start, int end, int node, int left, int right){
        if(start > right || end < left){
            return maxV;
        }

        if(start >= left && end <= right){
            return tree[node];
        }

        int mid = (start + end) / 2;
        int leftV = query(start, mid, node * 2, left, right);
        int rightV = query(mid+1, end, node * 2 + 1, left, right);

        return Math.min(leftV, rightV);
    }
}
