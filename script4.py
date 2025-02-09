import pygame
import requests

# Initialize Pygame and Joystick
pygame.init()
pygame.joystick.init()

# Arduino Server IP Address
ip_address = "http://192.168.4.1"

# Button mappings
BUTTON_RIGHT = 0   # Move right
BUTTON_BACKWARD = 1  # Move backward
BUTTON_FORWARD = 2   # Move forward
BUTTON_LEFT = 3   # Move left
BUTTON_SHOOT = 7  # Shoot
BUTTON_TALONADE = 8

# Connect to the controller
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
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.JOYBUTTONDOWN:
            if event.button == BUTTON_RIGHT:
                try: 
                    requests.get(f"{ip_address}/forward")
                except:
                    pass
                print("Forward")
            elif event.button == BUTTON_BACKWARD:
                try: 
                    requests.get(f"{ip_address}/right")
                except:
                    pass
                print("Backward")
            elif event.button == BUTTON_FORWARD:
                try:
                    requests.get(f"{ip_address}/left")
                except:
                    pass
                print("Right")
            elif event.button == BUTTON_LEFT:
                try: 
                    requests.get(f"{ip_address}/backward")
                except:
                    pass
                print("Left")
            elif event.button == BUTTON_SHOOT:
                try: 
                    requests.get(f"{ip_address}/shoot")
                except:
                    pass
                print("Shoot")

            elif event.button == BUTTON_TALONADE:
                try:
                    requests.get(f"{ip_address}/talo")
                except:
                    pass
                print("Talo")

        elif event.type == pygame.JOYBUTTONUP:
            try:
                requests.get(f"{ip_address}/stop")
            except:
                pass
            print("Stop")

pygame.quit()
