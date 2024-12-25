package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class4G1062 {
    static int N, K, res;
    static boolean[] visited = new boolean[26];
    static String[] wordArray = new String[50];
    public static void main(String[] args)  throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        visited['a' - 'a'] = true;
        visited['n' - 'a'] = true;
        visited['t' - 'a'] = true;
        visited['c' - 'a'] = true;
        visited['i' - 'a'] = true;

        for(int i = 0; i < N; i++){
            wordArray[i] = br.readLine();
        }

        if(K-5 < 0){
            res = 0;
        } else {
            comb(0, 0, K-5);
        }

        System.out.println(res);
    }

    public static void comb(int start, int depth, int maxDepth){
        if(res == N)
            return;

        if(depth == maxDepth){
            wordCheck();
            return ;
        }

        for(int i = start; i < 26; i++) {
            if(visited[i])
                continue;

            visited[i] = true;
            comb(i+1, depth + 1, maxDepth);
            visited[i] = false;
        }
    }

    public static void wordCheck() {
        int tmpScore = N;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < wordArray[i].length(); j++){
                if(!visited[wordArray[i].charAt(j) - 'a']){
                    tmpScore -= 1;
                    break;
                }
            }
        }

        if(tmpScore > res)
            res = tmpScore;
    }
}
