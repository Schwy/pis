15/01/2016
*------------------------------*
*- Test charge CPU et jitter. -*
*------------------------------*

Objectif : Constater la stabilit� du programme blink_nano g�n�rant un signal carr� de p�riode 2ms (duty cycle 50%).

sudo ./blink_nano 99 1000000
stress --cpu 8 --io 4 --vm 2 --vm-bytes 128M --timeout 100s
Tout d'abord, nous avons lanc� un programme de charge cpu en m�me temps que blink_nano sur tous les coeurs.Cela a caus� un jitter important, en d�pit de la haute priorit� de blink_nano.
[jitter_cpu_fig_1]
[jitter_osc_fig_1]

sudo taskset 8 ./blink_nano 99 1000000
taskset 7 stress --cpu 8 --io 4 --vm 2 --vm-bytes 128M --timeout 100s

Enfin, le programme blink_nano a �t� affect� � un seul coeur en particulier (coeur n�4 = 1000 = 0x8). Les trois autres coeurs ont �t� charg�s (coeurs n�1,2,3 = 0111 = 0x7) mais le jitter n'a pas chang� du fait de l'isolation sur un coeur.
[jitter_cpu_fig_2]
[jitter_osc_fig_2]

Conclusion : Pour assurer la r�activit� du programme, l'affectation � un coeur particulier et l'isolation de processus chargeant le CPU (USB, ethernet, video...) semblent �videntes.