package Game;

public class Game implements Runnable{
	
	GamePanel gamePanel;
	private Thread gameThread;
	
	Game(){
		gamePanel = new GamePanel();
		new Window(gamePanel);
		gamePanel.requestFocus();
		startLoop();
	}
	
	void startLoop() {
		gameThread = new Thread(this);
		gameThread.start();
	}
	
	@Override
	public void run() {
		long now = System.currentTimeMillis();
		while(true) {
			
			if(System.currentTimeMillis() - now >= 16) {
				
				gamePanel.repaint();
				now = System.currentTimeMillis();
			}
		}
	}
}
