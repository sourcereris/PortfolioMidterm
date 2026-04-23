package Game;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class CollectPoints{
	Car car;
	CollectPoints(GamePanel panel) {
		car = panel.car;
	}

	List<Coordinates> gems = new ArrayList<>();
	List<decoration> dec = new ArrayList<>();
	Random random = new Random();
	Color color;
	
	
	int getXLocation() {
		
		int y = random.nextInt(10)*40+1410;
		return y;
	}
	int getYLocation() {
		
		int y = random.nextInt(20)*40+90;
		return y;
	}
	void checkGem() {
		if(gems.size() < 1 && !car.collected) {
			gems.add(new Coordinates(getXLocation(),getYLocation()));
		}
	}
	
	public void draw(Graphics g){
		
		checkGem();
		
		for(Coordinates cord: gems) {
			g.setColor(cord.color);
			g.fillOval(cord.x, cord.y, 20, 20);
			
		}
		if(gems.size() != 0) {
			if(Math.abs(car.hitX1 - gems.get(0).x) < 20 && Math.abs(car.hitY1 - gems.get(0).y) < 20 ||
				Math.abs(car.hitX2 - gems.get(0).x) < 20 && Math.abs(car.hitY2 - gems.get(0).y) < 20||
				Math.abs(car.hitX3 - gems.get(0).x) < 20 && Math.abs(car.hitY3 - gems.get(0).y) < 20||
				Math.abs(car.hitX4 - gems.get(0).x) < 20 && Math.abs(car.hitY4 - gems.get(0).y) < 20) {
					int x1 = gems.get(0).x, y1 = gems.get(0).y;
					gems.remove(0);
					car.collected = true;
					/*for(int i = 0; i < 80; i++) {
						dec.add(new decoration(x1, y1, car));
					}*/
			}
		}
		if(dec.size() != 0) {
			for(decoration deco: dec) {
				deco.draw(g);
			}
		}
	}
	
	public class Coordinates {
		int x, y;
		Color color;
		
		Coordinates(int x, int y){
			this.x = x;
			this.y = y;
			getColor();
		}
		
		Color getColor() {
			int r = random.nextInt(80)+45;
			int g = random.nextInt(100)+155;
			int b = random.nextInt(40);
			color = new Color(r, g ,b);
			return color;
		}
	}
}
