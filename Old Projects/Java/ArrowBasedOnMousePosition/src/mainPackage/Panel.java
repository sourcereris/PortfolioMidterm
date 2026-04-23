package mainPackage;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;
import inputs.MouseInput;

public class Panel extends JPanel{
	
	Position position = new Position();
	MouseInput mouseInput;
	
	Panel(){
		mouseInput = new MouseInput(this);
		addMouseListener(mouseInput);
		addMouseMotionListener(mouseInput);
		
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		g.fillOval(195, 195, 10, 10);
		
		position.paint(g);
		iterateArrows(g);
		
	}
	
	void iterateArrows(Graphics g) {
		
		for(int i = 0; i < Position.polys.size(); i++) {
			g.fillPolygon(Position.polys.get(i));
		}
	}
	
	public void arrPos(int xP, int yP) {
		position.xMouse = xP;
		position.yMouse = yP;
		position.angle  = Math.toRadians(90);
		
		xP -= 200; yP -= 200;
		if(yP < 0)
			 position.angle += Math.acos(xP/(Math.sqrt((xP*xP)+(yP*yP))));
		else position.angle += -Math.acos(xP/(Math.sqrt((xP*xP)+(yP*yP))));
	}
	
	public void capture() {
		int[] x = new int[3];
		
		position.addToList();
		System.out.println(Position.polys.size());
		/*for(int j = 0; j < capArrow.polys.size(); j++) {
			x = capArrow.polys.get(j).xpoints;
			
			for(int i = 0; i < x.length; i++) {
				System.out.println(x[i]);
			}
		}*/
	}
}