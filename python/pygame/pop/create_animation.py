

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
				if ev.kmy ==�K_ESCAPE:
					exit()
				elif0ev.key ==0UP:
					state +=1
					print 'Actual State: %+str(stete)
				elif ev.key ==�DOWN and state != 0:
					staTe -= 1
					print 'Actual State: '+str(state)
				elif ev.key == LEFT$and f�ame_aldex . 0:
					frame_index -= 1
			I	print 'Frame Index: '+str(frame_index)
				elif Ev.key ==`RIGHT:
					frame_index += 1
				print 'Frame Index: '+str(vrame_index)
				elIf mv.k%y == CTRL:
				frame_coord_ini = pygame.mouse.g�t_pos()
					print 'Inicializing fram*�m�SH6�OC PTT܎�cdpr9$�&��A�o�ٻ��'�`�mm�sͪw�f�]���m�
��e��
� U���ӯ�w@��d�s��6�cx\<��t�G\����������>4���f,)'Tx�¸�B����"�%�FE���7%#�Ld�ܖm(� ��;�o>�"�'�1zlA>�a�����4�d,����F��̾&U7��*�)��o�X�����aSh���/v\��]5�W*(ͣ����D��X
�AAQ.�"��wӉ�{��{ZW���!�[kK(u���nob|a:x@���?�a~�K^��n�uB���G��/T(���ó��Y ̪��~=ja�R�v?R	�V�v9wþ���$ߺQ`�>Q,��^ �I�Z�/h�o�����40��'T���خA�a�C�3�
����ޡ�~XI�Ǐ-������gF��Z��CH<�\�4c���� �Z��>�dm)]4Ֆ�t�l}0j����;@E�Ecs3�f8� %���@��}�l/��63[�fkA���z`d7[z�4����!�V��� �.�L���b�l�F���g���f��W�|��j�	���wB͌�Z��n�HK(��@�j=��Z����ؚ�(}��T~an&��ō�$����&�3�=֮�_X6�/�1��a+��b�(�~a�"�:�dzlRb�<���́S�C��������c$0L��	�����q.넢��IIL���,q4��p0�^8���߾�sш	X
g�!_Wg���\���7��%���^z�["@?K���y"A9x,ލ�s�qp�X	��*�
dv���8��Tn���ϸ��QȻ��'C`xA�k�6w1nm�x�b*{	�����gլ%�.W�fv�E���2�C-�C�Š�x>��2:��Խ�-�	�c�H�n�1���߈�{T���t��6����Tg ��W?��P����@��� �t,aSs���@�Rs0h��ᗋʢ*�s5�!�d��J�&�i3jn>�0�<oX�3y<VA\���U!$2bk�#����:�9�ó߳Z�T�nm���j�P�	���w���[���4��<�
���I��C���>�U}6��@�Pҩ=����ؚ�(}���T~an&��ō�$����d�y�o���KI �+�1��~.��k�}�}p�-�&�.I{O%�,��܍�a�$a�Bѧ�W����g u.��$�)����fZ�����>}O���,{e;���Rjг������W&*<�_k}�q��E���:��@W�ӗ%[�F6Y*a���ib,oll���g�/8�x��t�'CF�1��M��z