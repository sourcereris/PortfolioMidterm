package mainPackage;
import javax.swing.JFrame;
import javax.swing.WindowConstants;

public class MainArrow extends JFrame{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	Panel panel = new Panel();
	public static void main(String[] args) {
		MainArrow mr = new MainArrow();
		
		mr.window(mr.panel);
		mr.panel.requestFocus();
		mr.loop();
		
	}
	
	void loop() {
		long now = System.currentTimeMillis();
		while(true) {
			
			if(System.currentTimeMillis() - now >= 16) {
				
				panel.repaint();
				now = System.currentTimeMillis();
			}
		}
	}
	
	void window(Panel panel) {
		setSize(600, 600);
		getContentPane().add(panel);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setVisible(true);
		setResizable(true);
	}
	
}