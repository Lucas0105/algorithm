package programmers;

import java.util.*;

public class P43164 {

	public static void main(String[] args) {
		Solution solution = new Solution();
		String[][] input = {{"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"}};
		String[] answer = solution.solution(input);
		for(String ans : answer) {
			System.out.printf("%s ", ans);
		}
	}

}

class Solution {
    LinkedList<String> result;   
    boolean[] visit;
    
    public String[] solution(String[][] tickets) {
        result = new LinkedList<String>();
        visit = new boolean[tickets.length];
        dfs(0, "ICN", "ICN", tickets);
        Collections.sort(result);
        String[] answer = result.poll().split(" ");
        return answer;
    }
    
    public void dfs(int count, String start, String status, String[][] tickets) {
        if(tickets.length == count) {
            result.add(status);
            return;
        }
        
        for (int i = 0; i < tickets.length; i++) {
            if (!visit[i] && tickets[i][0].equals(start)) {
                visit[i] = true;
                dfs(count+1, tickets[i][1], status + " " + tickets[i][1], tickets);
                visit[i] = false;
            }
        }
        
        
    }
}