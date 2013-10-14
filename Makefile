all:
	gcc -o idle idle.c -lX11 -lXss

clean:
	rm idle

install:
	sudo cp idle /bin/
