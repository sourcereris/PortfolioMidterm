import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.*;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Paint{
	
	private static painter paint;
	private static Rect rect; 
	private static Window window;
	
	Paint(){
		paint = new painter();
	}
	
	public static void main(String[] args) {
		
		Paint pain = new Paint();
		window = new Window(paint);
		paint.requestFocus();
	
		long now = 0;
		long mili = System.currentTimeMillis();
		while(true) {
			
			long time = now;
			
			if(System.currentTimeMillis() - time >= 10) {
				now = System.currentTimeMillis();
				paint.repaint();
			}
			
			if(System.currentTimeMillis() - mili >= 1000) {
				mili = System.currentTimeMillis();
			}
		}
	}
}

class painter extends JPanel implements MouseListener, MouseMotionListener{

	List<Rect> list = new LinkedList<>();
	
	int x, y;
	
	painter(){
		addMouseListener(this);
		addMouseMotionListener(this);
	}
	public void paintComponent(Graphics g) {
		
		super.paintComponent(g);
		for(Rect rect: list) {rect.draw(g);}
		list.add(new Rect(375,375, this));
		del();
	}
	void del() {
		for(int i = 0; i < list.size(); i++) {
			if(Math.abs(list.get(i).x - x) < 8 &&
					Math.abs(list.get(i).y - y) < 20) list.remove(i);
		}
	}@Override
	public void mouseMoved(MouseEvent e) {
		x = e.getX(); y = e.getY();
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		
	}
	@Override
	public void mousePressed(MouseEvent e) {
		for(int i = 0; i < 50; i++)
			list.add(new Rect(e.getX(), e.getY(), this));
		
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}