

import pygame
from pygame.locals import *
from sys import argv

#caminho da imagem
#arquivo de saida

if len (argv) < 5:
	print 'parametros'
	print '<PathToImageSource>\n<PathToImage>\n<InitialState>\n<PathToOutputFile>'
else:
	ispr = 1
	ipath_to_image = 2
	iinitial_state = 3
	ioutput = 4
	spr = pygame.image.load (argv[ispr])
	sc = pygame.display.set_mode( (spr.get_width(), spr.get_height()) )
	mouse_coord = aux_mouse_coord = (0, 0)
	output = open(argv[ioutput], 'w')
	output.write('\n$'+argv[iinitial_state])
	output.write('\nc255, 0, 255')
	output.write('\np'+argv[ipath_to_image])
	frame_coord_ini = (0, 0)
	frame_w = frame_h = 0
	frame_index = 0
	frame_delay = 500
	state = 0
	frame = 0
	SHIFT = 304
	CTRL = 306
	ENTER = 13
	UP = 273
	DOWN = 274
	RIGHT = 275
	LEFT = 276
	BUTTON_STATE = 52
	BUTTON_FRAME = SHIFT
	BUTTON_DELAY = 49
	BUTTON_PATH = 112
	BUTTON_KEYCOLOR = 308
	BUTTON_DELAY_DOWN = 44
	BUTTON_DELAY_UP = 46
	
	while True:
		sc.fill ((0,0,0))
		for ev in pygame.event.get():
			if ev.type == KEYDOWN:
				if ev.key == K_ESCAPE:
					exit()
				elif ev.key == UP:
					state +=1
					print 'Actual State: '+str(state)
				elif ev.key == DOWN and state != 0:
					state -= 1
					print 'Actual State: '+str(state)
				elif ev.key == LEFT and frame_index > 0:
					frame_index -= 1
					print 'Frame Index: '+str(frame_index)
				elif ev.key == RIGHT:
					frame_index += 1
					print 'Frame Index: '+str(frame_index)
				elif ev.key == CTRL:
					frame_coord_ini = pygame.mouse.get_pos()
					print 'Inicializing frame capture...'
					print 'Initial Coord: ('+str(frame_coord_ini[0])+','+str(frame_coord_ini[1])+')'
				elif ev.key  == BUTTON_STATE:
					print 'Writing to output $'+str(state)
					output.write('\n$'+str(state))
				elif ev.key == BUTTON_DELAY_UP:
					frame_delay += 10
					print 'Frame Delay: '+str(frame_delay)
				elif ev.key == BUTTON_DELAY_DOWN and frame_delay-10>0:
					frame_delay -= 10
					print 'Frame Delay: '+str(frame_delay)
				elif ev.key == BUTTON_FRAME and pygame.mouse.get_pos() != frame_coord_ini:
					frame_w = pygame.mouse.get_pos()[0] - frame_coord_ini[0]
					frame_h = pygame.mouse.get_pos()[1] - frame_coord_ini[1]
					print 'Writing to output frame values'
					print '('+str(frame_coord_ini[0])+','+str(frame_coord_ini[1])+')'
					print 'W: '+str(frame_w)+'\nH: '+str(frame_h)
					output.write('\n%'+str(frame_coord_ini[0])+', '+str(frame_coord_ini[1])+', ' + str(frame_w)+ ', '+ str(frame_h))
					print 'Writing to Output: !'+str(frame_delay)
					output.write('\n!'+str(frame_delay))
				
				#else: print ev.key
			else:
				mouse_coord = pygame.mouse.get_pos()
				#print ev.type
		
		if mouse_coord != aux_mouse_coord:
			aux_mouse_coord = mouse_coord
			print mouse_coord
		
		sc.blit (spr, spr.get_rect())
		pygame.display.update()
		pygame.time.delay (30)
	output.close()
	print 'Output closed!'
