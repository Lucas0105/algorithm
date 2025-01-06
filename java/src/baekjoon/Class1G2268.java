package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class1G2268 {
    static int N, M;
    static long[] tree;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        int h = (int)Math.ceil(Math.log(N) / Math.log(2)) + 1;
        h = (int)Math.pow(2, h);
        tree = new long[h];

        for(int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            if(a == 0){
                if(b > c){
                    int tmp = c;
                    c = b;
                    b = tmp;
                }
                System.out.println(query(1, N, 1, b, c));
            } else if(a == 1){
                update(1, N, 1, b, c);
            }

        }

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

    public static void update(int start, int end, int node, int idx, int diff) {
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
