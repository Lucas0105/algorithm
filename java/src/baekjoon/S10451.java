package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class S10451 {
    static int T, N;
    static int[] arr = new int[1001];
    static int[] visited = new int[1001];
    static int result;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        T = Integer.parseInt(br.readLine());
        for(int i = 0; i < T; i++){
            N = Integer.parseInt(br.readLine());
            String[] inputData = br.readLine().split(" ");
            for(int j = 0; j < inputData.length; j++) {
                visited[j+1] = 0;
                arr[j+1] = Integer.parseInt(inputData[j]);
            }
            result = 0;
            searchCicle();

            System.out.println(result);
        }

    }

    public static void searchCicle () {
        for(int i = 1; i <= N; i++) {
            if(visited[i] == 0){
                result+=1;
                visited[i] = result;
                recursionSearch(i);
            }
        }
    }

    public static void recursionSearch(int child){
        while(child != arr[child] ){
            int parent = arr[child];
            if(visited[parent] != 0)
                break;
            visited[parent] = result;
            recursionSearch(parent);
        }
    }
}
