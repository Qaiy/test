//!!!������ʵ��ͼ�����ϵͳ 
#include<stdio.h>
#include<stdlib.h>
#include <malloc.h>
#include <string.h>

//����һ������ͼ����Ϣ����š��������۸񣩵�����
struct Book{
	char id[30];
	char name[30];
	double price;
}; 
typedef struct LNode{      
    Book data;      
    struct LNode *next;
}LNode, *LinkList;
// ��ʼ��һ����������ͷ��㣩
bool InitList(LinkList &L){      
    L = (LNode *)malloc(sizeof(LNode));  //����һ��ͷ��� 
    if (L == NULL)        //�ڴ治�㣬����ʧ��    
        return false;    
    L->next = NULL;       //ͷ���֮����ʱ��û�н��   
    return true;
}
bool Empty(LinkList L){  
    if (L->next == NULL) 
        return true;     
    else             
        return false;
}
//0. �޸�txt�ļ�
//bool Updata_books(LinkList &L){
//	FILE* fp;
//	if ((fp = fopen("D:\\book1.txt", "a+")) == NULL) {
//		puts("�ļ���ʧ��!\a\n");
//		return false;
//	}
// 
//	//����д���ļ�
//	rewind(fp);
//	LNode *p = L;
//	while (p->next != NULL) {
//		p = p->next;
//		fprintf(fp, "������id-name-price: %s %s %.2lf\n", p->data.id, p->data.name, p->data.price);
//	}
//	fclose(fp);
//	return true;
//}
//1.	ͼ����Ϣ��Ĵ��������
LinkList List_TailInsert(LinkList &L){
    FILE *file;
    if((file = fopen("D:\\book1.txt", "r"))==NULL)
    {
        printf("�Ҳ������ļ�����ʧ��!\n");
        return 0;
    }
    LNode *s, *r = L;                        //rΪ��βָ��
    while(!feof(file)){
    	s = (LNode *)malloc(sizeof(LNode));//����ռ�
    	fscanf(file,"%s %s %lf \n",s->data.id,s->data.name,&s->data.price);
    	s->next=NULL;
    	r->next=s;           
        r=s;                               //rָ��ָ���µı�β���
	}
	 r->next = NULL;                          //β���ָ���ÿ�    
	 fclose(file);
	 return L;
}
void PrintList(LinkList L)
{
	if(L == NULL) {
	 printf("ͼ�������Ϣ�����ڣ�\n"); 
	 return; 
	 }//����Ƿ����ָ�롣
	
	if(L->next == NULL) {
	 printf("ͼ�������Ϣ��Ϊ�գ�\n"); 
	 return; }
	
	LNode *p;
    p = L->next;
	printf("-------------------------------------------------------\n") ; 
	while(p!=NULL)
	{
		printf("%s \t %s \t\t %.2fԪ \n",p->data.id,p->data.name,p->data.price); //���д�ӡ��Ϣ��  
		p=p->next; //ָ��ָ����һ��� �� 
	}
	printf("-------------------------------------------------------\n") ;  
}
//��λ�ò��� ���ض�Ӧλ�õĽڵ� 
LNode * GetElem(LinkList L, int i){   
    if(i<0)            
        return NULL;    
    LNode *p;//ָ��pָ��ǰɨ�赽�Ľڵ�     
    int j=0; //��ǰpָ����ǵڼ����ڵ�   
    p = L; //Lָ��ͷ�ڵ㣬ͷ�ڵ��ǵ�0���ڵ㣨��������ݣ�    
    while(p!=NULL && j<i){   
        p = p->next;     
        j++;      
    }        
    return p;
}
//��巨������ 
// �ڽ��p�����Ԫ��e
bool InsertNextNode(LNode *p){
    Book e;      
    if(p==NULL){         
        return false;   
    }    
    LNode *s = (LNode *)malloc(sizeof(LNode));     
    if(s==NULL)     
        return false;
	printf("������id-name-price:");
	scanf("%s %s %lf",&e.id,&e.name,&e.price);	    
    s->data = e;     
    s->next = p->next;  
    p->next = s;     
    return true;
}
// ��װ��Ĳ���������ڵ�i��λ�ò���Ԫ��e�����Ե��ò�ѯ�����ͺ�����
//2.	ͼ����Ϣ�����ͼ������
bool ListInsert(LinkList &L, int i){  
    if(i<1)             
        return false; 
    // �ҵ���i-1��Ԫ��     
    LNode *p = GetElem(L, i-1);   
    // ��p�������Ԫ��e     
    return InsertNextNode(p);
}
// ɾ����i�����
//3.	ͼ����Ϣ��ľ�ͼ�����
bool ListDelete(LinkList &L, int i){      
    if(i<1)             
        return false;        
    LNode *p = GetElem(L, i-1);    
    if(p==NULL)       
        return false;    
    if(p->next == NULL)        
        return false;    	   
    //��q��ʱ���汻ɾ���Ľ��   
    LNode *q = p->next;     	     
    p->next = q->next;      
    free(q) ;   
    return true;
}
//4.	ͼ����Ϣ��İ���Ų���
//��ֵ(���id)����,�������id��Ӧ���������۸� 
void SearchId(LinkList L){
	char BookId[15];
	printf("������Ҫ�����鼮��id��");
	scanf("%s",&BookId);           
    LNode *p=L;     
    // �ӵ�һ����㿪ʼ����������Ϊe�Ľ��  
    while(p->next){
    	if(!strcmp(BookId,p->next->data.id)){
    		p=p->next;
    		printf("ͨ��id%s���ҵ��鼮Ϊ��%s %.2fԪ\n",p->data.id,p->data.name,p->data.price);
		}
		p=p->next;
	}     
}
//5.	ͼ����Ϣ��İ��۸��������
void SearchPrice(LinkList L){
	LNode *p=L;
	double min_price,max_price;
	printf("���������price��");
	getchar();
	scanf("%lf",&min_price);
	printf("���������price��");
	getchar();
	scanf("%lf",&max_price);
	while(p->next){
		if(p->next->data.price>=min_price&&p->next->data.price<=max_price){
			printf("%s %s %.2f\n",p->next->data.id,p->next->data.name,p->next->data.price);
		}
			p=p->next;
	}  
}
//6.ͼ����Ϣ��İ��۸���������
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
//7.	����ָ����ţ�����ͼ��۸���޸�
void IdToPrice(LinkList &L){
	LNode *p=L;
	char name[15];
	double price;
	printf("������id���ж�Ӧͼ��۸��޸�:");
	getchar();
	scanf("%s", &name);
	printf("�޸ļ۸�priceΪ:");
	getchar();
	scanf("%lf", &price);
	while (p->next) {
		if (!strcmp(name, p->next->data.id)) {
			p = p->next;
			p->data.price = price;
			printf("%s %s %.2fԪ\n", p->data.id, p->data.name, p->data.price);
		}
		p = p->next;
	}
}
//8.	ͼ��۸��յ�	
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
//9.	ͼ����Ϣ������ͼ��Ĳ���
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
			printf("����ͼ��Ϊ: %s %s %.2f\n",p->data.id,p->data.name,p->data.price);
		}
		p=p->next;
	}
}
//10. ͼ����Ϣ���ͼ��ȥ��
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
			if(InitList(L)){
				List_TailInsert(L);
				PrintList(L);
			    system("pause");
			    break;
			}else{
				printf("��ʼ��ʧ��");
				return 0; 
			}
		case 3:
			printf("��Ϊ��ͼ��ѡ�����λ��place:");
	        scanf("%d", &i);
            if(ListInsert(L,i)){
    	    printf("��ͼ�����ɹ�!\n");
		    PrintList(L);
		    system("pause");
			break;
	        }else{
		    printf("��ͼ�����ʧ��!"); 
		    return 0;
	        }
		case 4:
			printf("��ѡ���ĸ�λ��place�ľ�ͼ�����:");
	        scanf("%d", &i);
            if(ListDelete(L,i)){
    	    printf("��ͼ�����ɹ�!\n");
		    PrintList(L);
		    system("pause");
		   	break;
	    	}else{
			printf("��ͼ�����ʧ��!"); 
			return 0;;
			}
		case 5:
			SearchId(L);//5.��ֵ(���id)����,�������id��Ӧ���������۸� 
			system("pause");
			break;
		case 6:
			SearchPrice(L);//6.	ͼ����Ϣ��İ��۸��������
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
			printf("����error!\n\a");
			system("pause");
			break;
		}
	}
	return 0;
}
