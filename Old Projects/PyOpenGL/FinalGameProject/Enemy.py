import pygame
from RandomPos import *
from OpenGL.GL import *
from OpenGL.GLU import *

class Enemy:

    def __init__(self):
        self.alfa = get_rand_num(-3.14, 3.14)
        self.theta = get_rand_num(-3.14, 3.14)

        self.pos = pygame.math.Vector3(10,10,10)
        self.dist = 50

        self.move = pygame.math.Vector3(0, 0, 0)
        self.location()



    def location(self):
        x = cos(self.theta)*cos(self.alfa) * self.dist
        y = sin(self.alfa) * self.dist
        z = sin(self.theta)*cos(self.alfa) * self.dist

        self.pos.x = x
        self.pos.y = y
        self.pos.z = z

        self.move.x = get_rand_num(-1, 1)
        self.move.y = get_rand_num(-1, 1)

        if z == 0:
            z = 0.0001
        self.move.z = (x*self.move.x + y+self.move.y)/z

        self.move = self.move.normalize()

    def update(self):

        dist = self.pos.length()/50
        self.pos += self.move/10 / dist
        self.move -= self.pos * 0.0001

        self.draw()

    def draw(self):
        glPushMatrix()  # Save the current matrix state
        glTranslatef(self.pos.x, self.pos.y, self.pos.z)
        glColor4f(0.1, 0.8, 0.4, 1)  # Set color to yellow
        cube = gluNewQuadric()  # Create a new quadrics object
        gluSphere(cube, 2, 10, 10)  # Draw the sphere
        glPopMatrix()  # Restore the previous matrix state
