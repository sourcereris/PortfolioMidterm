package Game;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.TextField;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Inputs.KeyInputs;
import Inputs.MouseInputs;

public class GamePanel extends JPanel{
	Car car;
	CollectPoints coll;
	MouseInputs mouseInputs;
	JTextField tf;
	String score;
	
	
	Map map = new Map();
	public boolean up, down, right, left;
	
	int x = 0, y = 0;
	final long TIME = System.currentTimeMillis();
	
	int printButton = 0;
	GamePanel(){
		car = new Car(this);
		coll = new CollectPoints(this);
		mouseInputs = new MouseInputs(this);
		addMouseListener(mouseInputs);
		addKeyListener(new KeyInputs(this));
		addMouseMotionListener(mouseInputs);
	}
	
	void wall(Graphics g) {
		for(int i = 0; i < map.tiles.length; i++) {
			for(int j = 0; j < map.tiles[0].length; j++) {
				
				if(map.tiles[i][j] != 1)continue;
				
				if(car.hitX1 > i*40 && car.hitY1 > j*40 && 
						car.hitX1 <= i*40 + 40 && car.hitY1 <= j*40 +40) car.velocity *= -1;
				if(car.hitX2 > i*40 && car.hitY2 > j*40 && 
						car.hitX2 <= i*40 + 40 && car.hitY2 <= j*40 +40) car.velocity *= -1;
				if(car.hitX3 > i*40 && car.hitY3 > j*40 && 
						car.hitX3 <= i*40 + 40 && car.hitY3 <= j*40 +40) car.velocity *= -1;
				if(car.hitX4 > i*40 && car.hitY4 > j*40 && 
						car.hitX4 <= i*40 + 40 && car.hitY4 <= j*40 +40) car.velocity *= -1;
				
			}
		}
	}
	
	int time() {
		
		int time = (int)(System.currentTimeMillis()-TIME);
		
		return time;
	}
	void game(Graphics g){
		Graphics2D g2 = (Graphics2D) g;
		
		map.mapBuilder();
		map.addlist(map.wall0);
		if(car.score == 1)map.addlist(map.wall1);
		if(car.score == 2)map.addlist(map.wall2);
		if(car.score == 3)map.addlist(map.wall3);
		if(car.score == 4)map.addlist(map.wall4);
		if(car.score == 5)map.addlist(map.wall5);
		if(car.score == 6)map.addlist(map.wall6);
		
		
		for(int i = 0; i < map.tiles.length;i++) {
			for(int j = 0; j < map.tiles[0].length;j++) {
				if(map.tiles[i][j] == 1) g.fillRect(i*40, j*40, 40, 40);
			}
		}
		
		for(int i = 0; i < 4;i++) {
			for(int j = 0; j < 4; j++) {
				g.setColor(Color.green);
				g.fillRect(i*40+80, j*40+440, 40, 40);
			}
		}
		
		
		g.setColor(Color.black);
		wall(g);
		car.drawMe(g);
		coll.draw(g);
		
		
		g.setColor(Color.black);
		String str = Integer.toString(time()/1000);
		g.drawString(str, 50, 50);
	}
	void menu() {
		score = Integer.toString(car.score);
		if(printButton != 1) {
			add(tf = new JTextField("Your Score is: " + score));
			printButton++;
		}
	}
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		
		if(System.currentTimeMillis()-TIME < 100000)game(g);
		else menu();
	}
}
