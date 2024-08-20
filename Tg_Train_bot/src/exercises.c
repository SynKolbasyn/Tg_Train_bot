#include <stdio.h>
#include <windows.h>
#include <locale.h>

#define STRSIZE 128	// ������������ ����� ����������� ������
#define NUMSIZE 16	// ������������ ����� ������������ �����
#define EXRSIZE 16

FILE* List = NULL;

int get_next_type();	// ��������� ����� ����� � ������ ������� �������������
int get_next_list(int* list_id);	// ���������� ����� ������ � ����� � �������� ��������������� ������������
void block_finder(int block);	// ������� � ������� ������ �� ������ ����

int update_list_id(int* list_id) {
	errno_t read_res = NULL;	// �������� ���������� �������� �����
	read_res = fopen_s(&List, "List.txt", "r+");
	if (read_res != 0) return -1;

	*list_id = get_next_type();
	*++list_id = get_next_list(list_id);
	return *list_id;
}

int get_next_type() {
	int day = 0;
	int counter = 0;
	int cursor = 0;
	char str[STRSIZE] = { 0 };

	while (!feof(List)) {
		fgets(str, STRSIZE, List);
		if (str[cursor] != '*') continue;
		counter++;
		while (str[cursor] != '>') {
			(cursor)++;
		}
		(cursor)++;
		switch ((int)str[cursor] - 48) {
		case 0:
			day = counter;
			fseek(List, -3, SEEK_CUR);
			putc('1', List);
			break;
		case 1:
			fseek(List, -3, SEEK_CUR);
			putc('2', List);
			break;
		case 2:
			fseek(List, -3, SEEK_CUR);
			putc('0', List);
			break;
		default:
			printf("A FATAL ERROR HAS OCCURRED\nUNKNOWN HISTORY PARAMETER VALUE");
			exit;
		}
		fseek(List, 3, SEEK_CUR);
		cursor = 0;
	}
	return day;
}

get_next_list(int* list_id) {
	block_finder(*list_id);

	int cursor = 0;
	char str[STRSIZE] = { 0 };
	char priority[EXRSIZE] = { 0 };
	int counter = 0;
	int imin = 1;

	while (!feof(List)) {
		cursor = 0;
		fgets(str, STRSIZE, List);
		if (str[cursor] == '*' ) break;
		if (str[cursor] == '#') counter++;
		while (str[cursor] != '>' || str[cursor] != '/') {
			cursor++;
		}
		if (str[cursor] == '/') continue;
		cursor++;
		priority[counter] += (int)str[cursor] - 48;
	}
	for (int i = 2; i <= counter; i++) {
		if (priority[i] < priority[imin]) imin = i;
	}
	return imin;
}

void block_finder(int block) {
	char str[STRSIZE] = { 0 };
	int cursor = 0;
	int counter = 0;
	while (!feof(List) && counter < block) {
		fgets(str, STRSIZE, List);
		if (str[cursor] == '*') counter++;
	}
	return 0;
}