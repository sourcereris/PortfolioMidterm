package Main;
import java.awt.Graphics;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

import javax.swing.JPanel;
import Events.mouse;



public class gPanel extends JPanel{
	
	List<item> list = new LinkedList<>();
	List<pointers> list1 = new LinkedList<>();
	
	Random random = new Random();

	mouse mouse;
	gPanel(){
		mouse = new mouse(this);
		addMouseListener(new mouse(this));
		setPoints();
	}
	
	public void set(int x, int y) {
		list.add(new item(x,y));
	}
	void setPoints(){
		for(int i = 0; i < 800; i+=40) {
			for(int j = 0; j < 800; j+=40) {
				list1.add(new pointers(i,j));
			}
		}
	}
	protected void paintComponent(Graphics g){
		super.paintComponent(g);
		for(item item: list) {item.draw(g);}
		for(pointers point: list1) {point.draw(g);}
		/*if(list.size() < 50) {
			list.add(new item(random.nextInt(0, 800), random.nextInt(0, 800)));
		}*/
		physics();
	}
	
	// dist = sqrt((x1-x2)^+(y1-y2)^)
	private double distance(int i, int j) {
		double distance = Math.sqrt(Math.pow((list.get(j).x - list.get(i).x),2)
				+Math.pow((list.get(j).y - list.get(i).y),2));
		return distance;
	}
	public void physics() {
		for(int i = 0; i < list1.size(); i++) {
			for(int j = 0; j < list.size(); j++) {
				list1.get(i).dirX = (list1.get(i).x - list.get(j).x);
				list1.get(i).dirY = (list1.get(i).y - list.get(j).y);
			}
		}
		for(int i = 0; i < list.size(); i++) {
			for(int j = 0; j < list.size(); j++) {
				if(i == j)continue;
				list.get(i).f = 0.1/distance(i, j);
				list.get(i).dirX += (list.get(i).x - list.get(j).x) / distance(i, j);
				list.get(i).dirY += (list.get(i).y - list.get(j).y) / distance(i, j);
			}
		}
	}
}
