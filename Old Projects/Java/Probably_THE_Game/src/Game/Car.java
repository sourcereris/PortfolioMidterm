package Game;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

public class Car {
	GamePanel panel;
	//CarHitbox hitbox = new CarHitbox(this);
	boolean collected = false;
	
	double x = 80, y = 480;
	
	int bodyWidth = 70, bodyHeight = 40;
	int score = 0;
	
	double hitX1, hitY1;
	double hitX2, hitY2;
	double hitX3, hitY3;
	double hitX4, hitY4;
	
	
	double carAngle;
	double carRotationSpeed = Math.toRadians(8);
	double velocity = 0;
	double wheelAngle;
	
	Car (GamePanel panel){
		this.panel = panel;
	}
	
	void acceleration() {
		double vel = 0.8;
		if(score > 0 ) vel = 0.6;
		if(panel.up && velocity <= 0.8 && velocity >= 0) {
			velocity = velocity + 1.2 * 0.01;
		}else if(panel.down && velocity >= -0.4 && velocity <= 0) {
			velocity = velocity + 0.08 * -0.08;
		}else if(panel.down && velocity >= 0) {
			velocity = velocity + 0.4 * -0.1;
		}else if(panel.up && velocity <= 0) {
			velocity = velocity + 0.5 * 0.1;
		}
	}
	
	public void VehicleMove() {
		//////////////////////speed front/back ////////////////
		if(panel.up == true) {acceleration();}
		if(panel.down == true) {acceleration();}
		///////////////////// body and turret rotation////////
		if(panel.left == true) {carAngle -= 
						carRotationSpeed * velocity;
		}
		if(panel.right == true) {carAngle += carRotationSpeed * velocity;}
	}
	
	void carMovement() {
		y += 6*Math.sin(carAngle)*velocity;
		x += 6*Math.cos(carAngle)*velocity;
		if(panel.down == false && panel.up == false) {
			velocity = velocity + (velocity * -0.035);
			if(Math.abs(velocity) < 0.1) velocity = 0;
		}
	}
	
	void wheels() {
		wheelAngle = 0;
		if (panel.right && panel.left) wheelAngle = 0;
		else if(panel.right)wheelAngle = -Math.toRadians(30);
		else if(panel.left) wheelAngle = Math.toRadians(30);
	}
	
	
	void hit() {
		hitX1 = (-30 *  Math.cos(carAngle) + -16 * -Math.sin(carAngle))+x+35;
		hitY1 = (-30 *  Math.sin(carAngle) + -16 * Math.cos(carAngle))+y+20;
		
		hitX2 = (30 *  Math.cos(carAngle) + -16 * -Math.sin(carAngle))+x+35;
		hitY2 = (30 *  Math.sin(carAngle) + -16 * Math.cos(carAngle))+y+20;
		
		hitX3 = (-30 *  Math.cos(carAngle) + 16 * -Math.sin(carAngle))+x+35;
		hitY3 = (-30 *  Math.sin(carAngle) + 16 * Math.cos(carAngle))+y+20;
		
		hitX4 = (30 *  Math.cos(carAngle) + 16 * -Math.sin(carAngle))+x+35;
		hitY4 = (30 *  Math.sin(carAngle) + 16 * Math.cos(carAngle))+y+20;
	}
	
	
	void checkPoint() {
		if(x > 80 && x < 240 && y > 440 && y < 600 && collected) {
			collected = false;
			score++;
		}
	}
	
	void drawMe(Graphics g){
		Graphics2D g2 = (Graphics2D) g;
		
		carMovement();
		VehicleMove();
		wheels();
		checkPoint();
		
		g2.rotate(carAngle, x + 35, y + 20);
		
		//wheels
		g2.rotate(-wheelAngle, x + 50, y - 2);
		g.fillRoundRect((int)x + 40, (int)y, 20, 10, 5, 5);
		g2.rotate(wheelAngle,x + 50, y);
		
		g2.rotate(-wheelAngle, x + 50, y + 35);
		g.fillRoundRect((int)x + 40, (int)y + 30, 20, 10, 5, 5);
		g2.rotate(wheelAngle,  x + 50, y + 35);
		
		//car
		g.setColor(Color.gray);
		g.fillRoundRect((int)x, (int)y, bodyWidth, bodyHeight, 15, 15);
		//Window
		g.setColor(Color.BLACK);
		g.fillRoundRect((int)x + 38, (int)y + 5, 15, 30, 10, 30);
		g.fillRect((int)x + 48, (int)y + 5, 5, 30);
		Color color = new Color(0,0,0);
		if(collected) {
			color = new Color(10,200,10);
		}
		g.setColor(color);
		g.fillRect((int)x+4, (int)y+10, 20, 20);
		
		//hitbox.drawHitbox(g);
		g2.rotate(-carAngle, x + 35, y + 20);
		
		g.setColor(Color.BLACK);
		g2.setStroke(new BasicStroke(5));
		hit();
		g.drawLine((int)hitX1, (int)hitY1, (int)hitX2, (int)hitY2);
		g.drawLine((int)hitX3, (int)hitY3, (int)hitX4, (int)hitY4);
	}
}
