package panel;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

public class Point {
	
	boolean t = false;
	int x = -10, y, x2 = -10, y2;
	
	void changeColor(Graphics g) {
		if(t) {
			g.setColor(Color.GREEN);
			t = false;
		}
	}
	
	void draw(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		
		changeColor(g);
		g2.setStroke(new BasicStroke(6));
		g.fillOval(x-10, y-10, 20, 20);
		g.drawLine(x, y, x2, y2);
		g.fillOval(x2-10, y2-10, 20, 20);
		
		
	}
}
