import pygame
from OpenGL.GL import *
from OpenGL.GLU import *

class Bullet:

    def __init__(self, pos, direction):
        self.pos = pygame.math.Vector3(pos)
        self.direction = direction

    def update(self):
        self.pos += self.direction*2

    def draw(self):
        glPushMatrix()  # Save the current matrix state
        glTranslatef(self.pos.x, self.pos.y, self.pos.z)
        glColor4f(0.6, 0.6, 0.6, 1)  # Set color to yellow
        sphere = gluNewQuadric()  # Create a new quadrics object
        gluSphere(sphere, 0.1, 20, 20)  # Draw the sphere
        glPopMatrix()