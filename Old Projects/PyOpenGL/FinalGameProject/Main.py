from pygame.locals import *

from LoadMesh import *
from Camera import *
from Sun import *
from Enemy import *
from Bullet import *
from RandomPos import *
import random

pygame.init()

# project settings
screen_width = 1920
screen_height = 1080
background_color = (0.3, 0.3, 0.3, 1)
drawing_color = (1, 1, 1, 1)

start_time = pygame.time.get_ticks()
time_particle2 = 0

screen = pygame.display.set_mode((screen_width, screen_height), DOUBLEBUF | OPENGL)
pygame.display.set_caption('OpenGL in Python')

#mesh = LoadMesh("donut.obj", GL_LINE_LOOP)
camera = Camera()   #camera object
sun = Sun(5)        #sun object with mass parameter for force calculation

#Variables
shells = []     #array for gun objects
enemies = []    #array for enemies
bullets = []
clock = pygame.time.Clock()
counter = 0
mouseReleased = True

def light():
    # Adjusted ambient, diffuse, and specular light settings
    ambient_light = [0.1, 0.1, 0.1, 1.0]  # Lower ambient intensity for subtle indirect light
    diffuse_light = [0.8, 0.8, 0.5, 1.0]  # Warm, softer diffuse light for better realism
    specular_light = [1.0, 1.0, 1.0, 1.0]  # Strong white specular light for reflections

    # Position the light slightly offset for a better angle on shadows and highlights
    light_pos = [2.0, 4.0, 1.0, 1.0]

    # Set up the shading model and clear colors
    glShadeModel(GL_SMOOTH)
    glClearColor(0.1, 0.1, 0.1, 1.0)  # Black background
    glClearDepth(1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_CULL_FACE)
    glFrontFace(GL_CCW)

    # Enable lighting and set the light parameters
    glEnable(GL_LIGHTING)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light)
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light)
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos)

    # Enable the light source and set color material properties
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)

def initialise():
    glClearColor(background_color[0], background_color[1], background_color[2], background_color[3])
    glColor(drawing_color)

    light()
    # projection
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60, (screen_width / screen_height), 0.1, 1000)

def init_camera():
    # model view
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    glTranslatef(0, 0, 0)
    glViewport(0, 0, screen.get_width(), screen.get_height())
    glEnable(GL_DEPTH_TEST)
    camera.update(screen.get_width(), screen.get_height())

def draw_world_axes():
    glPushMatrix()

    glColor4f(1, 1, 1, 1)  # Set color to yellow
    sphere = gluNewQuadric()  # Create a new quadriceps object
    gluSphere(sphere, 0.01, 5, 5)

    glPopMatrix()


def draw_crosshair():
    # Save current projection and modelview matrix
    glMatrixMode(GL_PROJECTION)
    glPushMatrix()
    glLoadIdentity()
    glOrtho(-1, 1, -1, 1, -1, 1)  # Set orthographic projection

    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    glLoadIdentity()

    # Draw the crosshair lines in NDC
    glDisable(GL_DEPTH_TEST)  # Disable depth test for the 2D overlay
    glLineWidth(2)  # Set line thickness
    glColor3f(1.0, 1.0, 1.0)  # Set color (white)

    glBegin(GL_LINES)
    # Horizontal line
    glVertex2f(-0.013, 0.0)
    glVertex2f(-0.008, 0.0)

    glVertex2f(0.008, 0.0)
    glVertex2f(0.013, 0.0)
    # Vertical line
    glVertex2f(0.0, -0.02)
    glVertex2f(0.0, -0.01)

    glVertex2f(0.0, 0.01)
    glVertex2f(0.0, 0.02)
    glEnd()

    glEnable(GL_DEPTH_TEST)  # Re-enable depth testing

    # Restore previous projection and modelview matrix
    glMatrixMode(GL_MODELVIEW)
    glPopMatrix()

    glMatrixMode(GL_PROJECTION)
    glPopMatrix()

def display():
    global rot
    global start_time
    global time_particle2
    global counter
    time_particle = 1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    init_camera()
    sun.draw()
    draw_world_axes()


    current_time = pygame.time.get_ticks()
    elapsed_time = (current_time - start_time)

    if elapsed_time >= 100:
        start_time = pygame.time.get_ticks()
        time_particle += 1
        time_particle2 += 1


    if time_particle >= 2 and len(enemies) < 20:

        enemy = Enemy()
        enemies.append(enemy)
        time_particle = 0

    enemies_to_remove = []

    # Draw enemies
    for enemy in enemies:
        if enemy.pos.length() < 1.5:
            enemies_to_remove.append(enemy)
        else:
            for shell in bullets:
                if (enemy.pos - shell.pos).length() < 2:
                    enemies_to_remove.append(enemy)
        enemy.update()

    for enemy in enemies_to_remove:
        if enemy in enemies:
            enemies.remove(enemy)

    for shell in bullets:
        shell.update()
        shell.draw()
        if  shell.pos.length() > 500:
            bullets.remove(shell)


    # Draw shells
    for shell in shells:
        shell.update()

    # Draw crosshair at the center of the screen
    draw_crosshair()

done = False
initialise()
pygame.event.set_grab(True)
pygame.mouse.set_visible(False)

while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.mouse.set_visible(True)
                pygame.event.set_grab(False)
            if event.key == pygame.K_SPACE:
                pygame.mouse.set_visible(False)
                pygame.event.set_grab(True)
            if event.key == pygame.K_x:
                for enemy in enemies:
                    enemy.move += pygame.math.Vector3(0,0,2)

            if event.key == pygame.K_z:
                for i in range(5):
                    vec3 = pygame.math.Vector3(vec_perpendicular_to_center())
                    gun = Gun(vec3, sun)
                    shells.append(gun)



    mouse_buttons = pygame.mouse.get_pressed()
    if time_particle2 > 2: # equal to 200ms
        if mouse_buttons[0]:  # Left mouse button is pressed
            bullet = Bullet(camera.eye + camera.forward.normalize(),
                            camera.forward.normalize())
            bullets.append(bullet)
            time_particle2 = 0

    display()
    pygame.display.flip()
    clock.tick(60)
pygame.quit()