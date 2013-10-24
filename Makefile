all:
	gcc -o idle idle.c -lX11 -lXss

clean:
	rm idle

install:
	cp idle "/usr/local/bin/"
	cp powersave.sh "/usr/local/bin"
