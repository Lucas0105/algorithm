package baekjoon;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Stack;

public class Class2P1406 {

	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		Stack<Character> command = new Stack<>();
		Stack<Character> rCommand = new Stack<>();
		String data = br.readLine();
		int N = Integer.parseInt(br.readLine());
		
		for (int i = 0; i < data.length(); i++) {
			command.add(data.charAt(i));
		}
		

		
		for (int i = 0; i < N; i++) {
			String inputData = br.readLine();
			
			if (inputData.charAt(0) == 'L') {
				if (!command.isEmpty()) rCommand.add(command.pop());
			} else if (inputData.charAt(0) == 'D') {
				if (!rCommand.isEmpty()) command.add(rCommand.pop());
			} else if (inputData.charAt(0) == 'B') {
				if (!command.isEmpty()) command.pop();
			} else if (inputData.charAt(0) == 'P') {
				command.add(inputData.charAt(2));
			}
			
		}
		
		while (!command.isEmpty()) {
			rCommand.add(command.pop());
		}
		
		while (!rCommand.isEmpty()) {
			bw.write(rCommand.pop());
		}
		
		bw.flush();
		bw.close();
	}

}
