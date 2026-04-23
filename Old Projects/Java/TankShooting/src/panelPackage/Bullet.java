package panelPackage;

import java.awt.Graphics;
import java.util.Random;

public class Bullet{
	
	Random random = new Random();
	double x, y;
	double angle;
	int bulletSize = 8;
	double i = random.nextDouble(0.5);
	double a = Math.toRadians(10);
	Bullet(Vehicle vehicle,int x, int y){
		this.x = Math.cos(vehicle.turretAngle)*32 + vehicle.x + 27;
		this.y = Math.sin(vehicle.turretAngle)*32 + vehicle.y + 11;
		this.angle = vehicle.turretAngle;
	}
	
	void trajectory() {
		x += Math.cos(angle + a*i)*20;
		y += Math.sin(angle + a*i)*20;
	}
	
	void shot(Graphics g) {
	trajectory();
	g.fillOval((int)x, (int)y, bulletSize, bulletSize);
	
	}
}
