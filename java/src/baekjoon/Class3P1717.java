package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Class3P1717 {
	// n은 요소의 수. m은 연산의 수 
	static int n, m;
	static Element[] elements;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		Element[] elements = new Element[n+1];

		for (int i = 0; i <= n; i++) {
			Element newEl = new Element(i);
			elements[i] = newEl;
		}
		
		for (int i = 0; i < m; i++) {
			st = new StringTokenizer(br.readLine());
			int express = Integer.parseInt(st.nextToken());
			int parent = Integer.parseInt(st.nextToken());
			int child = Integer.parseInt(st.nextToken());
			
			// 합 연산
			if (express == 0) {
				if (parent == child) continue;
				
				Element pElement = elements[parent].findParent();
				Element cElement = elements[child].findParent();
				if (pElement != cElement) {
					cElement.parent = pElement;
				}
			// 같은 집합인지
			} else {
				if (elements[parent].findParent() == elements[child].findParent()) {
					System.out.println("YES");
				} else {
					System.out.println("NO");
				}
			}
			
		}
	}
	
	static class Element {
		public Element parent;
		int me;
		
		Element(int me) {
			this.me = me;
		}
		
		public Element findParent() {
			Element newEl = this;
			while (newEl.parent != null) {
				newEl = newEl.parent;
				this.parent = newEl;
			}
			return newEl;
		}
	}
}
