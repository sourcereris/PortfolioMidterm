package panel;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;


public class TwoConnectedPoints_Main extends JFrame{
	Panel panel;
	public static void main(String[] args) {
		TwoConnectedPoints_Main main = new TwoConnectedPoints_Main();
		main.go();
	}
	
	void go(){
		JButton ColorButton = new JButton("Green");
		
		setSize(600,600);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		getContentPane().add(BorderLayout.CENTER, panel = new Panel());
		//getContentPane().add(BorderLayout.WEST, ColorButton);
		
		setVisible(true);
		
		panel.requestFocusInWindow();
		long now = System.currentTimeMillis();
		while(true) {
			
			if(System.currentTimeMillis() - now >= 16) {
				
				panel.repaint();
				now = System.currentTimeMillis();
				ColorButton.addActionListener(new ColorAction());
			}
			
		}
	}
	private class ColorAction implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			System.out.println("Green!");
			panel.points.get(panel.points.size()).t = true;
		}
		
	}
}
