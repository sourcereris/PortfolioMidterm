from OpenGL.GL import *
import pygame

class Mesh:
    def __init__(self):
        self.vertices = []
        self.triangles = []
        self.draw_type = GL_LINE_LOOP

    def draw(self):
        for f in range(0, len(self.triangles), 3):  # Step by 3 to get a triangle (3 vertices)
            glBegin(self.draw_type)  # Begin drawing the triangle
            glVertex3fv(self.vertices[self.triangles[f]])  # First vertex
            glVertex3fv(self.vertices[self.triangles[f + 1]])  # Second vertex
            glVertex3fv(self.vertices[self.triangles[f + 2]])  # Third vertex
            glEnd()