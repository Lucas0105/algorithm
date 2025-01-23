package softeer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class 연탄의크기 {
    static int N;
    static int[] arr;
    public static void main(String[] args)  throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        arr = new int[N];
        StringTokenizer st = new StringTokenizer(br.readLine());

        int res = 0;
        for(int i = 0; i < N; i++){
            arr[i] = Integer.parseInt(st.nextToken());
        }

        for(int i = 2; i <= 100; i++){
            int tmp = 0;
            for(int j = 0; j < N; j++) {
                int targetNum = arr[j];

                if (i <= targetNum && targetNum % i == 0) {
                    tmp += 1;
                }
            }
            res = Math.max(res, tmp);
        }

        System.out.println(res);
    }
}
