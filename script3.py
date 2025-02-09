import pygame
import requests

# Initialize Pygame and Joystick
pygame.init()
pygame.joystick.init()

ip_address = "http://192.168.4.1"


def move(left_speed, right_speed):
    left_speed = int(left_speed * 255)
    right_speed = int(right_speed * 255)

    print(left_speed,right_speed)

    if abs(left_speed) < 15 and abs(right_speed) < 15:
        requests.get(f"{ip_address}/stop")
    else:
        requests.get(f"{ip_address}/move?left={left_speed}&right={right_speed}")


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
    events = pygame.event.get()

    for event in events:
        if event.type == pygame.QUIT:
            running = False

    speed = -joystick.get_axis(1)  # Forward/backward
    turn = joystick.get_axis(0)  # Left/right

    left_speed = speed + turn
    right_speed = speed - turn

    left_speed = max(min(left_speed, 1), -1)  # Clamp values between -1 and 1
    right_speed = max(min(right_speed, 1), -1)

    move(left_speed, right_speed)

pygame.quit()
