import random
from math import *

import pygame


def get_rand_num(from_r, to_r):
    return round(random.uniform(from_r, to_r), 2)


def vec_perpendicular_to_center():
    x = get_rand_num(-1, 1)
    y = get_rand_num(sqrt(1 - pow(x,2)), -sqrt(1 - pow(x,2)))

    zc = pow(1, 2) - (pow(x, 2) - pow(y, 2))

    if zc < 0:
        zc = -zc
    z = sqrt(zc)
    if random.randint(1, 2) == 1:
        z *= -1
    vector3 = pygame.math.Vector3(x*10, y*10, z*10)
    return vector3