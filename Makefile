make: vaccineMonitor.c skipList.c list.c citizen.c
	gcc -o vaccineMonitor vaccineMonitor.c citizen.c list.c skipList.c