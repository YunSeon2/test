#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#define MAX 50

typedef struct student
{
	int Number;
	char Name[10];
	int Age;
	char Gender[10];
	int Class;
}Student;
void ShowStudent(Student* St)
{
	printf("\t========%s학생(%d번)========\n", St->Name, St->Number);
	printf("\t나이 : %d,  성별 : %s,  학년 : %d\n", St->Age, St->Gender, St->Class);
	printf("\t===========================\n");
}
void ShowClass(Student* St[], int Class, int* StudentCount)
{
	printf("┌─────────%d 학년─────────┐\n", Class);
	for (int i = 0; i < *StudentCount; i++)
		if (St[i]->Class == Class)
			ShowStudent(St[i]);
	printf("└─────────────────────┘\n");
}
void SetStudent(Student* St, int* StudentCount)
{
	St->Number = ++(*StudentCount);
	printf("======%d번 학생======\n", St->Number);
	printf("이름 입력 : ");
	scanf("%s", St->Name);
	printf("나이 입력 : ");
	scanf("%d", &St->Age);
	printf("성별 입력 : ");
	scanf("%s", St->Gender);
	printf("학년 입력(1~3) : ");
	scanf("%d", &St->Class);
	if (St->Class > 3 || St->Class < 1)
	{
		printf("학년 잘못 입력\n");
		free(St);
		(*StudentCount)--;
		system("pause");
	}
}
void SortClass(Student* St[], int* StudentCount)
{
	Student* tmp;
	for (int i = 0; i < *StudentCount - 1; i++)
	{
		for (int j = i + 1; j < *StudentCount; j++)
		{
			if (St[i]->Class > St[j]->Class)
			{
				tmp = St[i];
				St[i] = St[j];
				St[j] = tmp;
			}
		}
	}
}
void SortNumber(Student* St[], int* StudentCount)
{
	Student* tmp2;
	for (int i = 0; i < *StudentCount - 1; i++)
	{
		for (int j = i + 1; j < *StudentCount; j++)
		{
			if (St[i]->Number > St[j]->Number)
			{
				tmp2 = St[i];
				St[i] = St[j];
				St[j] = tmp2;
			}
		}
	}
}
void WriteStudent(Student* St[], FILE* f, int *StudentCount)
{
	f = fopen("학생 정보.txt", "w");
	fprintf(f, "%d\n", *StudentCount);
	for (int i = 0; i < *StudentCount; i++)
	{
		fprintf(f, "%s %d %s %d\n", St[i]->Name, St[i]->Age, St[i]->Gender, St[i]->Class);
	}
	fclose(f);
	printf("저장 완료!!\n");
	system("pause");
}
void ReadStudent(Student* St[], FILE* f, int *StudentCount)
{
	f = fopen("학생 정보.txt", "r");
	if (f == NULL)
		printf("해당 이름의 파일이 없습니다.\n");
	else
	{
		for (int i = 0; i < *StudentCount; i++)
		{
			free(St[i]);
			St[i] = NULL;
		}
		fscanf(f, "%d\n", StudentCount);
		for (int i = 0; i < *StudentCount; i++)
		{
			St[i] = (Student*)malloc(sizeof(Student));
			fscanf(f, "%s %d %s %d\n", St[i]->Name, &St[i]->Age, St[i]->Gender, &St[i]->Class);
			St[i]->Number = i + 1;
		}
		fclose(f);
	}
}
void main()
{
	Student* Student_List[MAX];
	int Select;
	int StudentCount = 0;
	char Sname[10];
	int Sclass;
	FILE* f = NULL;

	while (1)
	{
		system("cls");
		printf("=====학생관리프로그램=====(총 인원 : %d)\n", StudentCount);
		printf("1.학생 등록\n");
		printf("2.학생 목록(번호순)\n");
		printf("3.학생 목록(학년순)\n");
		printf("4.학년 검색\n");
		printf("5.학생 검색\n");
		printf("6.마지막 학생 삭제\n");
		printf("7.학생 전체 삭제\n");
		printf("8.학생 정보 저장\n");
		printf("9.학생 정보 불러오기\n");
		printf("10.종료\n");
		printf("입력 : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			system("cls");
			if (StudentCount + 1 >= MAX)
			{
				printf("학생정원(%d명)이 모두 찼습니다.\n", MAX);
				system("pause");
				break;
			}
			Student_List[StudentCount] = (Student*)malloc(sizeof(Student));
			SetStudent(Student_List[StudentCount], &StudentCount);
			break;
		case 2:
			system("cls");
			SortNumber(Student_List, &StudentCount);
			for (int i = 0; i < StudentCount; i++)
				ShowStudent(Student_List[i]);
			system("pause");
			break;
		case 3:
			system("cls");
			SortClass(Student_List, &StudentCount);
			for (int i = 1; i <= 3; i++)
				ShowClass(Student_List, i, &StudentCount);
			system("pause");
			break;
		case 4:
			system("cls");
			printf("검색할 학년 입력(1~3): ");
			scanf("%d", &Sclass);
			ShowClass(Student_List, Sclass, &StudentCount);
			system("pause");
			break;
		case 5:
			system("cls");
			printf("검색할 이름 입력: ");
			scanf("%s", Sname);
			for (int i = 0; i < StudentCount; i++)
				if (!strcmp(Student_List[i]->Name, Sname))
					ShowStudent(Student_List[i]);
			system("pause");
			break;
		case 6:
			if (StudentCount == 0)
			{
				printf("더 이상 삭제할 학생이 없습니다.\n");
				system("pause");
				continue;
			}
			StudentCount--;
			printf("%s학생 동적할당 해제 완료\n", Student_List[StudentCount]->Name);
			free(Student_List[StudentCount]);
			Student_List[StudentCount] = NULL;
			system("pause");
			break;
		case 7:
			if (StudentCount == 0)
			{
				printf("더 이상 삭제할 학생이 없습니다.\n");
				system("pause");
				continue;
			}
			for (int i = 0; i < StudentCount; i++)
			{
				printf("%s학생 동적할당 해제 완료\n", Student_List[i]->Name);
				free(Student_List[i]);
				Student_List[i] = NULL;
			}
			StudentCount = 0;
			system("pause");
			break;
		case 8:
			WriteStudent(Student_List, f, &StudentCount);
			break;
		case 9:
			ReadStudent(Student_List, f, &StudentCount);
			break;
		case 10:
			for (int i = 0; i < StudentCount; i++)
			{
				printf("%s학생 동적할당 해제 완료\n", Student_List[i]->Name);
				free(Student_List[i]);
			}
			return;
		}
	}
}