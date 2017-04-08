package main;

import java.util.ArrayList;
import java.util.concurrent.Callable;

public class Task implements Callable<Object> {

	int x ;
	ArrayList<ArrayList<Integer>> a;
	ArrayList<ArrayList<Integer>> b;
	ArrayList<ArrayList<Integer>> c;
	
	
	public Task(int x, ArrayList<ArrayList<Integer>> a, ArrayList<ArrayList<Integer>> b, ArrayList<ArrayList<Integer>> c){
		this.x = x;
		this.a = a;
		this.b = b;
		this.c = c;
	}

	@Override
	public Object call() {
		// TODO Auto-generated method stub
		for(int i = 0; i < b.get(0).size(); i++){
			for(int j = 0; j < a.get(0).size(); j++){
				c.get(x).set(i, c.get(x).get(i) + a.get(x).get(j) * b.get(j).get(i));
			}
		}
		return null;
	}
}
