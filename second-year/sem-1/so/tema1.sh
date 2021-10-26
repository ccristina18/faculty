#!bin/sh
opt=0
optiune=0

while [ opt!=0 ] 
do 

echo "--------------------"
echo "1.Iesire."
echo "2.Afisare: numele serverului, tipul sistemului de operare, versiunea bash-ului si calea curenta."
echo "3.Afisarea zilei saptamanii in care va fi Craciunul in acest an."
echo "4.Afisarea primelor 2 shell-uri instalate in sistem."
echo "5.Afisarea pentru toti utilizatorii din sistem a numelui de login, a user ID-ului si a directorului de home."
echo "6.Afisarea ultimelor linii incepand cu linia 9 din fisierul /etc/protocols folosing comanda tail."
echo "7.Afisare tip procesor si marimea cache-ului."
echo "8.Scrieti comanda ls care afiseaza toate numele de directoare din directorul /proc care nu reprezinta imaginea unui proces de disc."
echo "9.Sa se afiseze toate fisierele de log. Sa se creeze o functie care primeste ca si parametrii cititi de la tastatura un nume de fisier de log si un text, si care va cauta si afisa liniile care contin textul primit ca si parametru."
echo "-------------------"
echo " Optiunea dvs.: "
read opt
echo "--------------------"
case $opt in

1) exit 0;;

2) echo "Nume server: " $HOSTNAME
	echo "Tip sistem operare: " $OSTYPE
		echo "Versiunea bash: " $BASH_VERSION
			echo "Calea curenta: " $pwd
		pwd;;
3) echo "Craciunul va fi sarbatorit anul acesta: " 
	date --date='Dec 25 2021' +%A;;
4) echo "Primele 2 shell-uri instalate in sistem sunt: "
	head /etc/shells -n 3 |tail -n 2;;
5)awk -F: 'BEGIN {print "Utilizatorii din sistem:\n------------------------"} {print $1,$3,$6}' /etc/passwd;;
6) tail /etc/protocols -n 9;;
7) echo "Tip procesor: "  
	cat /proc/cpuinfo
	echo "Marimea cache-ului: " 	
		cat /proc/cpuinfo | grep cache;;
8)ls /proc |grep '[a-z]';;
9)echo "Alegeti o optiune: "
	echo "11.Afisarea tuturor fisierelor log."
	echo "22.Afisare fisiere log arhivate/curente"
	read optiune 
	case $optiune in
	
		11) ls /var/log ;;
		
		22) ls /var/log
		echo "Introduceti numele fisierului:"
			read fisier
		echo "Introduceti cuvantul cautat in fisierul log:"
			read cuvant
		echo $fisier >nume.txt
			if [ $(grep '.gz' nume.txt) ]
				then
			sudo gunzip -c /var/log/$fisier | grep $cuvant
				else cat /var/log/$fisier | grep $cuvant
			fi ;;
		
	esac
	esac
	done
	done
		
		
