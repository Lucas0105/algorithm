package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class Class2P2504 {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String data = br.readLine();
		int limit = data.length();
		int index = 0;
		int result = 0;
		int mul = 1;
		Stack<Character> stack = new Stack<>();
		char nextChar;
		
		while (index < limit) {
			char curChar = data.charAt(index);
			nextChar = 'x';
			
			if (index + 1 != limit) {
				nextChar = data.charAt(index+1);
			}
			
			if (curChar == '(' && nextChar == ')') {
				result += 2 * mul;
				index ++;
			} else if(curChar == '[' && nextChar == ']') {
				result += 3 * mul;
				index ++;
			} else if (curChar == '(') {
				stack.add(curChar);
				mul *= 2;
			} else if (curChar == '[') {
				stack.add(curChar);
				mul *= 3;
			} else if (curChar == ')'){
				if (stack.isEmpty() || stack.peek() != '(') {
					result = 0;
					break;
				}
				stack.pop();
				mul /= 2;
			} else if (curChar == ']') {
				if (stack.isEmpty() || stack.peek() != '[') {
					result = 0;
					break;
				}
				stack.pop();
				mul /= 3;
			}
			
			index ++;
		}
		
		if (!stack.isEmpty()) result = 0;
		
		System.out.println(result);
	}
}
