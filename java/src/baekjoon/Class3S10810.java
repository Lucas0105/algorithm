package baekjoon;

import java.util.Scanner;

public class Class3S10810 {
    
  public static void main(String args[]) {
    int[] numArr = new int[101];
    for(int i = 0; i < 101; i++){
        numArr[i] = 0;
    }
    Scanner sc = new Scanner(System.in);
    
    int N, M;
    N = sc.nextInt();
    M = sc.nextInt();
    
    for(int i = 0; i < M; i++) {
        int a, b, c;
        a = sc.nextInt();
        b = sc.nextInt();
        c = sc.nextInt();
        
        for(int j = a; j <= b; j++) {
            numArr[j] = c;
        }
    }
    
    for(int i = 1; i <= N; i++){
        System.out.print(numArr[i] + " ");
    }
  }
}
