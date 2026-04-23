package panelPackage;
import javax.swing.JFrame;

public class GameWindow {
	
	JFrame frame;
	
	GameWindow(GamePanel panel){
		frame = new JFrame();
		frame.setSize(800, 800);
		frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
		frame.add(panel);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}
}
