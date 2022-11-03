#define _CRT_SECURE_NO_WARNINGS
#define duzineImenaIPrezimena 64
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#pragma region Strukture
typedef struct Osoba* Sljedeca;
struct Osoba {
	char _ime[duzineImenaIPrezimena];
	char _prezime[duzineImenaIPrezimena];
	int _godina_rodenja;
	Sljedeca _sljedecaOsoba;
};
#pragma endregion

#pragma region Definicije funkcija
int Izbornik(int);
int DodajNaPocetak(char*, char*, int, Sljedeca);
int DodajNaPoziciju(char*, char*, int, Sljedeca);
int Ispisi(Sljedeca);
int DodajNaKraj(Sljedeca);
Sljedeca PronadjiUListiPoPrezimenu(char*, Sljedeca);
Sljedeca PronadjiUListiPokazivaNaPrezime(char*, Sljedeca);
int IzbrisiPoPrezimenu(char*, Sljedeca);
int OslobodiNodove(Sljedeca);
int Sortiraj(Sljedeca);
int IspisiUDatoteku(Sljedeca);
int UpisIzDatoteke(char*,Sljedeca,int);
int PrebrojiRedove(char*);
#pragma endregion

int main()
{
	struct Osoba Head;
	int izbor = 0;
	Head._sljedecaOsoba = NULL;
	printf("Izaberite koju funkciju zelite izabrati:\n1-Dodaj na pocetak\n2-Ispisi listu\n3-Dodaj na kraj\n4-Pronadi po prezimenu\n5-Obrisi iz liste\n");
	printf("6-Dodaj iza osobe\n7-Dodaj prije osobe\n8-Sortiraj po prezimenu\n9-Ispisi iz datoteke\n10-Upisi u datoteku\n0-Izlaz\n");
	scanf("%d", &izbor);
	while (izbor) {
		Izbornik(izbor,&Head);
		printf("Izaberite koju funkciju zelite izabrati:\n1-Dodaj na pocetak\n2-Ispisi listu\n3-Dodaj na kraj\n4-Pronadi po prezimenu\n5-Obrisi iz liste\n");
		printf("6-Dodaj iza osobe\n7-Dodaj prije osobe\n8-Sortiraj po prezimenu\n9-Ispisi iz datoteke\n10-Upisi u datoteku\n0-Izlaz\n");
		scanf("%d", &izbor);
	}
	OslobodiNodove(&Head);
	return 0;
}

#pragma region Funkcije
int Izbornik(int izbor,Sljedeca Head) {
	char ime[duzineImenaIPrezimena] = "";
	char prezime2[duzineImenaIPrezimena] = "";
	char prezime[duzineImenaIPrezimena] = "";
	int godinaRodjenja = 0;
	char fname[20]="";
	switch (izbor) {
	case 1:
		printf("Upisi ime, prezime i godinu rodjenja osobe\n");
		scanf("%s %s %d", &ime, &prezime, &godinaRodjenja);
		if (DodajNaPocetak(ime, prezime, godinaRodjenja, Head))
			printf("Osoba uspjesno dodana na pocetak liste\n");
		break;
	case 2:
		Ispisi(Head);
		break;

	case 3:
		printf("Upisi ime, prezime i godinu rodjenja osobe\n");
		scanf("%s %s %d", &ime, &prezime, &godinaRodjenja);
		if (DodajNaKraj(ime, prezime, godinaRodjenja, Head))
			printf("Osoba uspjesno dodana na kraj liste\n");
		break;
	case 4:
		printf("Upisi prezime osobe koje zelis pronaci\n");
		scanf("%s", prezime);
		if (PronadjiUListiPoPrezimenu(prezime, Head) == NULL) {
			printf("Osoba koju trazite nije u listi!\n");
		}
		else {
			printf("Osoba koju trazite je u listi!\n");
		}
		break;
	case 5:
		printf("Upisi prezime osobe koje zelis pronaci\n");
		scanf("%s", prezime);
		IzbrisiPoPrezimenu(prezime, Head);
		break;
	case 6:
		printf("Upisite prezime osobe iza koje zelite dodati osobu\n");
		scanf("%s", prezime2);
		printf("Upisi ime, prezime i godinu rodjenja osobe\n");
		scanf("%s %s %d", &ime, &prezime, &godinaRodjenja);
		DodajNaPoziciju(ime, prezime, godinaRodjenja, PronadjiUListiPoPrezimenu(prezime, Head));
	case 7:
		printf("Upisite prezime osobe prije koje zelite dodati osobu\n");
		scanf("%s", prezime2);
		printf("Upisi ime, prezime i godinu rodjenja osobe\n");
		scanf("%s %s %d", &ime, &prezime, &godinaRodjenja);
		DodajNaPoziciju(ime, prezime, godinaRodjenja, PronadjiUListiPokazivaNaPrezime(prezime, Head));
	case 8:
		Sortiraj(Head);
		break;
	case 9:
		printf("Upisite kako zelite da se zove file\n");
		scanf("%s", fname);
		IspisiUDatoteku(fname,Head);
		break;
	case 10:
		printf("Upisite iz kojeg filea zelite ucitati ljude\n");
		scanf("%s", fname);
		UpisIzDatoteke(fname,Head, PrebrojiRedove(fname));
		break;
	case 0:
		break;
	}
}
int DodajNaPocetak(char* ime, char* prezime, int godina_rodenja, Sljedeca S) {
	DodajNaPoziciju(ime, prezime, godina_rodenja, S);
	return 0;
}
int DodajNaPoziciju(char* ime, char* prezime, int godina_rodenja, Sljedeca S) {
	Sljedeca osoba = (Sljedeca)malloc(sizeof(struct Osoba));
	if (osoba == NULL) {
		return;
	}
	strncpy(osoba->_ime, ime, duzineImenaIPrezimena);
	osoba->_ime[duzineImenaIPrezimena - 1] = '\0';
	strncpy(osoba->_prezime, prezime, duzineImenaIPrezimena);
	osoba->_prezime[duzineImenaIPrezimena - 1] = '\0';
	osoba->_godina_rodenja = godina_rodenja;
	osoba->_sljedecaOsoba = S->_sljedecaOsoba;
	S->_sljedecaOsoba = osoba;
	return 0;
}
int Ispisi(Sljedeca S) {
	Sljedeca osoba = S->_sljedecaOsoba;
	if (S->_godina_rodenja > 1000 && S->_godina_rodenja < 9999)
		printf("%s %s %d \n", S->_ime, S->_prezime, S->_godina_rodenja);//"%s %s %d", S->_ime, S->_prezime, S->_godina_rodenja
	if (osoba != NULL) {
		Ispisi(osoba);
	}
	return 0;
}
int DodajNaKraj(char* ime, char* prezime, int godina_rodenja, Sljedeca S) {
	if (S->_sljedecaOsoba == NULL)
		DodajNaPoziciju(ime, prezime, godina_rodenja, S);
	else
		DodajNaKraj(ime, prezime, godina_rodenja, S->_sljedecaOsoba);
}
Sljedeca PronadjiUListiPoPrezimenu(char* prezime, Sljedeca S) {
	if (!strcmp(S->_prezime, prezime)) {
		return S;
	}
	else {
		if (S->_sljedecaOsoba != NULL) {
			PronadjiUListiPoPrezimenu(prezime, S->_sljedecaOsoba);
		}
		else {
			return NULL;
		}
	}
}
Sljedeca PronadjiUListiPokazivaNaPrezime(char* prezime, Sljedeca S) {
	if (!strcmp(S->_sljedecaOsoba->_prezime, prezime)) {
		return S;
	}
	else {
		if (S->_sljedecaOsoba != NULL) {
			PronadjiUListiPokazivaNaPrezime(prezime, S->_sljedecaOsoba);
		}
		else {
			return NULL;
		}
	}
}
int IzbrisiPoPrezimenu(char* prezime, Sljedeca S) {
	Sljedeca trazeni = PronadjiUListiPoPrezimenu(prezime, S);
	if (trazeni == NULL) {
		printf("Osoba sa tim prezimenom nije u listi!\n");
	}
	else {
		Sljedeca prijeTrazenoga = PronadjiUListiPokazivaNaPrezime(prezime, S);
		prijeTrazenoga->_sljedecaOsoba = trazeni->_sljedecaOsoba;
		trazeni->_sljedecaOsoba = NULL;
		printf("Osoba je izbrisana iz liste!\n");
	}
}
int Sortiraj(Sljedeca p) {
	Sljedeca i, prev_i, temp, end;
	end = NULL;
	while (p->_sljedecaOsoba != end)
	{
		prev_i = p;
		i = p->_sljedecaOsoba;
		while (i->_sljedecaOsoba != end) {
			if (strcmp(i->_prezime,i->_sljedecaOsoba->_prezime)>0) {
				temp = i->_sljedecaOsoba;
				prev_i->_sljedecaOsoba = temp;
				i->_sljedecaOsoba = temp->_sljedecaOsoba;
				temp->_sljedecaOsoba =i;
				i = temp;
			}
			prev_i = i;
			i = i->_sljedecaOsoba;
		}
		end = i;
	}
	printf("Sortirano!");
}
int OslobodiNodove(Sljedeca S) {
	if (S->_sljedecaOsoba == NULL)
	{
		free(S);
	}
	else {
		OslobodiNodove(S->_sljedecaOsoba);
		free(S);
	}
	return 0;
}
int IspisiUDatoteku(char* fileName, Sljedeca S) {
	FILE* f;
	f= fopen(fileName, "w");
	if (f == NULL) {
		printf("Datoteka nije valjana\n");
		return 1;
	}
	while (S->_sljedecaOsoba != NULL) {
		fprintf(f, "%s      %s    %d\n", S->_sljedecaOsoba->_ime, S->_sljedecaOsoba->_prezime, S->_sljedecaOsoba->_godina_rodenja);
		S = S->_sljedecaOsoba;
	}
	printf("Dovrseno ispisivanje u datoteku!\n");
	fclose(f);
}

int DodajSortirano(char* ime, char* prezime, int godina_rodenja, Sljedeca S) {
	while (S->_sljedecaOsoba != NULL) {
		if (strcmp(prezime,S->_sljedecaOsoba->_prezime)<0) {
			DodajNaPoziciju(ime,prezime,godina_rodenja,S);
			return 0;
		}
		S = S->_sljedecaOsoba;
	}
	DodajNaPoziciju(ime, prezime, godina_rodenja, S);
}
int PrebrojiRedove(char* fileName) {
	int cnt = 0;
	char* buffer = malloc(1024);
	if (buffer == NULL) {
		return 1;
	}
	FILE* f;
	f = fopen(fileName, "r");
	while (1) {
		if (fgets(buffer, 50, f) == '\0')
			break;
		cnt++;
	}
	fclose(f);
	return cnt;
}
int UpisIzDatoteke(char* fileName, Sljedeca S,int cnt) {
	FILE* f;
	int i,godinaRodenja;
	char ime[duzineImenaIPrezimena], prezime[duzineImenaIPrezimena];
	f = fopen(fileName, "r");
	if (f == NULL || cnt==0) {
		printf("Datoteka nije valjana\n");
		return 1;
	}
	for (i = 0; i < cnt; i++) {
		fscanf(f, "%s %s %d", &ime, &prezime, &godinaRodenja);
		DodajSortirano(ime, prezime, godinaRodenja, S);
	}
}
#pragma endregion
