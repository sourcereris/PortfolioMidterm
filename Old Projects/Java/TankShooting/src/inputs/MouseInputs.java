package inputs;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import panelPackage.GamePanel;

public class MouseInputs implements MouseListener, MouseMotionListener {
	
	private GamePanel panel;
	public MouseInputs(GamePanel panel){
		this.panel = panel;
	}
	
	
	@Override
	public void mouseDragged(MouseEvent e) {
		panel.turretPosition(e.getX(), e.getY());
		
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		panel.turretPosition(e.getX(), e.getY());
		panel.x = e.getX();
		panel.y = e.getY();
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		
		panel.mouse = true;
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		panel.mouse = false;
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
