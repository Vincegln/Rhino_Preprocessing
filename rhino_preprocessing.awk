awk '/dias_aorta/ {flag=1}; /dias_inf_vc/ {flag=0}; 
{if(flag) {print > "./Done" FILENAME}}' *.nrb
