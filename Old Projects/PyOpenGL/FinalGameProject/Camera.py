from math import *
from math import pi

import pygame
from pygame import MOUSEBUTTONDOWN
from Gun import *

class Camera:
    def __init__(self):
        self.eye = pygame.math.Vector3(0,3,0)
        self.up = pygame.math.Vector3(0,1,0)
        self.right = pygame.math.Vector3(1,0,0)
        self.forward = pygame.math.Vector3(0,-3,-20)
        self.look = self.eye + self.forward
        self.yaw = 90
        self.pitch = 0
        self.last_mouse = pygame.math.Vector2(0,0)

        self.x_angle = 0.

    def rotate(self, yaw, pitch):
        self.yaw += yaw
        self.pitch += pitch
        self.pitch = max(-90, min(90, self.pitch))

        self.forward.x = cos(radians(self.yaw)) * cos(radians(self.pitch)) * 20
        self.forward.y = sin(radians(self.pitch)) * 20
        self.forward.z = sin(radians(self.yaw)) * cos(radians(self.pitch)) * 20

        self.forward = self.forward.normalize()
        self.right = self.forward.cross(pygame.Vector3(0,1,0)).normalize()
        self.up = self.right.cross(self.forward).normalize()

    def camera_path(self):
        self.eye[0] = cos(self.x_angle) * 40
        self.eye[2] = sin(self.x_angle) * 40

    def update(self, w, h):


        self.look = self.eye + self.forward
        gluLookAt(  self.eye.x, self.eye.y, self.eye.z,
                    self.look.x, self.look.y, self.look.z,
                    self.up.x, self.up.y, self.up.z)

        if pygame.mouse.get_visible():
            return

        mouse_pos = pygame.mouse.get_pos()
        mouse_change = self.last_mouse - pygame.math.Vector2(mouse_pos)
        pygame.mouse.set_pos(w/2, h/2)
        self.last_mouse = pygame.mouse.get_pos()

        self.rotate(-mouse_change.x * 0.1, mouse_change.y * 0.1)

        self.camera_path()

        keys = pygame.key.get_pressed()

        if keys[pygame.K_a]:
            self.x_angle += pi / 180

        if keys[pygame.K_d]:
            self.x_angle -= pi / 180

        if keys[pygame.K_w]:  # Move up
            if self.eye[1] < 8:
                self.eye[1] += 0.6
        if keys[pygame.K_s]:  # Move down
            if self.eye[1] > -8:
                self.eye[1] -= 0.6