import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class Events {
	
	public static void main(String[] args) {
		Events eve = new Events();
		eve.go();
	}
	
	JFrame app;
	JLabel label;
	public void go() {
		
		app = new JFrame();
		app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JButton ColorButton = new JButton("Change color!");
		ColorButton.addActionListener(new ColorAction());
		
		JButton LabelButton = new JButton("Change label!");
		
		LabelButton.addActionListener(new LabelAction());
		
		label = new JLabel("I am A Label!");
		MyDrawPanel panel = new MyDrawPanel();
		
		app.getContentPane().add(BorderLayout.SOUTH, ColorButton);
		app.getContentPane().add(BorderLayout.CENTER, panel);
		app.getContentPane().add(BorderLayout.EAST, LabelButton);
		app.getContentPane().add(BorderLayout.WEST, label);
		
		app.setSize(500, 300);
		app.setLocationRelativeTo(null);
	    
	    app.setVisible(true);
	    
	}
	class ColorAction implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			app.repaint();
		}
	}
	class LabelAction implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			label.setText("I was a Label!");
		}
	}
}
class MyDrawPanel extends JPanel {
	public void paintComponent(Graphics g) {
		Graphics2D g2d = (Graphics2D) g;
	
		int red = (int) (Math.random() * 255);
		int green = (int) (Math.random() * 255);
		int blue = (int) (Math.random() * 255);
		Color color = new Color(red, green, blue);
		
		red = (int) (Math.random() * 255);
		green = (int) (Math.random() * 255);
		blue = (int) (Math.random() * 255);
		Color color1 = new Color(red, green, blue);
		g.setColor(color);
		
		GradientPaint gradient = new GradientPaint(70,70, color, 150,150, color1);
		g2d.setPaint(gradient);
		g2d.fillOval(70,70,100,100);
		
		//g.fillOval(100, 100, 50, 50);
	}
}