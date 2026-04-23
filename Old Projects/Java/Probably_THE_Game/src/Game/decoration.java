package Game;

import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;

public class decoration {
	
	Random random = new Random();
	Color color;
	Car car;
	
	final long TIME = System.currentTimeMillis();
	double x1 = Integer.MAX_VALUE;
	double y1 = Integer.MAX_VALUE;
	
	double x;
	double y;
	double xF, yF;
	double dirY = (double)random.nextInt(200)/100-1;
	double dirX = (double)random.nextInt(200)/100-1;
	
	decoration(double xF, double yF, Car car){
		this.xF = xF;
		this.yF = yF;
		this.car = car;
		this.color = getColor();
	}
	void returnTo () {
		
		x1 = x;y1 = y;
		x += x * Math.cos(Math.atan(((car.hitX1+10) - x1) /(((car.hitY1+5) - y1))));
		y += y * Math.sin(Math.atan(((car.hitX1+10) - x1) /(((car.hitY1+5) - y1))));
		System.out.println(car.hitX1);
		
	}
	protected void update() {
		
		x = (int) xF;
		y = (int) yF;
		
		xF = xF + dirX;
		yF = yF + dirY;
		
	}
	public Color getColor() {
		int r,g,b;
			r = random.nextInt(10);
			g = random.nextInt(50)+205;
			b = random.nextInt(40)+160;
			return new 			Color(r, g, b);
	}
	protected void draw(Graphics g){
		if(System.currentTimeMillis() - TIME < 1000)
			update();
		else returnTo();
			
		g.setColor(color);
		g.fillOval((int)x, (int)y, 8, 8);
		
	}
}
