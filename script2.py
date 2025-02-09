import pygame
import requests

# Initialize Pygame and Joystick
pygame.init()
pygame.joystick.init()

ip_address = "http://192.168.4.1"

# Set window size and font
#WIDTH, HEIGHT = 500, 500
#screen = pygame.display.set_mode((WIDTH, HEIGHT))
#pygame.display.set_caption("Switch Pro Controller Live Data")
#font = pygame.font.Font(None, 30)

def deplacement(speed):
    # speed varie de -1 a 1 donc on le multiplie par 255 pour avoir une valeur entre -255 et 255
    speed = speed * 255
    if abs(speed) < 15:
        requests.get(f"{ip_address}/forward?speed={0}")
        requests.get(f"{ip_address}/backwards?speed={0}")
    elif speed > 0:
        requests.get(f"{ip_address}/forward?speed={255}")
        print("forward")
    elif speed < 0:
        requests.get(f"{ip_address}/backwards?speed={255}")
        print("backwards")

def rotation(speed):
    # speed varie de -1 a 1 donc on le multiplie par 255 pour avoir une valeur entre -255 et 255
    speed = speed * 255
    if abs(speed) < 15:
        requests.get(f"{ip_address}/right?speed={0}")
        requests.get(f"{ip_address}/left?speed={0}")
    if speed > 0:
        requests.get(f"{ip_address}/right?speed={255}")
        print("right")
    elif speed < 0:
        requests.get(f"{ip_address}/left?speed={255}")
        print("left")

# Connect joystick
if pygame.joystick.get_count() > 0:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print(f"Connected: {joystick.get_name()}")
else:
    print("No joystick detected!")
    pygame.quit()
    exit()

running = True
while running:
    #screen.fill((30, 30, 30))  # Dark background
    events = pygame.event.get()

    for event in events:
        if event.type == pygame.QUIT:
            running = False

    # Display joystick axis data
    axis_texts = []
    for i in range(joystick.get_numaxes()):
        axis_value = joystick.get_axis(i)
        if i == 0:
            #rotation(axis_value)
            pass
        if i == 1:
            deplacement(axis_value)
        #axis_texts.append(f"Axis {i}: {axis_value:.2f}")

    # Axis 0 : axe horizontal joystick gauche
    # Axis 1 : axe vertical joystick gauche
    # Axis 2 : axe horizontal joystick droit
    # Axis 3 : axe vertical joystick droit

pygame.quit()


# valeurs entre 0 et 255

#Axis 0 : axe horizontal joystick gauche
#Axis 1 : axe vertical joystick gauche
#Axis 2 : axe horizontal joystick droit
#Axis 3 : axe vertical joystick droit

#Button 0 : A