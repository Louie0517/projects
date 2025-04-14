import pygame
import sys

pygame.init()

windowScreen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("Calculator")
clock = pygame.time.Clock()

#colors
grey = (100, 100, 100, 128)
dark = (190, 110, 0, 19)
transparent_dark = (190, 110, 0, 32)
white = (255, 255, 255)
black = (0, 0, 0)
blackishGrey = (15, 15, 15)
red = (255, 0, 0, 80)
transparent_red = (255, 0, 0, 100)
midnight_blue = (20, 24, 45)
midnight_blue_transparent = (20, 24, 45, 150)
ash_grey = (200, 200, 200, 128)


buttons = [
    ['7', '8', '9', '/'],
    ['4', '5', '6', '*'],
    ['1', '2', '3', '-'],
    ['0', 'C', '=', '+']
]

def border(surface, color, radius, rect):
    x, y, width, height = rect
    
    #body
    pygame.draw.rect(surface, color, (x + radius, y, width - 2 * radius, height))
    pygame.draw.rect(surface, color, (x, y + radius, width, height - 2 * radius))
    #corners
    pygame.draw.circle(surface, color, (x + radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + width - radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + radius, y + height - radius), radius)
    pygame.draw.circle(surface, color, (x + width - radius, y + height - radius), radius)

def screen_for_calculator(surface, color, radius, rect, text_to_show):
    x, y, width, height = rect
    
    #body
    pygame.draw.rect(surface, color, (x + radius, y, width - 2 * radius, height))
    pygame.draw.rect(surface, color, (x, y + radius, width, height - 2 * radius))
    
    #corners
    pygame.draw.circle(surface, color, (x + radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + width - radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + radius, y + height - radius), radius)
    pygame.draw.circle(surface, color, (x + width - radius, y + height - radius), radius)
    
    font = pygame.font.Font("C:/python_projects/font/Digital_7_itallic.ttf", 75)
    text = font.render(text_to_show, True, black)
    text_rect = text.get_rect(center=(x + width // 2, y + height// 2))
    
    if text_rect.right > x + width:
        text_rect.right = x + width
    if text_rect.bottom > y + height:
        text_rect.bottom = y + height
    if text_rect.left < x:
        text_rect.left = x
    if text_rect.top < y:
        text_rect.top = y
    
    
    surface.blit(text, text_rect)

    
           
def button_access(value):
    for row_index, rowButton in enumerate(buttons):
        for col_index, item in enumerate(rowButton):
            if item == value:
                return row_index, col_index
    return None
    
def buttons_for_calculator(surface, newColor, clickLabel, buttons, x, y, width, height, gap):
    font = pygame.font.SysFont(None, 40)
    for row_index, row in enumerate(buttons):
        for col_index, label in enumerate(row):     
            but_x = x + col_index * (width + gap)
            but_y = y + row_index * (height + gap)
            rect = pygame.Rect(but_x, but_y, width, height)
            
            button_surface = pygame.Surface((width, height), pygame.SRCALPHA)
            
            if label == clickLabel:
                 button_surface.fill(newColor)
                 if label in special_buttons:
                     button_surface.fill(transparent_red)
                 else:
                     button_surface.fill(newColor)
                 if label in clear_buttons:
                     button_surface.fill(midnight_blue_transparent)
            elif label in special_buttons:
                 button_surface.fill(red)
            elif label in clear_buttons:
                button_surface.fill(midnight_blue)
            else:
                 button_surface.fill(dark)
            
            surface.blit(button_surface, (but_x, but_y))
            pygame.draw.rect(surface, black, rect, 2)
            
            text = font.render(label, True, white)
            textIn_rect = text.get_rect(center=rect.center)
            surface.blit(text, textIn_rect)
   
new_label = None    
label_click_time = 0
highlight_duration = 300
special_buttons = ['=', '-', '*', '+', '/']   
clear_buttons = ['C'] 
current_input = ""
        
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
            
            
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                mouse_x, mouse_y = event.pos
                for row_index, rowButton in enumerate(buttons):
                    for col_index, item in enumerate(rowButton):
                        but_x = 200 + col_index * (80 + 6)
                        but_y = 200 + row_index * (80 + 6)
                        rect = pygame.Rect(but_x, but_y, 80, 80)
                        if rect.collidepoint(mouse_x, mouse_y):
                             new_label = item
                             label_click_time = pygame.time.get_ticks()
                             print(f"Button {item} clicked at ({mouse_x}, {mouse_y})")
                             if item == 'C':
                                 current_input = ""
                             elif item == '=':
                                 try:
                                     current_input = str(eval(current_input))
                                 except:
                                     current_input = "Error"
                             else:
                                current_input += item
                                
    if new_label is not None and pygame.time.get_ticks() - label_click_time > highlight_duration:
        new_label = None
                                 
            
    windowScreen.fill(ash_grey)

    border(windowScreen, blackishGrey, 10, (155,75, 446, 485))
    screen_for_calculator(windowScreen, grey, 10, (201, 110, 337, 80), text_to_show=current_input)
    buttons_for_calculator(windowScreen, transparent_dark, new_label, buttons, x = 200, y = 200, width = 80, height = 80, gap = 6)

    pygame.display.flip()

    clock.tick(6)