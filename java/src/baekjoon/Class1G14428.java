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
    static ArrayList<Integer>[] memory = new ArrayList[100001];
    static HashMap<Integer, Integer> hMap = new HashMap<>();
    static int hIdx = 0;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        arr = new int[N + 1];
        for(int i = 0; i <= 100000; i++){
            memory[i] = new ArrayList<>();
        }

        StringTokenizer st= new StringTokenizer(br.readLine());
        for(int i = 1; i <= N; i++){
            arr[i]  = Integer.parseInt(st.nextToken());
            memory[getIdx(arr[i])].add(i);
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
                memory[getIdx(arr[b])].removeIf(s-> s == b);
                memory[getIdx(c)].add(b);
                arr[b] = c;
                update(1, N, 1, b, c);
            } else {
                int value = query(1, N, 1, b, c);
                int res = (int)1e10;
                for(int j = 0; j < memory[getIdx(value)].size(); j++){
                    int tmp = memory[getIdx(value)].get(j);
                    if(tmp < b || tmp > c)
                        continue;
                    res = Math.min(res, memory[getIdx(value)].get(j));
                }

                System.out.println(res);
            }

        }
    }

    public static void init(int start, int end, int node) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        init(start, mid, node * 2);
        init(mid + 1, end, node * 2 + 1);

        tree[node] = Math.min(tree[node * 2], tree[node * 2 + 1]);
    }


    public static void update(int start, int end, int node, int idx, int diff){
        if(start == end){
            tree[node] = diff;
            return;
        }

        int mid = (start + end) / 2;

        if(idx <= mid)
            update(start, mid, node * 2, idx, diff);
        else
            update(mid + 1, end, node * 2 + 1, idx, diff);

        tree[node] = Math.min(tree[node * 2], tree[node * 2 + 1]);
    }

    public static int query(int start, int end, int node, int left, int right) {
        if (start > right || end < left) {
            return (int) 2e10;
        }

        if (start >= left && end <= right) {
            return tree[node];
        }
        int mid = (start + end) / 2;

        int leftV = query(start, mid, node * 2, left, right);
        int rightV = query(mid + 1, end, node * 2 + 1, left, right);

        return Math.min(leftV, rightV);
    }

    public static int getIdx(int v){
        if(hMap.containsKey(v))
            return hMap.get(v);
        else{
            hMap.put(v, hIdx);
            return hIdx++;
        }
    }
}
