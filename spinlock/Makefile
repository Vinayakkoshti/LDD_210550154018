obj-m := spinlock.o
KDIR= /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o apps application.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf  apps
