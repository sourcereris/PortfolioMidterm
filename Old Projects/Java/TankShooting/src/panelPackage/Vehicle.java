 package panelPackage;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

public class Vehicle {
	
	double x = 50, y = 200;
	int mouseX, mouseY;
	int gunWidth = 40, gunHeight = 10;
	int bodyWidth = 50, bodyHeight = 30;
	double angleDiff;
	double turretAngle = Math.toRadians(0);
	double turretRotationSpeed = Math.toRadians(3); //3 degrees in one frame
	double vehicleAngle;
	double vehicleRotationSpeed = Math.toRadians(7);
	//turret 26;26
	//body 50;30
	//middle is x+31, y+15
	
	//angle between turret and mouse is tan(mousex - x+31)/(mousey - y+15)
	void rotate() {
		
		double x1, y1, PI, mouseAngle;
		x1 = (mouseX - (x+31));
		y1 = (mouseY - (y+15));
		PI = Math.PI;
		mouseAngle = Math.atan(y1/x1);
		
		//in which quarter angle 180 or 360 + degrees///////////////
		if(x1 >= 0 && y1 < 0)mouseAngle += (2 * PI); // 4th quarter
		else if(x1 < 0) {
			if(y1 >= 0)		mouseAngle += PI; 	    //2nd quarter
			else 			mouseAngle += PI; 		//3rd quarter
		}//////////////////////////////////////////////////////////
		
		angleDiff = turretAngle - mouseAngle;
		//////////////////////////////////////////////////////
		if(Math.abs(angleDiff) <= Math.toRadians(3))			
						 degreeCalc(mouseAngle,PI);				// angle = turretAngle - mouseAngle
		else if(angleDiff <=      PI  && angleDiff >=     0   )	//angle 0     <-> 180
						{degreeCalc(mouseAngle,PI);turretAngle -= turretRotationSpeed;}
		else if(angleDiff <= 0             && angleDiff >=    -PI)	//angle 0     <-> (-180)
						{degreeCalc(mouseAngle,PI);turretAngle += turretRotationSpeed;}
		else if(angleDiff <= (2 * PI) && angleDiff >=     PI ) //angle 180   <-> 360
						{degreeCalc(mouseAngle,PI);turretAngle += turretRotationSpeed;}
		else if(angleDiff <=     -PI  && angleDiff >= (-2*PI)) //angle (-180)<->(-360)
						{degreeCalc(mouseAngle,PI);turretAngle -= turretRotationSpeed;}	
		//////////////////////////////////////////////////////
	}
	void degreeCalc(double mouseAngle, double PI) {
		if(turretAngle + turretRotationSpeed >= (2*PI))turretAngle -= (2*PI);
		else if(turretAngle - turretRotationSpeed <= 0)			 turretAngle += (2*PI);
		if(Math.abs(angleDiff) <= turretRotationSpeed) {turretAngle = mouseAngle;}
	}
	void vehicleMovement(float i) {
		y += 6*Math.sin(vehicleAngle)*i;
		x += 6*Math.cos(vehicleAngle)*i;
	}
	
	
	public void drive(Graphics g) {
		Graphics2D g2 = (Graphics2D)g;

		g2.rotate(vehicleAngle, x + 30, y + 15);
		g.fillRect((int)x, (int)y, bodyWidth, bodyHeight);
		g2.rotate(-vehicleAngle, x + 30, y + 15);
		
		g2.setColor(new Color(69, 75, 27));
		g.fillOval((int)x + 18, (int)y + 2, 26, 26); //hull diameter 26
		g2.rotate(turretAngle, x + 30, y + 15);
		g.fillRect((int)x + 30, (int)y + 10, gunWidth, gunHeight);
		g2.rotate(-turretAngle, x + 30, y + 15);
		rotate();

	}
}
