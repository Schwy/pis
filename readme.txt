15/01/2016
*------------------------------*
*- Test charge CPU et jitter. -*
*------------------------------*

Objectif : Constater la stabilité du programme blink_nano générant un signal carré de période 2ms (duty cycle 50%).

sudo ./blink_nano 99 1000000
stress --cpu 8 --io 4 --vm 2 --vm-bytes 128M --timeout 100s
Tout d'abord, nous avons lancé un programme de charge cpu en même temps que blink_nano sur tous les coeurs.Cela a causé un jitter important, en dépit de la haute priorité de blink_nano.
[jitter_cpu_fig_1]
[jitter_osc_fig_1]

sudo taskset 8 ./blink_nano 99 1000000
taskset 7 stress --cpu 8 --io 4 --vm 2 --vm-bytes 128M --timeout 100s

Enfin, le programme blink_nano a été affecté à un seul coeur en particulier (coeur n°4 = 1000 = 0x8). Les trois autres coeurs ont été chargés (coeurs n°1,2,3 = 0111 = 0x7) mais le jitter n'a pas changé du fait de l'isolation sur un coeur.
[jitter_cpu_fig_2]
[jitter_osc_fig_2]

Conclusion : Pour assurer la réactivité du programme, l'affectation à un coeur particulier et l'isolation de processus chargeant le CPU (USB, ethernet, video...) semblent évidentes.