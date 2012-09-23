
import sys
from pygame import display, image, draw, event, init, mouse, QUIT, MOUSEBUTTONDOWN, KEYDOWN
from pygame.event import *
from term import Color
from time import sleep


def main ():
	term = Color ()
	init()
	screen = display.set_mode ( (800, 600) )
	finished = False
	sprDimension = 20
	R = 255
	G = 0
	B = 0
	RedKey = 114
	GreenKey = 103
	BlueKey = 98
	UP = 273
	DOWN = 274
	colorFocus = ''
	
	while not finished:
		for ev in event.get ():
			if ev.type == QUIT:
				finished = True
			elif ev.type == MOUSEBUTTONDOWN:
				if mouse.get_pressed ()[0] == 1:
					draw.rect (screen, (R, G, B), (mouse.get_pos()[0], mouse.get_pos()[1], sprDimension, sprDimension), 0)
			elif ev.type == KEYDOWN:
				print ev.key
				if ev.key == RedKey:
					colorFocus = 'r'
				elif ev.key == GreenKey:
					colorFocus = 'g'
				elif ev.key == BlueKey:
					colorFocus =  'b'
				elif ev.key == UP and colorFocus != '':
					if colorFocus == 'r':
						if R == 255:
							R = 0
						else:
							R += 1
							
					if colorFocus == 'g':
						if G == 255:
							G = 0
						else:
							G += 1
							
					if colorFocus == 'b':
						if B == 255:
							B = 0
						else:
							B += 1						
							
				elif ev.key == DOWN and colorFocus != -1:
					print ev.key
					
					if colorFocus == 'r':
						if R == 0:
							R = 255
						else:
							R -= 1
							
					if colorFocus == 'g':
						if G == 0:
							G = 255
						else:
							G -= 1
							
					if colorFocus == 'b':
						if B == 0:
							B = 255
						else:
							B -= 1
		
		print R, G, B
		
		draw.rect (screen, (R, G, B), (screen.get_width()-sprDimension, 0, screen.get_width(), sprDimension), 0)
		display.update ()
		draw.rect (screen, (0,0,0), screen.get_rect(), 0)
		
		sleep (0.4)
		
if __name__ == "__main__":
	main()
