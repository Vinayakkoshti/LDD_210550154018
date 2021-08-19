obj-m:=jiffies.o
KDIR=/lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o apps application.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf apps
