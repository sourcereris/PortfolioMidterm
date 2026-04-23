package Main;

public class Main {

	private static gPanel panel;
	public static void main(String[] args) {
		
		panel = new gPanel();
		new Window(panel);
		panel.requestFocus();
		int[] nums = {1,1,1,1};
		System.out.println(nums.length);
		
		long now = System.currentTimeMillis();
		
		while(true) {
			if(System.currentTimeMillis() - now > 10) {
				now = System.currentTimeMillis();			
				panel.repaint();
			}
		}

	}

}
