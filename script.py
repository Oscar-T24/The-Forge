import pygame

pygame.init()
pygame.joystick.init()

if pygame.joystick.get_count() > 0:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print(f"Connected: {joystick.get_name()}")

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.JOYAXISMOTION:
            print(f"Axis {event.axis} moved to {event.value}")
        elif event.type == pygame.JOYBUTTONDOWN:
            print(f"Button {event.button} pressed")
        elif event.type == pygame.QUIT:
            running = False
pygame.quit()
