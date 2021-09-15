#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citizen.h"
#include "list.h"
#include "skipList.h"
#include <time.h>

#define K 16

int main(int argc, char *argv[])
{

    char buff[255];
    char day[255];
    char *id;
    char *name;
    char *surname;
    char *country;
    char *citizenAge;
    char *virus;
    char *vacc;
    char *date;
    int age;
    long hash;
    int bloomSize;
    char *bloomString;
    int idExist;
    int virusExist;
    int vaccinated;
    int countryExist;
    char *cmd1;
    Citizen *citizen;
    HashTable *ht;

    List *countries;
    List *viruses;
    List *vaccination;
    BloomList *bloom;
    BloomFilter *bloomF;
    listOfSkipList *VaccinatedList;
    listOfSkipList *NoVaccinatedList;
    skipList *slist;

    time_t current = time(NULL);
    struct tm *pLocal = localtime(&current);
    strftime(day, sizeof(day), "%d/%m/%Y", pLocal);

    VaccinatedList = listOfSkipListInit();
    NoVaccinatedList = listOfSkipListInit();

    countries = initList();
    viruses = initList();
    vaccination = initList();

    // //---CONVERT KBYTES TO BYTES----
    bloomString = argv[4];
    bloomString = strtok(bloomString, "K");
    bloomSize = atoi(bloomString);
    bloomSize = bloomSize * 1000;

    initHashTable(&ht);
    bloom = initBloomList();
    srand(time(NULL));

    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file");
    }

    bloomF = malloc(sizeof(BloomFilter));

    while (fgets(buff, sizeof(buff), file) != NULL)
    {

        id = strtok(buff, " ");
        name = strtok(NULL, " ");
        surname = strtok(NULL, " ");
        country = strtok(NULL, " ");
        citizenAge = strtok(NULL, " ");
        virus = strtok(NULL, " ");
        vacc = strtok(NULL, " ");
        date = strtok(NULL, " ");

        age = atoi(citizenAge);

        citizen = malloc(sizeof(Citizen));

        initCitizen(citizen, id, name, surname, country, virus, vacc);
        setCitizenInfo(citizen, id, name, surname, country, age, virus, vacc, date);

        countryExist = insertNode(countries, country);
        virusExist = insertNode(viruses, virus);
        vaccinated = insertNode(vaccination, vacc);

        int insert = insertCitizenHashTable(ht, citizen, countries, viruses, vaccination);

        if (insert != 0)
        {
            increasePopulation(countries, country);
            increaseAgeArray(countries, country, age);
            if (virusExist == 1)
            {
                initBloomFilter(bloomF, bloomSize, viruses, virus);
                slist = skipListInit(viruses, virus);
                bloomInsertList(bloom, bloomF, viruses);
                listOfSkipListInsert(NoVaccinatedList, slist, viruses);
                listOfSkipListInsert(VaccinatedList, slist, viruses);
            }
            //----INSERT BLOOM FILTER---
            if (strcmp(citizen->vaccinated, "YES") == 0)
            {
                bloomInsert(bloom, citizen->id, K, citizen->virus);
                insertSkipList(VaccinatedList, citizen, ht);
            }
            else
            {
                insertSkipList(NoVaccinatedList, citizen, ht);
            }
        }

        deleteCitizen(citizen);
        free(citizen);
    }

    printf("\033[0;31m");
    printf("/vaccineStatusBloom citizenID virusName\n/vaccineStatus citizenId virusName\n/vaccineStatus citizenID\n/populationStatus [country] virusName date1 date2\n/popStatusByAge [country] virusName date1 date2\n/insertCitizenRecord citizenID firstName lastName country age virusName YES/NO [date]\n/vaccinateNow citizenID firstName lastName country age virusName\n/list-nonVaccinated-Persons virusName\n/exit\n\n");
    printf("\033[0m");
    while (fgets(buff, sizeof(buff), stdin) != NULL)
    {
        buff[strlen(buff) - 1] = '\0';
        char *cmd1 = strtok(buff, " ");

        if (strcmp(cmd1, "/vaccineStatusBloom") == 0)
        {
            char *citizenID = strtok(NULL, " ");
            char *virusName = strtok(NULL, " ");

            if ((citizenID == NULL) || (virusName == NULL))
            {
                printf("ERROR INPUT!!\n");
                exit(1);
            }
            searchBloom(bloom, citizenID, K, virusName);
        }
        else if (strcmp(cmd1, "/vaccineStatus") == 0)
        {
            char *citizenID = strtok(NULL, " ");
            char *virusName = strtok(NULL, " ");

            if (virusName != NULL)
            {
                searchSkipList(VaccinatedList, citizenID, virusName);
            }
            else
            {
                searchAllSkipList(VaccinatedList, citizenID, viruses);
                searchAllSkipList(NoVaccinatedList, citizenID, viruses);
            }
        }
        else if (strcmp(cmd1, "/populationStatus") == 0)
        {
            char *arg2 = strtok(NULL, " ");

            int exist = nodeExist(countries, arg2);

            if (exist == 1)
            {
                char *arg3 = strtok(NULL, " ");
                char *arg4 = strtok(NULL, " ");
                char *arg5 = strtok(NULL, " ");

                if ((arg4 == NULL) || (arg5 == NULL))
                {
                    printf("ERROR\n");
                    exit(1);
                }

                char *day1;
                char *day2;
                char *month1;
                char *month2;
                char *year1;
                char *year2;

                day1 = strtok(arg4, "/");
                month1 = strtok(NULL, "/");
                year1 = strtok(NULL, "/");

                day2 = strtok(arg5, "/");
                month2 = strtok(NULL, "/");
                year2 = strtok(NULL, "/");

                populationStatus(VaccinatedList, arg3, countries, arg2, day1, month1, year1, day2, month2, year2);
            }
            else
            {

                char *arg3 = strtok(NULL, " ");
                char *arg4 = strtok(NULL, " ");
                char *arg5 = strtok(NULL, " ");

                char *Day1;
                char *Day2;
                char *Month1;
                char *Month2;
                char *Year1;
                char *Year2;

                Day1 = strtok(arg3, "/");
                Month1 = strtok(NULL, "/");
                Year1 = strtok(NULL, "/");

                Day2 = strtok(arg4, "/");
                Month2 = strtok(NULL, "/");
                Year2 = strtok(NULL, "/");

                if ((arg3 == NULL) || (arg4 == NULL))
                {
                    printf("ERROR\n");
                    exit(1);
                }

                listNode *tmp = countries->head;
                while (tmp != NULL)
                {

                    populationStatus(VaccinatedList, arg2, countries, tmp->name, Day1, Month1, Year1, Day2, Month2, Year2);

                    tmp = tmp->next;
                }
            }
        }
        else if (strcmp(cmd1, "/popStatusByAge") == 0)
        {
            char *arg2 = strtok(NULL, " ");

            int exist = nodeExist(countries, arg2);

            if (exist == 1)
            {

                char *arg3 = strtok(NULL, " ");
                char *arg4 = strtok(NULL, " ");
                char *arg5 = strtok(NULL, " ");

                if ((arg4 == NULL) || (arg5 == NULL))
                {
                    printf("ERROR\n");
                    exit(1);
                }

                char *day1;
                char *day2;
                char *month1;
                char *month2;
                char *year1;
                char *year2;

                day1 = strtok(arg4, "/");
                month1 = strtok(NULL, "/");
                year1 = strtok(NULL, "/");

                day2 = strtok(arg5, "/");
                month2 = strtok(NULL, "/");
                year2 = strtok(NULL, "/");

                popStatusByAge(VaccinatedList, arg3, countries, arg2, day1, month1, year1, day2, month2, year2);
            }
            else
            {

                char *arg3 = strtok(NULL, " ");
                char *arg4 = strtok(NULL, " ");
                char *arg5 = strtok(NULL, " ");

                char *Day1;
                char *Day2;
                char *Month1;
                char *Month2;
                char *Year1;
                char *Year2;

                Day1 = strtok(arg3, "/");
                Month1 = strtok(NULL, "/");
                Year1 = strtok(NULL, "/");

                Day2 = strtok(arg4, "/");
                Month2 = strtok(NULL, "/");
                Year2 = strtok(NULL, "/");

                if ((arg3 == NULL) || (arg4 == NULL))
                {
                    printf("ERROR\n");
                    exit(1);
                }

                listNode *tmp = countries->head;
                while (tmp != NULL)
                {

                    popStatusByAge(VaccinatedList, arg2, countries, tmp->name, Day1, Month1, Year1, Day2, Month2, Year2);

                    tmp = tmp->next;
                }
            }
        }
        else if (strcmp(cmd1, "/insertCitizenRecord") == 0)
        {
            char *citizenId = strtok(NULL, " ");
            char *firstName = strtok(NULL, " ");
            char *lastName = strtok(NULL, " ");
            char *country = strtok(NULL, " ");
            char *ageCitizen = strtok(NULL, " ");
            char *virus = strtok(NULL, " ");
            char *vacc = strtok(NULL, " ");
            char *date = strtok(NULL, " ");

            int age = atoi(ageCitizen);

            int vaccinated = citizenVaccinated(VaccinatedList, citizenId, virus);

            if (vaccinated != 1)
            {

                Citizen *citi = malloc(sizeof(Citizen));

                initCitizen(citi, citizenId, firstName, lastName, country, virus, vacc);
                setCitizenInfo(citi, citizenId, firstName, lastName, country, age, virus, vacc, date);

                countryExist = insertNode(countries, country);
                virusExist = insertNode(viruses, virus);
                vaccinated = insertNode(vaccination, vacc);
                if (strcmp(vacc, "YES") == 0)
                {
                    int noVAccinated = citizenNoVaccinated(NoVaccinatedList, citizenId, virus);
                    if (noVAccinated == 1)
                    {

                        deleteSkipList(NoVaccinatedList, citi);
                        deleteCitizenHT(ht, citi);
                    }
                }

                int insert = insertCitizenHashTable(ht, citi, countries, viruses, vaccination);

                if (insert != 0)
                {
                    increasePopulation(countries, country);
                    increaseAgeArray(countries, country, age);
                    if (virusExist == 1)
                    {
                        initBloomFilter(bloomF, bloomSize, viruses, virus);
                        slist = skipListInit(viruses, virus);
                        bloomInsertList(bloom, bloomF, viruses);
                        listOfSkipListInsert(NoVaccinatedList, slist, viruses);
                        listOfSkipListInsert(VaccinatedList, slist, viruses);
                    }
                    //----INSERT BLOOM FILTER---
                    if (strcmp(citi->vaccinated, "YES") == 0)
                    {
                        bloomInsert(bloom, citi->id, K, citi->virus);
                        insertSkipList(VaccinatedList, citi, ht);
                    }
                    else
                    {
                        insertSkipList(NoVaccinatedList, citi, ht);
                    }

                    printf("Citizen was added\n");
                }
            }
        }
        else if (strcmp(cmd1, "/vaccinateNow") == 0)
        {
            char *citizenId = strtok(NULL, " ");
            char *firstName = strtok(NULL, " ");
            char *lastName = strtok(NULL, " ");
            char *country = strtok(NULL, " ");
            char *ageCitizen = strtok(NULL, " ");
            char *virus = strtok(NULL, " ");

            int age = atoi(ageCitizen);

            int vaccinated = citizenVaccinated(VaccinatedList, citizenId, virus);

            if (vaccinated != 1)
            {

                Citizen *citi = malloc(sizeof(Citizen));

                initCitizen(citi, citizenId, firstName, lastName, country, virus, "YES");
                setCitizenInfo(citi, citizenId, firstName, lastName, country, age, virus, "YES", day);

                countryExist = insertNode(countries, country);
                virusExist = insertNode(viruses, virus);
                vaccinated = insertNode(vaccination, "YES");
                int noVAccinated = citizenNoVaccinated(NoVaccinatedList, citizenId, virus);
                if (noVAccinated == 1)
                {

                    deleteSkipList(NoVaccinatedList, citi);
                    deleteCitizenHT(ht, citi);
                }

                int insert = insertCitizenHashTable(ht, citi, countries, viruses, vaccination);

                if (insert != 0)
                {
                    increasePopulation(countries, country);
                    increaseAgeArray(countries, country, age);
                    if (virusExist == 1)
                    {
                        initBloomFilter(bloomF, bloomSize, viruses, virus);
                        slist = skipListInit(viruses, virus);
                        bloomInsertList(bloom, bloomF, viruses);
                        listOfSkipListInsert(NoVaccinatedList, slist, viruses);
                        listOfSkipListInsert(VaccinatedList, slist, viruses);
                    }
                    //----INSERT BLOOM FILTER---
                    if (strcmp(citi->vaccinated, "YES") == 0)
                    {
                        bloomInsert(bloom, citi->id, K, citi->virus);
                        insertSkipList(VaccinatedList, citi, ht);
                    }
                    else
                    {
                        insertSkipList(NoVaccinatedList, citi, ht);
                    }

                    printf("Citizen was added\n");
                }
            }
        }
        else if (strcmp(cmd1, "/list-nonVaccinated-Persons") == 0)
        {
            char *virusName = strtok(NULL, " ");
            nonVaccinated(NoVaccinatedList, virusName);
        }
        else if (strcmp(cmd1, "/exit") == 0)
        {
            free(VaccinatedList);
            free(NoVaccinatedList);
            free(slist);
            deleteList(viruses);
            deleteList(countries);
            deleteList(vaccination);
            free(countries);
            free(viruses);
            free(vaccination);
            deleteHT(ht);
            free(ht);
            deleteBloomFilter(bloom);
            free(bloom);
            free(bloomF);

            break;
        }
        else{
            printf("Wrong Input!!!\n");
        }
        printf("\033[0;31m");
        printf("\n/vaccineStatusBloom citizenID virusName\n/vaccineStatus citizenId virusName\n/vaccineStatus citizenID\n/populationStatus [country] virusName date1 date2\n/popStatusByAge [country] virusName date1 date2\n/insertCitizenRecord citizenID firstName lastName country age virusName YES/NO [date]\n/vaccinateNow citizenID firstName lastName country age virusName\n/list-nonVaccinated-Persons virusName\n/exit\n\n");
        printf("\033[0m");
    }

    return 0;
}