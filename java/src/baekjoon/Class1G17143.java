package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Class1G17143 {
    static int R, C, M, res;
    static Shark[][] sharkTable = new Shark[101][101];
    static int[] dr = new int[] {-1, 0, 1, 0};
    static int[] dc = new int[] {0, 1, 0, -1};
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] a = br.readLine().split(" ");
        R = Integer.parseInt(a[0]);C = Integer.parseInt(a[1]);M = Integer.parseInt(a[2]);

        for(int i = 0; i < M; i++) {
            String[] b = br.readLine().split(" ");
            int r = Integer.parseInt(b[0]);int c = Integer.parseInt(b[1]);
            int s = Integer.parseInt(b[2]);int d = Integer.parseInt(b[3]);
            int z = Integer.parseInt(b[4]);
            d-=1;
            if (d == 1)
                d = 2;
            else if(d == 2)
                d = 1;

            Shark newShark = new Shark(r, c, s, d, z);
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
                M -= 1;
                return w;
            }
        }
        return 0;
    }

    public static void moveShark() {
        Shark[] sharks = new Shark[M];
        int idx = 0;
        for(int row = 1; row <= R; row++){
            for(int col = 1; col <=C; col++){
                if(sharkTable[row][col] != null){
                    sharks[idx] = sharkTable[row][col];
                    idx +=1 ;
                }
            }
        }
        sharkTable = new Shark[R+1][C+1];

        int removeShark = 0;
        for(int i = 0; i < M; i++) {
            int moveR = sharks[i].s % ((R-1) * 2);
            int moveC = sharks[i].s % ((C-1) * 2);

            for(int j = 1; j <= moveR; j++){
                if(dr[sharks[i].d] == 0)
                    break;
                sharks[i].r += dr[sharks[i].d];

                if(sharks[i].r == 0){
                    sharks[i].r = 2;
                    sharks[i].d = (sharks[i].d + 2) % 4;
                } else if(sharks[i].r == R + 1){
                    sharks[i].r = R-1;
                    sharks[i].d = (sharks[i].d + 2) % 4;
                }
            }

            for(int j = 1; j <= moveC; j++){
                if(dc[sharks[i].d] == 0)
                    break;
                sharks[i].c += dc[sharks[i].d];
                if(sharks[i].c == 0 ){
                    sharks[i].c = 2;
                    sharks[i].d = (sharks[i].d + 2) % 4;
                } else if(sharks[i].c == C + 1) {
                    sharks[i].c = C -1;
                    sharks[i].d = (sharks[i].d + 2) % 4;
                }

            }

            if(sharkTable[sharks[i].r][sharks[i].c] != null){
                if(sharks[i].z > sharkTable[sharks[i].r][sharks[i].c].z){
                    sharkTable[sharks[i].r][sharks[i].c] = sharks[i];
                }
                removeShark += 1;
            } else {
                sharkTable[sharks[i].r][sharks[i].c] = sharks[i];
            }
        }
        M-= removeShark;
    }
    
    public static class Shark{
        int r, c, s, d, z;

        public Shark(int r, int c, int s, int d, int z){
            this.r = r;this.c = c;this.s = s;this.d = d;this.z = z;
        }
    }
}
