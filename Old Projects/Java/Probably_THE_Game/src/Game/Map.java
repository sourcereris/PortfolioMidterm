package Game;

import java.util.ArrayList;
import java.util.List;

public class Map {
	int[][] tiles = new int[48][27];
	
	List<tiles> wall0 = new ArrayList<>();
	List<tiles> wall1 = new ArrayList<>();
	List<tiles> wall2 = new ArrayList<>();
	List<tiles> wall3 = new ArrayList<>();
	List<tiles> wall4 = new ArrayList<>();
	List<tiles> wall5 = new ArrayList<>();
	List<tiles> wall6 = new ArrayList<>();
	List<tiles> wall7 = new ArrayList<>();
	List<tiles> wall8 = new ArrayList<>();
	
	
	void addlist(List<tiles> tilesList) {
		for(int i = 0; i < tilesList.size();i++) {
			tiles[tilesList.get(i).x][tilesList.get(i).y] = 1;
		}
	}
	
	void mapBuilder() {
		for(int i = 0; i != 48; i++) {
			wall0.add(new tiles(i,0));
			wall0.add(new tiles(i,25));
			wall0.add(new tiles(i,26));
		}
		for(int i = 0; i != 25;i++) {
			wall0.add(new tiles(0, i));
			wall0.add(new tiles(47, i));
		}
		
		wall0.add(new tiles(21,1));wall0.add(new tiles(21,2));
		wall0.add(new tiles(21,3));wall0.add(new tiles(22,1));
		wall0.add(new tiles(22,2));
		wall0.add(new tiles(21,22));wall0.add(new tiles(21,23));
		wall0.add(new tiles(21,24));wall0.add(new tiles(22,24));
		wall0.add(new tiles(22,23));
		
		wall1.add(new tiles(10,10));wall1.add(new tiles(11,10));
		wall1.add(new tiles(11,10));wall1.add(new tiles(11,9));
		wall1.add(new tiles(11,8)); wall1.add(new tiles(11,7));
		wall1.add(new tiles(11,6)); wall1.add(new tiles(11,5));
		wall1.add(new tiles(11,4)); wall1.add(new tiles(11,3));
		wall1.add(new tiles(11,2)); wall1.add(new tiles(11,1));
		
		
		wall1.add(new tiles(10,15));
		wall1.add(new tiles(11,16));wall1.add(new tiles(11,15));
		wall1.add(new tiles(11,17));wall1.add(new tiles(11,18));
		wall1.add(new tiles(11,19));wall1.add(new tiles(11,20));
		wall1.add(new tiles(11,21));wall1.add(new tiles(11,22));
		wall1.add(new tiles(11,23));wall1.add(new tiles(11,24));
		
		wall2.add(new tiles(15,7));wall2.add(new tiles(15,8));
		wall2.add(new tiles(15,9));wall2.add(new tiles(15,10));
		wall2.add(new tiles(16,10));wall2.add(new tiles(16,11));
		wall2.add(new tiles(16,12));wall2.add(new tiles(16,13));
		wall2.add(new tiles(16,14));wall2.add(new tiles(16,15));
		wall2.add(new tiles(15,15));wall2.add(new tiles(15,16));
		wall2.add(new tiles(15,17));wall2.add(new tiles(15,18));
		
		
		wall3.add(new tiles(21,6));wall3.add(new tiles(21,7));
		wall3.add(new tiles(21,8));wall3.add(new tiles(22,6));
		wall3.add(new tiles(23,6));wall3.add(new tiles(24,6));
		wall3.add(new tiles(25,6));wall3.add(new tiles(25,5));
		wall3.add(new tiles(21,17));wall3.add(new tiles(21,18));
		wall3.add(new tiles(21,19));wall3.add(new tiles(22,19));
		wall3.add(new tiles(23,19));wall3.add(new tiles(24,19));
		wall3.add(new tiles(25,19));wall3.add(new tiles(25,20));
		wall3.add(new tiles(24,10));
		wall3.add(new tiles(24,11));wall3.add(new tiles(24,12));
		wall3.add(new tiles(24,13));wall3.add(new tiles(24,14));
		wall3.add(new tiles(24,15));
		
		wall4.add(new tiles(29,1));wall4.add(new tiles(29,2));
		wall4.add(new tiles(29,3));wall4.add(new tiles(30,3));
		wall4.add(new tiles(31,3));wall4.add(new tiles(31,2));
		wall4.add(new tiles(31,1));wall4.add(new tiles(29,22));
		wall4.add(new tiles(29,23));wall4.add(new tiles(31,22));
		wall4.add(new tiles(29,24));wall4.add(new tiles(30,22));
		wall4.add(new tiles(31,24));wall4.add(new tiles(31,23));
		
		wall5.add(new tiles(29,6));wall5.add(new tiles(29,7));
		wall5.add(new tiles(29,8));wall5.add(new tiles(29,9));
		wall5.add(new tiles(29,10));wall5.add(new tiles(30,6));
		wall5.add(new tiles(31,6));wall5.add(new tiles(32,6));
		wall5.add(new tiles(33,6));wall5.add(new tiles(34,6));
		wall5.add(new tiles(34,5));
		wall5.add(new tiles(35,5));
		wall5.add(new tiles(29,15));wall5.add(new tiles(29,16));
		wall5.add(new tiles(29,17));wall5.add(new tiles(29,18));
		wall5.add(new tiles(29,19));wall5.add(new tiles(30,19));
		wall5.add(new tiles(31,19));wall5.add(new tiles(32,19));
		wall5.add(new tiles(33,19));wall5.add(new tiles(34,19));
		wall5.add(new tiles(34,20));
		wall5.add(new tiles(35,20));
		wall5.add(new tiles(35,12));
		wall5.add(new tiles(36,12));wall5.add(new tiles(36,13));
		wall5.add(new tiles(35,13));
		

		wall6.add(new tiles(31,10));wall6.add(new tiles(31,9));
		wall6.add(new tiles(32,9));wall6.add(new tiles(33,9));
		wall6.add(new tiles(30,10));wall6.add(new tiles(30,15));
		wall6.add(new tiles(31,15));wall6.add(new tiles(32,16));
		wall6.add(new tiles(31,16));wall6.add(new tiles(33,16));
		
		
	}
	
	class tiles{
		int x, y;
		tiles(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
}
