package Main;
//F = (m * m) / d
//F = ma
//a = F/m
import java.util.Random;
import java.awt.Graphics;

public class item {
	
	Random random = new Random();
	
	double x, y;
	double f = 0.01; // force, how strong it pulls and acceleration.
	double dirX = random.nextDouble(-10, 10);
	double dirY = random.nextDouble(-10, 10);; // direction + (pos) or - (neg) (x/a)*dirX
	
	
	item(int x, int y){
		this.x = (double)x;
		this.y = (double)y;
	}
	void attraction() {
		x += (f * -dirX)*10;
		y += (f * -dirY)*10;
	}
	void walls() {
		if(x < 0 || x > 800) {
			dirX = dirX * (-1);
			
		}
			
		if(y < 0 || y > 800) 
			dirY = dirY * (-1);
	}
	void draw(Graphics g) {
		walls();
		attraction();
		g.fillOval((int)x, (int)y, 20, 20);
		
	}
}
