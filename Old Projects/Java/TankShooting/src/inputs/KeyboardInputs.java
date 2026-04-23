package inputs;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import panelPackage.GamePanel;
public class KeyboardInputs implements KeyListener{

	private GamePanel panel;
	public KeyboardInputs(GamePanel gamePanel) {
		this.panel = gamePanel;
	}
	
	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyPressed(KeyEvent e) {
		if(e.getKeyCode() == 'W') {
			panel.up = true;
		}if(e.getKeyCode() == 'A') {
			panel.left = true;
		}if(e.getKeyCode() == 'S') {
			panel.down = true;
		}if(e.getKeyCode() == 'D') {
			panel.right = true;
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		if(e.getKeyCode() == 'W') {
			panel.up = false;
		}if(e.getKeyCode() == 'A') {
			panel.left = false;
		}if(e.getKeyCode() == 'S') {
			panel.down = false;
		}if(e.getKeyCode() == 'D') {
			panel.right = false;
		}
	}

}
