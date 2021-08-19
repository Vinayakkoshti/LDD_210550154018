obj-m:=kern.o
KDIR=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o read app_read.c 
clean:
	make -C $(KDIR) M=$(PWD) clean	
	rm -rf read
