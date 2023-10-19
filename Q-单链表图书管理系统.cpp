//!!!单链表实现图书管理系统 
#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>

//定义一个包含图书信息（书号、书名、价格）的链表
struct Book{
	char id[30];
	char name[30];
	double price;
}; 
typedef struct LNode{      
    Book data;      
    struct LNode *next;
}LNode, *LinkList;
// 初始化一个单链表（带头结点）
bool InitList(LinkList &L){      
    L = (LNode *)malloc(sizeof(LNode));  //分配一个头结点 
    if (L == NULL)        //内存不足，分配失败    
        return false;    
    L->next = NULL;       //头结点之后暂时还没有结点   
    return true;
}
bool Empty(LinkList L){  
    if (L->next == NULL) 
        return true;     
    else             
        return false;
}
//0. 修改txt文件
//bool Updata_books(LinkList &L){
//	FILE* fp;
//	if ((fp = fopen("D:\\book1.txt", "a+")) == NULL) {
//		puts("文件打开失败!\a\n");
//		return false;
//	}
// 
//	//数据写入文件
//	rewind(fp);
//	LNode *p = L;
//	while (p->next != NULL) {
//		p = p->next;
//		fprintf(fp, "请输入id-name-price: %s %s %.2lf\n", p->data.id, p->data.name, p->data.price);
//	}
//	fclose(fp);
//	return true;
//}
//1.	图书信息表的创建和输出
LinkList List_TailInsert(LinkList &L){
    FILE *file;
    if((file = fopen("D:\\book1.txt", "r"))==NULL)
    {
        printf("找不到该文件，打开失败!\n");
        return 0;
    }
    LNode *s, *r = L;                        //r为表尾指针
    while(!feof(file)){
    	s = (LNode *)malloc(sizeof(LNode));//申请空间
    	fscanf(file,"%s %s %lf \n",s->data.id,s->data.name,&s->data.price);
    	s->next=NULL;
    	r->next=s;           
        r=s;                               //r指针指向新的表尾结点
	}
	 r->next = NULL;                          //尾结点指针置空    
	 fclose(file);
	 return L;
}
void PrintList(LinkList L)
{
	if(L == NULL) {
	 printf("图书管理信息表不存在！\n"); 
	 return; 
	 }//检查是否传入空指针。
	
	if(L->next == NULL) {
	 printf("图书管理信息表为空！\n"); 
	 return; }
	
	LNode *p;
    p = L->next;
	printf("-------------------------------------------------------\n") ; 
	while(p!=NULL)
	{
		printf("%s \t %s \t\t %.2f元 \n",p->data.id,p->data.name,p->data.price); //逐行打印信息。  
		p=p->next; //指针指向下一结点 。 
	}
	printf("-------------------------------------------------------\n") ;  
}
//按位置查找 返回对应位置的节点 
LNode * GetElem(LinkList L, int i){   
    if(i<0)            
        return NULL;    
    LNode *p;//指针p指向当前扫描到的节点     
    int j=0; //当前p指向的是第几个节点   
    p = L; //L指向头节点，头节点是第0个节点（不存放数据）    
    while(p!=NULL && j<i){   
        p = p->next;     
        j++;      
    }        
    return p;
}
//后插法！！！ 
// 在结点p后插入元素e
bool InsertNextNode(LNode *p){
    Book e;      
    if(p==NULL){         
        return false;   
    }    
    LNode *s = (LNode *)malloc(sizeof(LNode));     
    if(s==NULL)     
        return false;
	printf("请输入id-name-price:");
	scanf("%s %s %lf",&e.id,&e.name,&e.price);	    
    s->data = e;     
    s->next = p->next;  
    p->next = s;     
    return true;
}
// 封装后的插入操作，在第i个位置插入元素e，可以调用查询操作和后插操作
//2.	图书信息表的新图书的入库
bool ListInsert(LinkList &L, int i){  
    if(i<1)             
        return false; 
    // 找到第i-1个元素     
    LNode *p = GetElem(L, i-1);   
    // 在p结点后插入元素e     
    return InsertNextNode(p);
}
// 删除第i个结点
//3.	图书信息表的旧图书出库
bool ListDelete(LinkList &L, int i){      
    if(i<1)             
        return false;        
    LNode *p = GetElem(L, i-1);    
    if(p==NULL)       
        return false;    
    if(p->next == NULL)        
        return false;    	   
    //令q暂时保存被删除的结点   
    LNode *q = p->next;     	     
    p->next = q->next;      
    free(q) ;   
    return true;
}
//4.	图书信息表的按书号查找
//按值(书号id)查找,返回书号id对应的书名，价格 
void SearchId(LinkList L){
	char BookId[15];
	printf("请输入要查找书籍的id：");
	scanf("%s",&BookId);           
    LNode *p=L;     
    // 从第一个结点开始查找数据域为e的结点  
    while(p->next){
    	if(!strcmp(BookId,p->next->data.id)){
    		p=p->next;
    		printf("通过id%s查找的书籍为：%s %.2f元\n",p->data.id,p->data.name,p->data.price);
		}
		p=p->next;
	}     
}
//5.	图书信息表的按价格区间查找
void SearchPrice(LinkList L){
	LNode *p=L;
	double min_price,max_price;
	printf("请输入最低price：");
	getchar();
	scanf("%lf",&min_price);
	printf("请输入最高price：");
	getchar();
	scanf("%lf",&max_price);
	while(p->next){
		if(p->next->data.price>=min_price&&p->next->data.price<=max_price){
			printf("%s %s %.2f\n",p->next->data.id,p->next->data.name,p->next->data.price);
		}
			p=p->next;
	}  
}
//6.图书信息表的按价格升序排序
void LowPriceToHightPrice(LinkList &L){
	LNode *pFirst=L,*pSecond=L,*pEnd=NULL;
	Book temp;
	while(pFirst!=pEnd){
		while(pFirst->next!=pEnd){
			if(pFirst->data.price > pFirst->next->data.price){
				temp=pFirst->data;
				pFirst->data=pFirst->next->data;
				pFirst->next->data=temp;
			}
			pFirst=pFirst->next;
		}
		pEnd=pFirst;
		pFirst=L;
	}
}
//7.	根据指定书号，进行图书价格的修改
void IdToPrice(LinkList &L){
	LNode *p=L;
	char name[15];
	double price;
	printf("请输入id进行对应图书价格修改:");
	getchar();
	scanf("%s", &name);
	printf("修改价格price为:");
	getchar();
	scanf("%lf", &price);
	while (p->next) {
		if (!strcmp(name, p->next->data.id)) {
			p = p->next;
			p->data.price = price;
			printf("%s %s %.2f元\n", p->data.id, p->data.name, p->data.price);
		}
		p = p->next;
	}
}
//8.	图书价格普调	
LinkList PriceAdjust(LinkList &L){
	LNode *p=L;
	int len=0;
	double sum=0;
	double average;
	p=L->next;
	while(p){
		sum+=p->data.price;
		p=p->next;
		len++;
	}
	average=sum/len;
	p=L->next;
	while(p){
		if(average>p->data.price){
			p->data.price+=(p->data.price * 0.2);
		}else{
			p->data.price+=(p->data.price * 0.1);
		}
		p=p->next;
	}
	return L;
}
//9.	图书信息表的最贵图书的查找
void SearchTheBestPriceBook(LinkList &L){
	LNode *p=L->next;
	double expensive=0;
	while(p){
		expensive=expensive < p->data.price ?p->data.price : expensive;
		p=p->next;
	}
	p=L->next;
	while(p){
		if(p->data.price>=expensive){
			printf("最贵的图书为: %s %s %.2f\n",p->data.id,p->data.name,p->data.price);
		}
		p=p->next;
	}
}
//10. 图书信息表的图书去重
void DeleteDuplicateBook(LinkList &L){
//	LinkList p;
//	LinkList mark;
//	LinkList q;
	LNode *p,*mark,*q;
	for (mark = L->next; mark != NULL; mark = mark->next)
	{
		q = mark;
		p = mark->next;
		while (p)
		{
			if (!strcmp(mark->data.id, p->data.id))
			{
				q->next = p->next;
				free(p);
				p = q->next;
			}
			else
			{
				q = p;
				p = p->next;
			}
		}
	}
}
int main(){
	LinkList L;
	int i,FirstChoose;
	   while (true) {
		system("cls");
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
			if(InitList(L)){
				List_TailInsert(L);
				PrintList(L);
			    system("pause");
			    break;
			}else{
				printf("初始化失败");
				return 0; 
			}
		case 3:
			printf("请为新图书选择入库位置place:");
	        scanf("%d", &i);
            if(ListInsert(L,i)){
    	    printf("新图书入库成功!\n");
		    PrintList(L);
		    system("pause");
			break;
	        }else{
		    printf("新图书入库失败!"); 
		    return 0;
	        }
		case 4:
			printf("请选择哪个位置place的旧图书出库:");
	        scanf("%d", &i);
            if(ListDelete(L,i)){
    	    printf("旧图书出库成功!\n");
		    PrintList(L);
		    system("pause");
		   	break;
	    	}else{
			printf("旧图书出库失败!"); 
			return 0;;
			}
		case 5:
			SearchId(L);//5.按值(书号id)查找,返回书号id对应的书名，价格 
			system("pause");
			break;
		case 6:
			SearchPrice(L);//6.	图书信息表的按价格区间查找
			system("pause");
			break;
		case 7:
			LowPriceToHightPrice(L);
		    PrintList(L);
			system("pause");
			break;
		case 8:
			 IdToPrice(L);
   		   	 PrintList(L);
			system("pause");
			break;
		case 9:
			PriceAdjust(L);
  			PrintList(L);
			system("pause");
			break;
		case 10:
			SearchTheBestPriceBook(L);
			system("pause");
			break;
		case 11:
			DeleteDuplicateBook(L);
 			PrintList(L);
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
