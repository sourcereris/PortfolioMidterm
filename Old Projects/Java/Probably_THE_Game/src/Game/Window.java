package Game;
import javax.swing.JFrame;

public class Window extends JFrame{
	GamePanel panel;
	
	int x = 1920, y = 1080;
	
	Window(GamePanel panel){
		this.panel = panel;
		parameters();
	}
	
	void parameters() {
		setSize(1920,1080);
		getContentPane().add(panel);
		setDefaultCloseOperation(this.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setVisible(true);
		setResizable(true);
	}
}
