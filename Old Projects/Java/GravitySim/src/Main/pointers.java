package Main;

import java.awt.Graphics;

public class pointers {
	
	double x, y, dX, dY;
	double dirX;
	double dirY;
	
	pointers(int x, int y) {
		this.x = x;
		this.y = y;
	}
	void lines() {
		dX = x + dirX/20;
		dY = y + dirY/20;
	}
	
	void draw(Graphics g) {
		lines();
		g.drawLine((int)x, (int)y, (int)dX, (int)dY);
	}
}
