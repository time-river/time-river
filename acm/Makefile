dir=$(shell pwd)
build:
	gcc main.c -o test -fno-asm -O2 -Wall -std=c99 -DONLINE_JUDGE
t:
	$(dir)/test
clean:
	rm -rf $(dir)/test
