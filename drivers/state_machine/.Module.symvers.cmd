cmd_/home/sslim/troubleshooting_project/drivers/state_machine/Module.symvers := sed 's/\.ko$$/\.o/' /home/sslim/troubleshooting_project/drivers/state_machine/modules.order | scripts/mod/modpost -m -a  -o /home/sslim/troubleshooting_project/drivers/state_machine/Module.symvers -e -i Module.symvers   -T -
