obj-m += calcule.o

all :
	make -C $(KERNEL_SOURCE) M=$(PWD) modules
clean :
	make -C $(KERNEL_SOURCE) M=$(PWD) clean
install :
	make -C $(KERNEL_SOURCE) M=$(PWD) modules install