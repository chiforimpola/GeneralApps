
import sys
import os
import pygame
from pygame.locals import *
import filesSearch

if len (sys.argv) <= 1:
    print "Enter the images path!"
    sys.exit()

WIDTH  = 800
HEIGTH = 800
REFRESH = 100

UP    = 273
DOWN  = 274
RIGHT = 275
LEFT  = 276

media = []
file_index = 0
dir_index = 0
img = None
screen = None
DEBUG = False

def initEngine():
    pygame.init()
    pygame.font.init()


types = { "png", "jpg", "bmp" }
first = True
for i in sys.argv:
	if not first:
		media = filesSearch.getByType (types, i, True)
	if first:
		first = not first

if len (media) == 0:
	print "Nenhum arquivo com extensao encontrado!"
	print "Extensoes buscadas: "
	print types
	sys.exit()


initEngine()

def openAndUpdate(path):
	global img, screen
	print "Opening: " + path
	img = pygame.image.load (path)
	screen = pygame.display.set_mode((img.get_rect().width, img.get_rect().height))
	os.environ['SDL_VIDEO_WINDOW_POS'] = '%d,%d' % (0, 0)

openAndUpdate (media[file_index])

finished = False
while not finished:
    for event in pygame.event.get():
        if event.type  == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
            sys.exit ()

        elif event.type == KEYDOWN:
            #print event.key

            if event.key == LEFT:
				if file_index > 0:
					file_index -= 1
				else:
					file_index = len (media) - 1
				
				openAndUpdate (media[file_index])
                
            if event.key == RIGHT:
				if file_index < len (media) and file_index + 1 < len (media):
					file_index += 1
				else:
					file_index = 0
				
				openAndUpdate (media[file_index])

    screen.blit (img, img.get_rect())
    #pygame.draw.rect (screen, (255, 0, 0), (10, 10, 20, 20))
    pygame.display.update ()
    pygame.time.delay (REFRESH)

