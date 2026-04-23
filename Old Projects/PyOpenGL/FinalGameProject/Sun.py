import pygame
from OpenGL.GL import *
from OpenGL.GLU import *
from math import *
import time


class Sun:

    def __init__(self, mass):

        self.mass = mass
        self.pos = pygame.math.Vector3(0., 0., 0.)
        self.parameters = [1, 30, 30] #size, latitude, longitude
        self.g = 0.01
        # self.stime = time.time()
        #
        # self.pos = pygame.math.Vector3(10., 0., 0.)
        # self.velocity = pygame.math.Vector3(0., 0., 0.05)
        # self.pos_diff = pygame.math.Vector3(0.,0.,0.)
        # self.force = 0.

    def draw(self):

        # self.pos_diff = -self.pos
        # self.force = self.g * self.mass / self.pos_diff.length()
        #
        # self.velocity += self.pos_diff * self.force
        # self.pos = self.pos + self.velocity


        glPushMatrix()  # Save the current matrix state

        glTranslatef(self.pos[0], self.pos[1], self.pos[2])
        glColor4f(1, 0.5, 0.5, 1)  # Set color to yellow
        sphere = gluNewQuadric()  # Create a new quadriceps object
        gluSphere(sphere, self.parameters[0], self.parameters[1], self.parameters[2])  # Draw the sphere

        glPopMatrix()  # Restore the previous matrix state
