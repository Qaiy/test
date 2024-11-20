//!!!˳���ʵ��ͼ�����ϵͳ 
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100			//˳�����ܴﵽ����󳤶�
typedef int Status; //Status �Ǻ�������ֵ���ͣ���ֵ�Ǻ������״̬���롣
//����һ������ͼ����Ϣ����š��������۸񣩵�˳���
struct Book{
	char id[30];
	char name[30];
	double price;
}; 
typedef struct
{
	int length;//��ǰ˳�����
	Book* elem;//����˳�����Ԫ�����͵�����ָ��
}SqList;
//0.˳���ĳ�ʼ�� 
Status CreateBookList(SqList &L) {
	L.elem = new Book[MAXSIZE]; //Ϊ˳������һ����СΪMAXSIZE������ռ�
	if (!L.elem) {
		printf("˳����ʼ��ʧ��!\a\n");
		exit(OVERFLOW); //�洢����ʧ���˳�
	}
	L.length = 0; //�ձ���Ϊ0
	printf("˳����ʼ���ɹ���\n");
	return OK;
}
//1.	ͼ����Ϣ��Ĵ��������
//���鼮����
int read_books(SqList* L, bool& status) {
 	int i = 0;
	FILE* fp;
	if ((fp = fopen("D://book1.txt", "r")) == NULL) {
		printf("\a");
		puts("�Ҳ������ļ�����ʧ��!");
		return 0;
	} 
	while (!feof(fp)) {
		fscanf(fp, "%s%s%lf\n", L->elem[i].id, L->elem[i].name, &L->elem[i].price);
		printf("%s\t%s\t%.2lfԪ\n", L->elem[i].id, L->elem[i].name, L->elem[i].price);
		i++;
		L->length++;
	}
	fclose(fp);
	return 1; 
}
//��ӡ˳������� 
void print(SqList L) {
	for (int i = 0; i < L.length; i++) {
		printf("%s\t%s\t%.2lfԪ\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
	}
	//updata_books(&L);
	printf("Current storage space : (% d / % d)\n", L.length, MAXSIZE);
}
Status WhetherReset(bool& status) {
	char reset;
	if (status == true) {
		printf("Are you sure to reset the list based on documents?(Y/N)\a");
		getchar();
		scanf("%c", &reset);
		if (reset == 'Y')return OK;
		else return ERROR;
	}return OK;
}	
//2.	ͼ����Ϣ�����ͼ������
//2�ϼ���ͼ��
Status Insert_BookList(SqList& L) {
	SqList* base;
	Book e;
	int location;
	printf("Please enter the position you want to insert:");
	scanf("%d", &location);
	if (L.length < 0) {
		printf("Error:The order table not created!\a\n");
		return ERROR;               //������С��0����δ�����ڴ棬�������������
	}
	if (L.length >= MAXSIZE) {        //���ȴ���˳������ֵʱ�������������
		printf("Error:The order table is full!\a\n");
		return ERROR;
	}
	if (location <= 0 || location > L.length + 1) {
		printf("Error:The insertion position is invalid!\a\n");
		return ERROR;
	}
//	printf("Isbn:");
//	scanf("%s", &e.id);
//	printf("title:");
//	scanf("%s", &e.name);
//	printf("price:");
//	scanf("%lf", &e.price);
	printf("������ISBN-Name-Price:");
	scanf("%s %s %lf",&e.id,&e.name,&e.price);
	for (int i = L.length - 1; i >= location - 1; i--) {
		L.elem[i + 1] = L.elem[i];
	}
	L.elem[location - 1] = e;
	++L.length;
//	updata_books(&L);
	print(L);
	printf("Insert the success.\n");
	return OK;
}
//3.	ͼ����Ϣ��ľ�ͼ�����
//3�¼ܾ�ͼ��(�������)
Status DeleteBookList(SqList& L) {
	char isbn[15];
	if (L.length < 0) {
		printf("Error:No books on the shelves!\a\n");
		return ERROR;               //������С��0����δ�����ڴ棬������ɾ������
	}
	printf("Isbn that you want to delete:");
	getchar();
	scanf("%s", &isbn);
	for (int i = 0; i < L.length; i++) {
		if (!strcmp(isbn, L.elem[i].id)) {
			for (i; i < L.length; i++) {
				L.elem[i] = L.elem[i + 1];
			}
			--L.length;
			//updata_books(&L);
			print(L);
			printf("Delete the success.\n");
			return OK;
		}
	}
	print(L);
	printf("Books don't exist!\n\a");
	return ERROR;
}
//4.	ͼ����Ϣ��İ���Ų���
//4����Ų���
Status SearchBookIsbn(SqList L) {
	char isbn[15];
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	printf("Enter the isbn you want to find:");
	getchar();
	scanf("%s", &isbn);
	for (int i = 0; i < L.length; i++) {
		if (!strcmp(isbn, L.elem[i].id)) {
			printf("The book with THE ISBN %s has been found for you:\n", isbn);
			printf("%s\t%s\t%.2lfԪ\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
			return OK;
		}
	}
	printf("ERROR:Books don't exist!\n\a");
	return ERROR;
}
//����������
Status SearchBookName(SqList L) {
	char Name[15];
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	printf("Enter the Name you want to find:");
	getchar();
	scanf("%s", &Name);
	for (int i = 0; i < L.length; i++) {
		if (!strcmp(Name, L.elem[i].name)) {
			printf("The book with THE Name %s has been found for you:\n", Name);
			printf("%s\t%s\t%.2lfԪ\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
			return OK;
		}
	}
	printf("ERROR:Books don't exist!\n\a");
	return ERROR;
}
//5.	ͼ����Ϣ��İ��۸��������
//5���ڼ۸��������
Status SearchBookPriceRange(SqList L) {
	int num = 0;
	bool exist = false;
	double min_price;
	double max_price;
	printf("The lowest price:");
	getchar();
	scanf("%lf", &min_price);
	printf("The highest price:");
	getchar();
	scanf("%lf", &max_price);
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i].price >= min_price && L.elem[i].price <= max_price) {
			printf("%s\t%s\t%.2lf\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
			num++;
			exist = true;
		}
	}
	if (exist == false) {
		printf("ERROR:Books are not available at this price!\n\a");
		return ERROR;
	}
	printf("There are %d books altogether.\n", num);
	return OK;
}
//6.	ͼ����Ϣ��İ��۸���������
//6�۸���������
Status PriceAscendingSort(SqList& L) {
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	Book temp;
	for (int j = L.length - 1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			if (L.elem[i].price > L.elem[i + 1].price) {
				temp = L.elem[i];
				L.elem[i] = L.elem[i + 1];
				L.elem[i + 1] = temp;
			}
		}
	}
//	updata_books(&L);
	print(L);
	printf("Order to complete.\n");
}
//7.	����ָ����ţ�����ͼ��۸���޸�
//7��ͼ��۸��޸�
Status ReviseAccordingBookPrice(SqList& L) {
	char isbn[15];
	double price;
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	printf("isbn:");
	getchar();
	scanf("%s", &isbn);
	printf("price:");
	getchar();
	scanf("%lf", &price);
	for (int i = 0; i < L.length; i++) {
		if (!strcmp(isbn, L.elem[i].id)) {
			L.elem[i].price = price;
//			updata_books(&L);
			print(L);
			printf("Modify the success.\n");
			return OK;
		}
	}
	printf("ERROR:Books don't exist!\n\a");
	return ERROR;
}
//8.	ͼ��۸��յ�
/*
	8��ͼ��۸��յ� (��������ͼ���ƽ���۸񣬽����е���ƽ���۸��ͼ��۸���� 20%��
	 ���и��ڻ����ƽ���۸��ͼ��۸���� 10%�������������۸��޸ĺ��ȫ��ͼ����Ϣ��)
*/
Status PriceIncrease(SqList& L) {
	double sum_price = 0;
	double average;
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	for (int i = 0; i < L.length; i++) {
		sum_price += L.elem[i].price;
	}
	average = sum_price / L.length;
	for (int i = 0; i < L.length; i++) {
		if (average > L.elem[i].price) {
			L.elem[i].price += (L.elem[i].price * 0.2);
		}
		else {
			L.elem[i].price += (L.elem[i].price * 0.1);
		}
	}
//	updata_books(&L);
	print(L);
	printf("The average price: %lf Ԫ\n", average);
	printf("The price has been raised successfully.\n");
	return OK;
}	
//9.	ͼ����Ϣ������ͼ��Ĳ���
//9�����ͼ�����
Status SearchBookPriceBest(SqList L) {
	int num = 0;
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	double expensive = 0;
	for (int i = 0; i < L.length; i++) {
		expensive = expensive < L.elem[i].price ? L.elem[i].price : expensive;
	}
	for (int i = 0; i < L.length; i++) {
		if (L.elem[i].price >= expensive) {
			printf("%s\t%s\t%.2lf\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
			num++;
		}
	}
	printf("There are %d books altogether.\n", num);
	return OK;
}
//10. ͼ����Ϣ���ͼ��ȥ��
//10ͼ��ȥ��
Status DeleteDuplicateBooks(SqList& L) {
	if (L.length < 0) {
		printf("Error:No book data!\a\n");
		return ERROR;
	}
	for (int j = 0; j < L.length; j++) {
		for (int i = (j + 1); i < L.length - j; i++) {
			if (!strcmp(L.elem[j].id, L.elem[i].id)) {
				for (i; i < L.length; i++) {
					L.elem[i] = L.elem[i + 1];
				}
				i--; j--;
				--L.length;
			}
		}
	}
//	updata_books(&L);
	print(L);
	printf("Duplicate books have been successfully deleted.\n");
	return OK;
}
int main(){
	SqList L;
	bool status = false;
	int FirstChoose;
		while (true) {
		printf("============The main menu=========\n");
//		printf("0���޸�txt�ļ�\n");
		printf("1���˳�ϵͳ\n");
		printf("2����ʼ��������ͼ����Ϣ��Ĵ��������\n");
		printf("3��ͼ����Ϣ�����ͼ������\n");
		printf("4��ͼ����Ϣ��ľ�ͼ��ĳ���\n");
		printf("5��ͼ����Ϣ��İ���Ų���\n");
		printf("6��ͼ����Ϣ��İ��۸��������\n");
		printf("7��ͼ����Ϣ��İ��۸���������\n");
		printf("8������ָ����ţ�����ͼ��۸���޸�\n");
		printf("9��ͼ��۸��յ�\n");
		printf("10��ͼ����Ϣ������ͼ��Ĳ���\n");
		printf("11��ͼ����Ϣ���ͼ��ȥ��\n");
		printf("12��ͼ����Ϣ��İ���������\n");
		printf("\nPlease enter the required function number:");
		scanf("%d", &FirstChoose);
		switch (FirstChoose) {
//		case 0:
//			if(Updata_books(L)){
//				printf("�޸�txt�ļ��ɹ�!\n");
//			}else{
//				printf("�޸�txt�ļ�ʧ��\n");
//			}	
		case 1:
			system("cls");
			printf("�ɹ��˳�ϵͳ\n");
			return 0;
		case 2:
		if (WhetherReset(status)) {
			CreateBookList(L);
			read_books(&L, status);
			printf("Create table succeeded complete.\n");
			system("pause");
			break;
			}
			else
			{
				printf("Reset cancelled.\n");
				system("pause");
				break;
			}
		case 3:
			Insert_BookList(L);//	ͼ����Ϣ�����ͼ������
			system("pause");
			break;
		case 4:
			DeleteBookList(L);
			system("pause");
			break;
		case 5:
			SearchBookIsbn(L);
			system("pause");
			break;
		case 6:
			SearchBookPriceRange(L);
			system("pause");
			break;
		case 7:
			PriceAscendingSort(L);//	ͼ����Ϣ��İ��۸���������
			system("pause");
			break;
		case 8:
			ReviseAccordingBookPrice(L);//	����ָ����ţ�����ͼ��۸���޸�
			system("pause");
			break;
		case 9:
		    PriceIncrease(L);//	ͼ��۸��յ�
			system("pause");
			break;
		case 10:
			SearchBookPriceBest(L);//ͼ����Ϣ������ͼ��Ĳ���
			system("pause");
			break;
		case 11:
			DeleteDuplicateBooks(L);
			system("pause");
			break;
		case 12:
			SearchBookName(L);
		 	system("pause");
			break;
       	default:
			printf("����error!\n\a");
			system("pause");
			break;
		}
	}
	return 0; 
}

