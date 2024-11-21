default:
	gcc -O1 -g -DDEBUG -oCUMB terminal-graphics/Graphics.c terminal-graphics/ansi-terminal/Ansi.c *.c
	./CUMB