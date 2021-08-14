obj-m += char_DD_open_close.o
KDIR=/lib/modules/$(shell uname  -r)/build/
PWD:=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc application.c -o apps
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm apps
