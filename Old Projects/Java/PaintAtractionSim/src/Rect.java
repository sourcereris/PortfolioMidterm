import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;

public class Rect{
	
	painter paint; 
	
	Random random = new Random();
	Color color;
	
	final long TIME = System.currentTimeMillis();
	
	double x;
	double y;
	double xF;
	double yF;
	
	double addx;
	double addy;
	
	float dirY = random.nextFloat(-1,1);
	float dirX = random.nextFloat(-1,1);
	
	double rand = random.nextDouble(0.5, 10);
	
	Rect(float xF, float yF, painter painter){
		this.xF = xF;
		this.yF = yF;
		this.paint = painter;
		this.color = getColor();
	}
	
	void returnTo() {
		x = xF;
		y = yF;
		
			addx = Math.cos(Math.atan2( (paint.y - y),(paint.x - x)));
			addy = Math.sin(Math.atan2( (paint.y - y),(paint.x - x)));
			
		xF += addx * rand;
		yF += addy * rand;
	}
	protected void update() {
		
		x = xF;
		y = yF;
		
		xF += dirX;
		yF += dirY;
		
	}
	public Color getColor() {
		int r,g,b;
			r = random.nextInt(200, 255);
			g = random.nextInt(140, 255);
			b = random.nextInt(00, 1);
			return new 			Color(r, g, b);
	}
	protected void draw(Graphics g){
		int t = random.nextInt(5000);
		
		if(System.currentTimeMillis() - TIME < y)
			update();
		else returnTo();
		
		g.setColor(color);
		g.fillOval((int)x, (int)y, 8, 8);
		
	}
}
