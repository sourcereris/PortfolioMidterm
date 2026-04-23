package Events;
import Main.*;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class mouse implements MouseListener{
	
	gPanel panel;
	public mouse(gPanel panel){
		this.panel = panel;
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		panel.set(e.getX(), e.getY());
		
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
