obj-m += char.o
KDIR=/lib/modules/$(shell uname  -r)/build/
PWD:=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc application.c -o app1
	gcc application2.c -o app2

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm app1 app2
