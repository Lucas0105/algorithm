package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class1G2357 {
    static int N, M;
    static int[] nArr = new int[100001];
    static int[] maxTree;
    static int[] minTree;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        for(int i = 0; i < N; i++) {
            nArr[i] = Integer.parseInt(br.readLine());
        }

        int h = (int)Math.ceil(Math.log(N) / Math.log(2));
        h = (int)Math.pow(2, h + 1);
        maxTree = new int[h];
        minTree = new int[h];

        init(maxTree, 0, N - 1, 1, 1);
        init(minTree, 0, N - 1, 1, -1);

        for(int i = 0; i < M; i++){
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1;
            int b = Integer.parseInt(st.nextToken()) - 1;

            int maxV = getMax(maxTree, 0, N - 1, 1, a, b, 1);
            int minV = getMax(minTree, 0, N - 1, 1, a, b, -1);

            System.out.println(minV * - 1 + " " + maxV);
        }
    }

    public static int init (int[] tree, int start, int end, int node, int flag) {
        if(start == end){
            return tree[node] = nArr[start] * flag;
        }

        int mid = (start + end) / 2;

        return tree[node] = Math.max(init(tree, start, mid, node * 2, flag), init(tree, mid + 1, end, node * 2 + 1, flag));
    }

    public static int getMax(int[] tree, int start, int end, int node, int left, int right, int flag) {
        if(start > right || end < left ){
            if(flag == 1)
                return 0;
            else
                return -1000000000;
        }

        if(left <= start && right >= end){
            return tree[node];
        }

        int mid = (start + end) / 2;

        return Math.max(getMax(tree, start, mid, node * 2, left, right, flag), getMax(tree, mid + 1, end, node * 2 + 1, left, right, flag));
    }
}
