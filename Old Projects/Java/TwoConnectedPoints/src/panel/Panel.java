package panel;

import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;

public class Panel extends JPanel implements MouseListener, MouseMotionListener{
	
	Point point;
	List<Point> points = new ArrayList<>();
	
	Panel(){
		point = new Point();
		addMouseListener(this);
		addMouseMotionListener(this);
	}
	
	
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		point.draw(g);
		for(Point point: points) {
			point.draw(g);
		}
	}
	
	void addToList() {
		points.add(new Point());
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		points.get(points.size()-1).x2 = e.getX(); points.get(points.size()-1).y2  = e.getY();
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		addToList();
		points.get(points.size()-1).x2 = e.getX(); points.get(points.size()-1).y2  = e.getY();
		points.get(points.size()-1).x = e.getX(); points.get(points.size()-1).y  = e.getY();
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		points.get(points.size()-1).x2 = e.getX(); points.get(points.size()-1).y2  = e.getY();
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
}
