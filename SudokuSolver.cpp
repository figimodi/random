#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

bool Check();
void Verticale(int y, int x);
void Orizzontale(int y, int x);
void Quadrato(int y, int x);
void Adiacenti(int y, int x);
void X1(int y, int x);
void X2(int y, int x);
void X3(int y, int x);
void Y1(int y, int x);
void Y2(int y, int x);
void Y3(int y, int x);
void EAX1(int y, int x);
void EAX2(int y, int x);
void EAX3(int y, int x);
void EAY1(int y, int x);
void EAY2(int y, int x);
void EAY3(int y, int x);
int Coordinate(int var);
void CheckAviable(int y, int x);
void Confronta(int cont1, int cont2, int y, int x);

FILE *file = fopen("s.txt", "r");
struct {
	int value;
	int aviable[9] = { 1,2,3,4,5,6,7,8,9 };
	bool flag;
}griglia[9][9];
int vett1[9];
int vett2[9];

int main(void) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			fscanf(file, "%d ", &griglia[y][x].value);
			if (griglia[y][x].value != 0)
				griglia[y][x].flag = true;
		}
	}
	while (!Check()) {
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				if (!griglia[y][x].flag) {
					Verticale(y, x);
					Orizzontale(y, x);
					Quadrato(y, x);
					CheckAviable(y, x);
					if (!griglia[y][x].flag)
						Adiacenti(y, x);
				}
			}
		}
	}
	fclose(file);
	file = fopen("s_solved.txt", "w");
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			fprintf(file, "%d ", griglia[y][x].value);
			printf("%d ", griglia[y][x].value);
		}
		printf("\n");
		fprintf(file, "\n");
	}
	fclose(file);
	printf("\n\nBy Filippo Greco\n\n");
	system("pause");
}

bool Check() {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++)
			if (!griglia[y][x].flag)
				return false;
	}
	return true;
}

void Verticale(int y, int x) {
	for (int i = 0; i < 9; i++) {
		if (griglia[i][x].value != 0)
			griglia[y][x].aviable[griglia[i][x].value - 1] = 0;
	}
}

void Orizzontale(int y, int x) {
	for (int i = 0; i < 9; i++) {
		if (griglia[y][i].value != 0)
			griglia[y][x].aviable[griglia[y][i].value - 1] = 0;
	}
}

void Quadrato(int y, int x) {
	switch (Coordinate(y)) {
	case 1:
		Y1(y, x);
		break;
	case 2:
		Y2(y, x);
		break;
	case 3:
		Y3(y, x);
		break;
	}
	switch (Coordinate(x))
	{
	case 1:
		X1(y, x);
		break;
	case 2:
		X2(y, x);
		break;
	case 3:
		X3(y, x);
		break;
	}
}

void X1(int y, int x) {
	for (int i = 1; i < 3; i++) {
		if (griglia[y][x + i].value != 0)
			griglia[y][x].aviable[griglia[y][x + i].value - 1] = 0;
	}
}

void X2(int y, int x) {
	if (griglia[y][x + 1].value != 0)
		griglia[y][x].aviable[griglia[y][x + 1].value - 1] = 0;
	if (griglia[y][x - 1].value != 0)
		griglia[y][x].aviable[griglia[y][x - 1].value - 1] = 0;
}

void X3(int y, int x) {
	for (int i = 1; i < 3; i++) {
		if (griglia[y][x - i].value != 0)
			griglia[y][x].aviable[griglia[y][x - i].value - 1] = 0;
	}
}

void Y1(int y, int x) {
	for (int z = 1; z < 3; z++) {
		for (int i = 0; i < 3; i++) {
			if (griglia[y + z][x + i - Coordinate(x) + 1].value != 0)
				griglia[y][x].aviable[griglia[y + z][x + i - Coordinate(x) + 1].value - 1] = 0;
		}
	}
}

void Y2(int y, int x) {
	for (int i = 0; i < 3; i++) {
		if (griglia[y + 1][x + i - Coordinate(x) + 1].value != 0)
			griglia[y][x].aviable[griglia[y + 1][x + i - Coordinate(x) + 1].value - 1] = 0;
		if (griglia[y - 1][x + i - Coordinate(x) + 1].value != 0)
			griglia[y][x].aviable[griglia[y - 1][x + i - Coordinate(x) + 1].value - 1] = 0;
	}
}

void Y3(int y, int x) {
	for (int z = 1; z < 3; z++) {
		for (int i = 0; i < 3; i++) {
			if (griglia[y - z][x + i - Coordinate(x) + 1].value != 0)
				griglia[y][x].aviable[griglia[y - z][x + i - Coordinate(x) + 1].value - 1] = 0;
		}
	}
}

int Coordinate(int var) {
	if (var == 0 || var == 3 || var == 6)
		return 1;
	if (var == 1 || var == 4 || var == 7)
		return 2;
	if (var == 2 || var == 5 || var == 8)
		return 3;
	return 0 ;
}

void CheckAviable(int y, int x) {
	int counter = 0;
	int valore;
	for (int i = 0; i < 9; i++) {
		if (griglia[y][x].aviable[i] == 0)
			counter++;
		else
			valore = griglia[y][x].aviable[i];
	}
	if (counter == 8) {
		griglia[y][x].value = valore;
		griglia[y][x].flag = true;
	}
}

void Confronta(int cont1, int cont2, int y, int x) {
	for (int z = 0; z < cont1; z++) {
		for (int i = 0; i < cont2; i++)
			if ((vett1[z] == vett2[i]) && (griglia[y][x].aviable[vett1[z] - 1] != 0) && (vett1[z] != 0)) {
				griglia[y][x].value = vett1[z];
				griglia[y][x].flag = true;
			}
	}
}

void Adiacenti(int y, int x) {
	switch (Coordinate(y)) {
	case 1:
		EAY1(y, x);
		break;
	case 2:
		EAY2(y, x);
		break;
	case 3:
		EAY3(y, x);
		break;
	}
	if (!griglia[y][x].flag) {
		switch (Coordinate(x)) {
		case 1:
			EAX1(y, x);
			break;
		case 2:
			EAX2(y, x);
			break;
		case 3:
			EAX3(y, x);
			break;
		}
	}
}

void EAY1(int y, int x) {
	int cont1 = 0;
	int cont2 = 0;
	bool ok = false;
	switch (Coordinate(x)) {
	case 1:
		if (griglia[y][x + 1].value != 0 && griglia[y][x + 2].value != 0)
			ok = true;
		break;
	case 2:
		if (griglia[y][x + 1].value != 0 && griglia[y][x - 1].value != 0)
			ok = true;
		break;
	case 3:
		if (griglia[y][x - 1].value != 0 && griglia[y][x - 2].value != 0)
			ok = true;
		break;
	}
	if (ok) {
		for (int i = 0; i < 9; i++) {
			if (griglia[y + 1][i].value != 0) {
				vett1[cont1] = griglia[y + 1][i].value;
				cont1++;
			}
			if (griglia[y + 2][i].value != 0) {
				vett2[cont2] = griglia[y + 2][i].value;
				cont2++;
			}
		}
		Confronta(cont1, cont2, y, x);
	}
}

void EAY2(int y, int x) {
	int cont1 = 0;
	int cont2 = 0;
	bool ok = false;
	switch (Coordinate(x)) {
	case 1:
		if (griglia[y][x + 1].value != 0 && griglia[y][x + 2].value != 0)
			ok = true;
		break;
	case 2:
		if (griglia[y][x + 1].value != 0 && griglia[y][x - 1].value != 0)
			ok = true;
		break;
	case 3:
		if (griglia[y][x - 1].value != 0 && griglia[y][x - 2].value != 0)
			ok = true;
		break;
	}
	if (ok) {
		for (int i = 0; i < 9; i++) {
			if (griglia[y + 1][i].value != 0) {
				vett1[cont1] = griglia[y + 1][i].value;
				cont1++;
			}
			if (griglia[y - 1][i].value != 0) {
				vett2[cont2] = griglia[y - 1][i].value;
				cont2++;
			}
		}
		Confronta(cont1, cont2, y, x);
	}
}

void EAY3(int y, int x) {
	int cont1 = 0;
	int cont2 = 0;
	bool ok = false;
	switch (Coordinate(x)) {
	case 1:
		if (griglia[y][x + 1].value != 0 && griglia[y][x + 2].value != 0)
			ok = true;
		break;
	case 2:
		if (griglia[y][x + 1].value != 0 && griglia[y][x - 1].value != 0)
			ok = true;
		break;
	case 3:
		if (griglia[y][x - 1].value != 0 && griglia[y][x - 2].value != 0)
			ok = true;
		break;
	}
	if (ok) {
		for (int i = 0; i < 9; i++) {
			if (griglia[y - 1][i].value != 0) {
				vett1[cont1] = griglia[y - 1][i].value;
				cont1++;
			}
			if (griglia[y - 2][i].value != 0) {
				vett2[cont2] = griglia[y - 2][i].value;
				cont2++;
			}
		}
		Confronta(cont1, cont2, y, x);
	}
}

void EAX1(int y, int x) {
	int cont1 = 0;
	int cont2 = 0;
	bool ok = false;
	switch (Coordinate(y)) {
	case 1:
		if (griglia[y + 1][x].value != 0 && griglia[y + 2][x].value != 0)
			ok = true;
		break;
	case 2:
		if (griglia[y + 1][x].value != 0 && griglia[y - 1][x].value != 0)
			ok = true;
		break;
	case 3:
		if (griglia[y - 1][x].value != 0 && griglia[y - 2][x].value != 0)
			ok = true;
		break;
	}
	if (ok) {
		for (int i = 0; i < 9; i++) {
			if (griglia[i][x + 1].value != 0) {
				vett1[cont1] = griglia[i][x + 1].value;
				cont1++;
			}
			if (griglia[i][x + 2].value != 0) {
				vett2[cont2] = griglia[i][x + 2].value;
				cont2++;
			}
		}
		Confronta(cont1, cont2, y, x);
	}
}

void EAX2(int y, int x) {
	int cont1 = 0;
	int cont2 = 0;
	bool ok = false;
	switch (Coordinate(y)) {
	case 1:
		if (griglia[y + 1][x].value != 0 && griglia[y + 2][x].value != 0)
			ok = true;
		break;
	case 2:
		if (griglia[y + 1][x].value != 0 && griglia[y - 1][x].value != 0)
			ok = true;
		break;
	case 3:
		if (griglia[y - 1][x].value != 0 && griglia[y - 2][x].value != 0)
			ok = true;
		break;
	}
	if (ok) {
		for (int i = 0; i < 9; i++) {
			if (griglia[i][x + 1].value != 0) {
				vett1[cont1] = griglia[i][x + 1].value;
				cont1++;
			}
			if (griglia[i][x - 1].value != 0) {
				vett2[cont2] = griglia[i][x - 1].value;
				cont2++;
			}
		}
		Confronta(cont1, cont2, y, x);
	}
}

void EAX3(int y, int x) {
	int cont1 = 0;
	int cont2 = 0;
	bool ok = false;
	switch (Coordinate(y)) {
	case 1:
		if (griglia[y + 1][x].value != 0 && griglia[y + 2][x].value != 0)
			ok = true;
		break;
	case 2:
		if (griglia[y + 1][x].value != 0 && griglia[y - 1][x].value != 0)
			ok = true;
		break;
	case 3:
		if (griglia[y - 1][x].value != 0 && griglia[y - 2][x].value != 0)
			ok = true;
		break;
	}
	if (ok) {
		for (int i = 0; i < 9; i++) {
			if (griglia[i][x - 1].value != 0) {
				vett1[cont1] = griglia[i][x - 1].value;
				cont1++;
			}
			if (griglia[i][x - 2].value != 0) {
				vett2[cont2] = griglia[i][x - 2].value;
				cont2++;
			}
		}
		Confronta(cont1, cont2, y, x);
	}
}