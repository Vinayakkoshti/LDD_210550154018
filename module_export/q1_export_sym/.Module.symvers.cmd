cmd_/home/pi/Desktop/Linux_Device_Driver/module_export/q1_export_sym/Module.symvers := sed 's/ko$$/o/' /home/pi/Desktop/Linux_Device_Driver/module_export/q1_export_sym/modules.order | scripts/mod/modpost -m -a   -o /home/pi/Desktop/Linux_Device_Driver/module_export/q1_export_sym/Module.symvers -e -i Module.symvers   -T -
