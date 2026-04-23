package panelPackage;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JPanel;

import inputs.KeyboardInputs;
import inputs.MouseInputs;

public class GamePanel extends JPanel{
	
	MouseInputs mouseInputs;
	Vehicle vehicle = new Vehicle();
	
	Thread thread = new Thread();;
	
	public boolean up, down, left, right, mouse, timer = true;
	public int x, y;
	
	List <Bullet> mag = new LinkedList<>();
	
	
	GamePanel(){
		mouseInputs = new MouseInputs(this);
		addKeyListener(new KeyboardInputs(this));
		addMouseListener(mouseInputs);
		addMouseMotionListener(mouseInputs);
		//addMouseListener(this);
	}
	public void turretPosition(int x, int y) {
		vehicle.mouseX = x;
		vehicle.mouseY = y;
	}
	public void bulletDirection() {
		
		if(mouse == true) {
			mag.add(new Bullet(vehicle,x, y));
			timer = false;
			}
		}
		
		
	
	void deleteBullet() {
		for(int i =0; i < mag.size(); i++) {
			if(mag.get(i).x >= 600) mag.remove(i);
		}
	}
	public void VehicleMove() {
		//////////////////////speed front/back ////////////////
		if(up == true) {vehicle.vehicleMovement(1);}
		if(down == true) {vehicle.vehicleMovement((float) -0.6);}
		///////////////////// body and turret rotation////////
		if(left == true) {vehicle.vehicleAngle -= 
						vehicle.vehicleRotationSpeed;
						vehicle.turretAngle -= 
						vehicle.vehicleRotationSpeed;
		}
		if(right == true) {vehicle.vehicleAngle += 
						vehicle.vehicleRotationSpeed;
						vehicle.turretAngle += 
						vehicle.vehicleRotationSpeed;}
	}/////////////////////////////////////////////////////////
	
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		bulletDirection();
		//deleteBullet();
		VehicleMove();
		vehicle.drive(g);
		for(Bullet shell: mag) shell.shot(g);
	}
}
