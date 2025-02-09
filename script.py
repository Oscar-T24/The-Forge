import pygame

# Initialize Pygame and Joystick
pygame.init()
pygame.joystick.init()

# Set window size and font
WIDTH, HEIGHT = 500, 500
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Switch Pro Controller Live Data")
font = pygame.font.Font(None, 30)

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
    screen.fill((30, 30, 30))  # Dark background
    events = pygame.event.get()

    for event in events:
        if event.type == pygame.QUIT:
            running = False

    # Display joystick axis data
    axis_texts = []
    for i in range(joystick.get_numaxes()):
        axis_value = joystick.get_axis(i)
        axis_texts.append(f"Axis {i}: {axis_value:.2f}")

    # Display button presses
    button_texts = []
    for i in range(joystick.get_numbuttons()):
        button_state = joystick.get_button(i)
        button_texts.append(f"Button {i}: {button_state}")

    # Display hat (D-pad) positions
    hat_texts = []
    for i in range(joystick.get_numhats()):
        hat_value = joystick.get_hat(i)
        hat_texts.append(f"Hat {i}: {hat_value}")

    # Render all text to screen
    all_texts = axis_texts + button_texts + hat_texts
    for index, text in enumerate(all_texts):
        text_surface = font.render(text, True, (255, 255, 255))
        screen.blit(text_surface, (20, 20 + index * 30))

    pygame.display.flip()
    pygame.time.delay(50)  # Reduce CPU usage

pygame.quit()

# Bouton 0 : droite
# Bouton 1 : recule
# Bouton 2 : avance
# Bouton 3 : gauche
# Bouton 7 : shoot