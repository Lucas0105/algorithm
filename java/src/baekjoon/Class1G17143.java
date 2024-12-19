package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class1G17143 {
    static int R, C, M, res;
    static Shark[][] sharkTable = new Shark[101][101];
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] a = br.readLine().split(" ");
        R = Integer.parseInt(a[0]);C = Integer.parseInt(a[0]);M = Integer.parseInt(a[0]);

        for(int i = 0; i < M; i++) {
            String[] b = br.readLine().split(" ");
            int r = Integer.parseInt(b[0]);int c = Integer.parseInt(b[1]);
            int s = Integer.parseInt(b[2]);int d = Integer.parseInt(b[3]);
            int z = Integer.parseInt(b[4]);
            Shark newShark = new Shark(s, d, z);
            sharkTable[r][c] = newShark;
        }

        // 0에서 이동했다는 가정 1부터 시작
        for(int pos = 1; pos <= C; pos++){
            res += catchShark(pos);
            moveShark();
        }

        System.out.println(res);
    }

    public static int catchShark(int pos) {
        for(int row = 1; row <= R; row++ ){
            if (sharkTable[row][pos] != null ){
                int w = sharkTable[row][pos].z;
                sharkTable[row][pos] = null;
                return w;
            }
        }
        return 0;
    }

    public static void moveShark() {

    }
    
    public static class Shark{
        int s, d, z;

        public Shark(int s, int d, int z){
            this.s = s;this.d = d;this.z = z;
        }
    }
}
