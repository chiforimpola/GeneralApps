
from sys import argv
from filesSearch import getByType
import pygame

#dir
#type
#outputimage

if len(argv) < 4:
	print ('<dir>\n<type>\n<output_file>')
else:
	idir = 1
	itype = 2
	ioutput = 3
	imgs = getByType (argv[itype], argv[idir], True)
	imgsHandle = []
	height = 0
	width  = 0
	
	for i in imgs:
		imgsHandle.append (pygame.image.load(i))
	for i in imgsHandle:
		height += i.get_size()[1]
		if i.get_size()[0] > width:
			width = i.get_size()[0]
	output = pygame.Surface ( (width, height) )
	x = y = 0
	for i in imgsHandle:
		output.blit (i, (x, y, 0, 0))
		y += i.get_size()[1]
	pygame.image.save(output, argv[ioutput])
	
	print 'Image saved: ' + argv[ioutput]
