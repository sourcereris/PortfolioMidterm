package inputs;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import mainPackage.*;

public class MouseInput implements MouseMotionListener, MouseListener{
	
	Panel panel;
	long now = System.currentTimeMillis();
	
	public MouseInput(Panel panel){
		this.panel = panel;
	}
	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override //this timer needs to be on a differend thread! FIX NEEDED
	public void mouseMoved(MouseEvent e) {
		/*if(System.currentTimeMillis() - now >= 16) {
				
				now = System.currentTimeMillis();
			}*/
		panel.arrPos(e.getX(), e.getY());
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		
	}
	@Override
	public void mousePressed(MouseEvent e) {
		panel.capture();
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

}
