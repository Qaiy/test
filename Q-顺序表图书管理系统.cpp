//!!!顺序表实现图书管理系统 
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100			//顺序表可能达到的最大长度
typedef int Status; //Status 是函数返回值类型，其值是函数结果状态代码。
//定义一个包含图书信息（书号、书名、价格）的顺序表
struct Book{
	char id[30];
	char name[30];
	double price;
}; 
typedef struct
{
	int length;//当前顺序表长度
	Book* elem;//定义顺序表中元素类型的数组指针
}SqList;
//0.顺序表的初始化 
Status CreateBookList(SqList &L) {
	L.elem = new Book[MAXSIZE]; //为顺序表分配一个大小为MAXSIZE的数组空间
	if (!L.elem) {
		printf("顺序表初始化失败!\a\n");
		exit(OVERFLOW); //存储分配失败退出
	}
	L.length = 0; //空表长度为0
	printf("顺序表初始化成功！\n");
	return OK;
}
//1.	图书信息表的创建和输出
//读书籍数据
int read_books(SqList* L, bool& status) {
 	int i = 0;
	FILE* fp;
	if ((fp = fopen("D://book1.txt", "r")) == NULL) {
		printf("\a");
		puts("找不到该文件，打开失败!");
		return 0;
	} 
	while (!feof(fp)) {
		fscanf(fp, "%s%s%lf\n", L->elem[i].id, L->elem[i].name, &L->elem[i].price);
		printf("%s\t%s\t%.2lf元\n", L->elem[i].id, L->elem[i].name, L->elem[i].price);
		i++;
		L->length++;
	}
	fclose(fp);
	return 1; 
}
//打印顺序表内容 
void print(SqList L) {
	for (int i = 0; i < L.length; i++) {
		printf("%s\t%s\t%.2lf元\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
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
//2.	图书信息表的新图书的入库
//2上架新图书
Status Insert_BookList(SqList& L) {
	SqList* base;
	Book e;
	int location;
	printf("Please enter the position you want to insert:");
	scanf("%d", &location);
	if (L.length < 0) {
		printf("Error:The order table not created!\a\n");
		return ERROR;               //当长度小于0就是未创建内存，不允许插入数据
	}
	if (L.length >= MAXSIZE) {        //长度大于顺序表最大值时不允许插入数据
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
	printf("请输入ISBN-Name-Price:");
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
//3.	图书信息表的旧图书出库
//3下架旧图书(输入书号)
Status DeleteBookList(SqList& L) {
	char isbn[15];
	if (L.length < 0) {
		printf("Error:No books on the shelves!\a\n");
		return ERROR;               //当长度小于0就是未创建内存，不允许删除数据
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
//4.	图书信息表的按书号查找
//4看书号查找
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
			printf("%s\t%s\t%.2lf元\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
			return OK;
		}
	}
	printf("ERROR:Books don't exist!\n\a");
	return ERROR;
}
//按书名查找
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
			printf("%s\t%s\t%.2lf元\n", L.elem[i].id, L.elem[i].name, L.elem[i].price);
			return OK;
		}
	}
	printf("ERROR:Books don't exist!\n\a");
	return ERROR;
}
//5.	图书信息表的按价格区间查找
//5基于价格区间查找
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
//6.	图书信息表的按价格升序排序
//6价格升序排序
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
//7.	根据指定书号，进行图书价格的修改
//7按图书价格修改
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
//8.	图书价格普调
/*
	8按图书价格普调 (计算所有图书的平均价格，将所有低于平均价格的图书价格提高 20%，
	 所有高于或等于平均价格的图书价格提高 10%，最后逐行输出价格修改后的全部图书信息。)
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
	printf("The average price: %lf 元\n", average);
	printf("The price has been raised successfully.\n");
	return OK;
}	
//9.	图书信息表的最贵图书的查找
//9按最贵图书查找
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
//10. 图书信息表的图书去重
//10图书去重
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
//		printf("0、修改txt文件\n");
		printf("1、退出系统\n");
		printf("2、初始化单链表及图书信息表的创建和输出\n");
		printf("3、图书信息表的新图书的入库\n");
		printf("4、图书信息表的旧图书的出库\n");
		printf("5、图书信息表的按书号查找\n");
		printf("6、图书信息表的按价格区间查找\n");
		printf("7、图书信息表的按价格升序排序\n");
		printf("8、根据指定书号，进行图书价格的修改\n");
		printf("9、图书价格普调\n");
		printf("10、图书信息表的最贵图书的查找\n");
		printf("11、图书信息表的图书去重\n");
		printf("12、图书信息表的按书名查找\n");
		printf("\nPlease enter the required function number:");
		scanf("%d", &FirstChoose);
		switch (FirstChoose) {
//		case 0:
//			if(Updata_books(L)){
//				printf("修改txt文件成功!\n");
//			}else{
//				printf("修改txt文件失败\n");
//			}	
		case 1:
			system("cls");
			printf("成功退出系统\n");
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
			Insert_BookList(L);//	图书信息表的新图书的入库
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
			PriceAscendingSort(L);//	图书信息表的按价格升序排序
			system("pause");
			break;
		case 8:
			ReviseAccordingBookPrice(L);//	根据指定书号，进行图书价格的修改
			system("pause");
			break;
		case 9:
		    PriceIncrease(L);//	图书价格普调
			system("pause");
			break;
		case 10:
			SearchBookPriceBest(L);//图书信息表的最贵图书的查找
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
			printf("输入error!\n\a");
			system("pause");
			break;
		}
	}
	return 0; 
}

