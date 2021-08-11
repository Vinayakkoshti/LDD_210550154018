obj-m += q3_calcy_param.o
KDIR=/lib/modules/$(shell uname  -r)/build/
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
