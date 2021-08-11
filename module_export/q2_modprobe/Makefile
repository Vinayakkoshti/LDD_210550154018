obj-m += my_add.o average.o
KDIR=/lib/modules/$(shell uname  -r)/build/

install:
	make -C $(KDIR) M=$(PWD) modules_install
	depmod -a
clean:
	make -C $(KDIR) M=$(PWD) clean

