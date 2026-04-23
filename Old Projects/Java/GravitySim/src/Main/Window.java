package Main;
import javax.swing.JFrame;

public class Window extends JFrame{
	JFrame frame = new JFrame();
	
	Window(gPanel paint){
		frame.setSize(800, 800);
		frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
		frame.add(paint);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}
}
