cmd_/home/julia/Documents/OS_6/lab_04/part_02/Module.symvers := sed 's/\.ko$$/\.o/' /home/julia/Documents/OS_6/lab_04/part_02/modules.order | scripts/mod/modpost -m -a  -o /home/julia/Documents/OS_6/lab_04/part_02/Module.symvers -e -i Module.symvers   -T -
