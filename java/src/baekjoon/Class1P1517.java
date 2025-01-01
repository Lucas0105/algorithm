package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Class1P1517 {
    static int N;
    static int[] elements;
    static HashMap<Integer, LinkedList<Integer>> indexPos;
    static long[] tree;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        int h = (int)Math.ceil(Math.log(N) / Math.log(2)) + 1;
        h = (int)Math.pow(2, h);
        tree = new long[h];

        elements = new int[N];
        indexPos = new HashMap<>();
        st = new StringTokenizer(br.readLine());
        for(int i = 0; i < N; i++) {
            elements[i] = Integer.parseInt(st.nextToken());
            indexPos.computeIfAbsent(elements[i], k -> new LinkedList<Integer>()).add(i);
        }

        int[] sortEle = elements.clone();
        Arrays.sort(sortEle);

        long res = 0;
        for(int i = 0; i < N; i++) {
            int idx = indexPos.get(sortEle[i]).pop();
            res += query(0, N - 1, 1, idx + 1, N -1);
            update(0, N - 1, 1, idx);
        }
        System.out.println(res);
    }

    public static long query(int start, int end, int node, int left, int right) {
        if(start > right || end <left){
            return 0;
        }

        if(left <= start && right >= end){
            return tree[node];
        }

        int mid = (start + end) / 2;

        long leftV = query(start, mid, node * 2, left, right);
        long rightV = query(mid + 1, end, node * 2 + 1, left, right);

        return leftV + rightV;
    }

    public static void update(int start, int end, int node, int idx){
        if(start == end){
            tree[node] = 1;
            return;
        }

        int mid = (start + end) / 2;

        if(idx <= mid){
            update(start, mid, node * 2, idx);
        } else {
            update(mid + 1, end, node * 2 + 1, idx);
        }

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}
