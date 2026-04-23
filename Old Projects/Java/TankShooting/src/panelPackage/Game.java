package panelPackage;
public class Game implements Runnable{
	private GamePanel gamePanel;
	
	private Thread gameThread;
	private final int FPS_SET = 60;
	
	public Game() {
		gamePanel = new GamePanel();
		new GameWindow(gamePanel);
		gamePanel.requestFocus();
		startGameLoop();
		
	}
	private void startGameLoop() {
		gameThread = new Thread(this);
		gameThread.start();
		
	}
	@Override
	public void run() {
		double timePerFrame = 1000000000 / FPS_SET;
		long lastTime = System.nanoTime();
		long now = System.nanoTime();
		
		while(true) {
			now = System.nanoTime();
			if(now - lastTime >= timePerFrame) {
				gamePanel.repaint();
				lastTime = now;
			}
		}
	}
	
}
