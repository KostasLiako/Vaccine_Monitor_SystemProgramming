ΕΡΓΑΣΙΑ 1
	ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ ΣΥΣΤΗΜΑΤΟΣ 
			
Η εκφώνηση της εργασίας βρίσκετε [εδώ](https://github.com/KostasLiako/Vaccine_Monitor_SystemProgramming/blob/master/hw1-spring-2021.pdf)			



```
# Εντολή Μεταγλώτισσης:
make ή gcc -o vaccineMonitor vaccineMonitor.c citizen.c list.c skipList.c

# Εντολή Εκτέλεσης:
./vaccineMonitor -c inputFile.txt -b 100Kbytes

```



• Δομές που υλοποιήθηκαν: 
⁃ Bloom Filter .
⁃ Bloom List: Λίστα από Bloom Filters για τον κάθε ιό ξεχωριστά.
⁃ List: Απλή συνδεδεμένη λίστα για την αποθήκευση τον στοιχείων Country,Virus,Vaccination_Status για την αποφυγή επανάληψης πληροφορίας.
⁃ Hash Table: Για την αποθήκευση των εγγραφων.
⁃ Skip List.
⁃ Λίστα από Skip Lists: Για την αποθήκευση των skip list  για τον καθε ιό. 
										
• Υλοποίηση: 

 Αρχικά το πρόγραμμα ανοίγει το αρχείο inputFile.txt που έχει δωθεί ως όρισμα στην γραμμή εντολών. Επίσης μετατρέπει και το bloom size που δίνεται στην γραμμή εντολών σε νούμερο (δλδ 100Kbytes = 100.000 bytes).

Στην συνέχεια ξεκινάει η ανάγνωση των Records γραμμή-γραμμή από το αρχείο. Τα εκάστοτε πεδία κάθε Record τα διαχωρίζουμε μέσω τησ συνάρτησης strtok και τα αποθηκεύουμε στις αντίστοιχες μεταβλητές. 
Τα πεδία Country, Virus, Vaccination_Status(αν ειναι εμβολιασμένος η όχι) τα αποθηκεύουμε στην αντίστοιχη λίστα, αφου πρώτα γίνει ο έλεγχος αν υπάρχει ήδη, ετσι ώστε μην έχουμε επανάληψη πληροφορίας και μέσω Pointer κάθε πολίτης να δείχνει στα στοιχεία του.

Τέλος ο εκάστοτε πολίτης αποθηκεύεται στο Hash Table συναρτήση του αριθμού μητρώου του. 
Στην περίπτωση που δυο εγγραφές είναι inconsistent τότε απορρίπτεται η δεύτερη.

Στην συνέχεια αυξάνεται ο πληθυσμός της αντίστοιχης χώρας με την εγγραφή καθώς και το πεδίο του του αντίστοιχου πίνακα με τις ηλικιακές ομάδες.



• Εισαγωγή το Bloom Filter.

Μετά την παραπάνω διαδικασία γίνεται η εισαγωγή στο αντίστοιχο bloom filter. Αν δεν υπάρχει bloom filter για τον αντίστοιχο ιό. Δημιουργείται και αρχικοποιείται εισάγοντας το bloom size καθώς και ένα pointer στον ιό που αναφέρεται.Τελός εισάγεται στην λίστα που έχουμε σημιουργήσει με τους bloom filters.
Αν η πολίτης είναι εμβολιασμένος τότε καλείται η συνάρτηση και γίνεται εισαγωγή στο Bloom Filter.

• Εισαγωγή στην Skip List.
•        Μετά την εισαγωγή στον Bloom Filter γίνεται η εισαγωγή τπυ Record στην αντίστοιχη Skip List. Παραμοίως με απο πάνω αν δεν υπαρχει η Skip List για τομν εκάστοτε ιό δημιουργείται και αρχικοποιείται και εισα΄γεται στην λίστα με τις Skip lists,με την διαφορά ότι εδώ έχουμε δύο skip list για τον κάθε ιό. Μία για τους εμβολιασμένους κατα του ιού και μια για τους μη εμβολιασμένους.Τέλος γίνεται η εισαγωγή στην Skip List όπως γνωρίζουμε σύμφωνα με την θεωρία που γνωρίζουμε για τις Skip List.

• Ερωτήματα.

⁃ /vaccineStatusBloom: Στο συγκεκριμένο ερώτημα δίνουμε από το πληκτρολόγιο τον id και τον ιό που θέλουμε και ελέγχουμε αν ο αντίστοιχος πολίτης είναι πιθανός εμβολιασμένος η όχι. Αν τον Input είναι λάθος (δεν βαλουμε id ή virus) το πρόγραμμα θα βγάλει ERROR και θα τερματίσει.Στην συνέχεια εκτελείται η συνάρτηση searchBloom() και μας δίνει το αποτέλεσμα.
<br />
⁃ /vaccineStatus citizenID virusName:  Στο συγκεκριμένο ερώτημα προσπελαύνουμε την VaccinatedSkipList του συγκεκριμένου ιού μέσω της συνάρτησης searchSkipList() και σύμφωνα με την θεωρία της αναζήτης σε μία skip list. Αν βρεθέι μας εκτυπώνεται "VACCINATED ON" και την ημερομηνία εμβολιασμού.<br />
⁃ /vaccineStatus citizenID: Στο συγκεκριμένο ερώτημα προσπελαύνουμε όλες τις skip List για όλους τους ιούς και αν βρούμε τον συγκεκριμένο πολίτη εκτυπώνουμε το virusName αν είναι εμβολιασμένος και πότε εμβολιάστηκε.<br />
⁃ /populationStatus: Στο συγκεκριμένο ερώτημα όταν δίνεται country σαν όρισμα αναζητούμε στην αντίστοιχη skip List του ιού πόσα άτομα απο την συγκεκριμένη χώρα έχουν εμβολιαστεί μέσα στο διάστημα στο οποίο δώσαμε. Τέλος εκτυπώνεται ο αριθμός των ατόμων που εμβολιάστηκαν καθώς και το ποσοστό αυτού επι του συνολικού πλυθυσμού.Η παραπάνω διαδικασία δίνεται στην συναρτηση populationStatus() και η σύγκριση αν βρίσκεται μέσα στο διάστημα στην συνάρτηση compareDates(). Αν δεν δοθεί όρισμα country η παραπάνω διαδικασία γινεται για όλες τις χώρες που βρίσκονται στην λίστα countries.<br />
⁃ /popStatusByAge: Στο συγκεκριμένο ερώτημα ακολουθείται σχεδόν η ίδια διαδικασία με την /populationStatus με την διαφορά οτι πλέον οι εμβολιασμένοι πολίτες που βρίσκουμε στην αντίστοιχη Skip List ταξινομούνται ανάλογα την ηλικία τους και στο τέλος βγαίνει ποσοστό επι του συνόλου της ηλικιακής τους ομάδας της αντίστοιχης χώρας.<br />
⁃ /insertCitizenRecord: Στο συγκεκριμένο ερώτημα εισάγουμε μία καινούργια εγγραφή στο πρόγραμμα μας. Ακολουθείται η ίδια διαδικασία με την αρχή και την ανάγνωση του αρχείου και την αποθήκευση των εγγραφών. Παρομοίως και εδώ αν δώσουμε για input μια inconsistent εγγραφή αυτή απορρίπτεται. Σαυτό το ερώτημα όμως γίνεται ο έλεγχος αν ο πολίτης όπου εισάγουμε βρίσκεται στην noVaccinatedList του αντιστοιχου ιού και μετά θελουμε να τον περάσουμε ως εμβολιασμένο. Σαυτην την περίπτωση ο πολίτης διαγράφεται από την nonVaccinated skip list του ιου και εισάγεται στην Vaccinated.<br />
⁃ /vaccinateNow: Στο συγκεκριμένο ερώτημα ακολουθείται παρόμοια διαδικασία με την /insertCitizenRecord με την διαφορά οτι ο πολιτής που είσαγουμε είναι εμβολιασμένος κατα του αντίστοιχου ιού και με ημερομηνία εμβολιασμού την τωρινή ημερομηνία. Για να βρούμε την τωρινή ημερομηνία χρησιμοποιούμε την βιβλιοθήκη της C "time.h".<br />
⁃ /list-nonVaccinated-Persons: Στο συγκεκριμένο ερώτημα προσπελαύνουμε την nonVaccinated skip list του συγκεκριμένου ιού και εκτυπώνουμε ολές τις εγγραφές που υπάρχουν μαζί με τα υπόλοιπα στοιχεία τους.<br />
⁃ /exit: Απελευθερώνουμε την μνήμη όπου δεσμεύσαμε και τερματίζεται το πρόγραμμα. <br />
	
	
