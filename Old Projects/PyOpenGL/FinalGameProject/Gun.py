import pygame
from RandomPos import *
from OpenGL.GL import *
from OpenGL.GLU import *


def diagonal_vector(pos, frm, to):
    x = get_rand_num(frm, to)

    y = get_rand_num(frm, to)

    z = (x * pos.x + y * pos.y)/pos.z * -1

    return pygame.math.Vector3(x, y, z)


class Gun:

    def __init__(self, pos, sun):
        self.pos = pygame.math.Vector3(pos)
        self.movement = pygame.math.Vector3(diagonal_vector(pos, -1, 1))
        self.sun = sun



    def update(self):

        pos_diff = self.sun.pos - self.pos
        force = self.sun.g * self.sun.mass / (pos_diff.length())
        self.movement -= force * pos_diff
        self.pos -= self.movement * 0.1
        self.draw()

    def draw(self):
        glPushMatrix()  # Save the current matrix state
        glTranslatef(self.pos.x, self.pos.y, self.pos.z)
        glColor4f(0.6, 0.6, 0.6, 1)  # Set color to yellow
        sphere = gluNewQuadric()  # Create a new quadrics object
        gluSphere(sphere, 0.2, 20, 20)  # Draw the sphere
        glPopMatrix()  # Restore the previous matrix state

        #if self.pos.z < - 10:
            #self.b = False

