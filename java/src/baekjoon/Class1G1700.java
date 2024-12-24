package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.function.Consumer;

public class Class1G1700 {
    static int N, K, res;
    static int[] arr = new int[100];
    static Set<Integer> multitab = new HashSet<>();
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());

        int idx = 0;
        while(st.hasMoreTokens()){
            arr[idx] = Integer.parseInt(st.nextToken());
            idx += 1;
        }

        idx = 0;
        while(multitab.size() < N ){
            multitab.add(arr[idx++]);
        }

        for(int i = idx; i < K; i++){
            // 이미 사용 중이면 Pass
            if(multitab.contains(arr[i])){
                continue;
            }

            // 사용 중 X => 하나의 전기용품 제거
            Iterator<Integer> iterTab = multitab.iterator();
            int maxPos = 0;
            int maxNum = 0;

            while(iterTab.hasNext()){
                int num = iterTab.next();
                boolean isMatch = false;
                for(int j = i; j <K; j++){
                    if(num == arr[j]){
                        if(maxPos < j){
                            maxPos = j;
                            maxNum = arr[j];
                            isMatch = true;
                        }
                        break;
                    }
                }

                if(!isMatch){
                    maxNum = num;
                    break;
                }
            }

            multitab.remove(maxNum);

            multitab.add(arr[i]);
            res += 1;
        }

        System.out.println(res);
    }
}
