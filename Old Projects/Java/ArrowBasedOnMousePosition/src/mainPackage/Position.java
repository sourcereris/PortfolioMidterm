package mainPackage;

import java.awt.Graphics;
import java.awt.Polygon;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Position {
	
	double angle;
	double[][] arrow  = {{-10d, 0d, 10d},{15d, -15d, 15d}};
	double[][] result; //constantly changed by mouse in panel class;
	public int xMouse;
	public int yMouse;
	
	static List<Polygon> polys = new ArrayList<>();
	
	Position(){
		poly = new Polygon();
	}
	
	Panel panel;
	Polygon poly;
	
	public void paint(Graphics g) {
		
		double[][] rotMtr = {{Math.cos(angle), Math.sin(angle)},
	 			 			{-Math.sin(angle), Math.cos(angle)}};
		
		multiplyMatrices(rotMtr, arrow);
		coordinates();
		
		g.fillPolygon(poly);
		
	}
	
	void coordinates() {
		poly.reset();
		for(int i = 0; i < arrow[0].length; i++)
			poly.addPoint((int)result[0][i], (int)result[1][i]);
		poly.translate(xMouse, yMouse);
		
	}
	
	double[][] multiplyMatrices(double[][] firstMatrix, double[][] secondMatrix) {
	    result = new double[firstMatrix.length][secondMatrix[0].length];

	    for (int row = 0; row < result.length; row++) {
	        for (int col = 0; col < result[row].length; col++) {
	            result[row][col] = multiplyMatricesCell(firstMatrix, secondMatrix, row, col);
	        }
	    }return result;
	}
	
	double multiplyMatricesCell(double[][] firstMatrix, double[][] secondMatrix, int row, int col) {
	    double cell = 0;
	    for (int i = 0; i < secondMatrix.length; i++) {
	        cell += firstMatrix[row][i] * secondMatrix[i][col];
	    }return cell;
	    
	}
	
	void addToList() {
		Polygon one = new Polygon();
		int[] x;
		int[] y;
		
		x = poly.xpoints;
		y = poly.ypoints;
		
		for(int i = 0; i < poly.npoints; i++)
			one.addPoint(x[i],y[i]);
		polys.add(one);
	}
}
