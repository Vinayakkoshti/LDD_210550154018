cmd_/home/pi/Desktop/Linux_Device_Driver/module_export/q2_modprobe/Module.symvers := sed 's/ko$$/o/' /home/pi/Desktop/Linux_Device_Driver/module_export/q2_modprobe/modules.order | scripts/mod/modpost -m -a   -o /home/pi/Desktop/Linux_Device_Driver/module_export/q2_modprobe/Module.symvers -e -i Module.symvers   -T -
