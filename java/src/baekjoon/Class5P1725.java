package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class5P1725 {
    static int N;
    static long[] arr;
    static long[] tree;
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());

        arr = new long[N];
        for(int i = 0; i < N; i++){
            arr[i] = Long.parseLong(br.readLine());
        }

        int h = (int)Math.ceil(Math.log(N) / Math.log(2)) + 1;
        h = (int)Math.pow(2, h);
        tree = new long[h];

        init(0, N-1, 1);

        System.out.println(tree[1]);
    }

    public static void init(int start, int end, int node) {
        if(start == end){
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        long midV = calc(start, mid, end);
        init(start, mid, node * 2);
        init(mid + 1, end, node * 2 + 1);

        tree[node] = Math.max(tree[node * 2], tree[node * 2 + 1]);
        tree[node] = Math.max(tree[node], midV);
    }

    public static long calc(int start, int mid, int end) {
        long res = arr[mid];
        long midV = arr[mid];
        int left = mid-1;
        int right = mid + 1;
        int cnt = 2;

        while(left >= start && right <= end) {
            if(arr[left] > arr[right]){
                if(midV > arr[left]){
                    res = Math.max(res, arr[left] * cnt);
                    midV = arr[left];
                } else {
                    res = Math.max(res, midV * cnt);
                }
                left -= 1;
            } else {
                if(midV > arr[right]){
                    res = Math.max(res, arr[right] * cnt);
                    midV = arr[right];
                } else {
                    res = Math.max(res, midV * cnt);
                }
                right += 1;
            }
            cnt++;
        }

        for(; left >= start; left--) {
            if(midV > arr[left]){
                res = Math.max(res, arr[left] * cnt);
                midV = arr[left];
            } else {
                res = Math.max(res, midV * cnt);
            }
            cnt++;
        }

        for(; right <= end; right++) {
            if(midV > arr[right]){
                res = Math.max(res, arr[right] * cnt);
                midV = arr[right];
            } else {
                res = Math.max(res, midV * cnt);
            }
            cnt++;
        }

        return res;
    }
}
