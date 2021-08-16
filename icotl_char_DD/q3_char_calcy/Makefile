obj-m:=char_DD_calc.o
KDIR=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o AddDev AddDev.c
	gcc -o SubDev SubDev.c
	gcc -o MulDev MulDev.c
	gcc -o DivDev DivDev.c
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf AddDev
	rm -rf SubDev
	rm -rf MulDev
	rm -rf DivDev

