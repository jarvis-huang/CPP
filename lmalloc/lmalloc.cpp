#include "stdio.h"
#include "stdlib.h"  //�õ�malloc(),free()����
#include "ctype.h"   //�õ�isdigit()����

#define MAX 1000    //��ʼʱmalloc��byte��

typedef struct Map
{
	unsigned m_size;
	char *m_addr;
	struct Map *next,*prev;    //next����prevǰ����
} Map;

void PromptInstructions(void);   //��ʼʱ��ʾ�û���ʾ��Ϣ

int lmalloc(Map **p,char *head, unsigned size);
int lfree   (Map **p,char *head, unsigned size, unsigned addr);
//head�ǳ���һ��ʼmalloc 1000��byte���׵�ַ,�������ڴ��ַ�����Ե�ַ������addr����Ե�ַ����ƫ������
//lmalloc���ط��䵽�Ŀռ���׵�ַ����û�ҵ�������NULL
//lfree���� 1���ͷųɹ�����0���ͷ�ʧ�ܣ�

void PrintResult (char *head, Map *p);  //��ӡ�����ʾ�ڴ�״̬

int WhichCommand(unsigned *size, unsigned *addr);   
/* �����û������ָ��б�������ָ�lmalloc, lfree, exit����free������ȡ���� 
   ����ֵ��0-�û���������  1-lmallocָ��  2-lfreeָ��  3-freeallָ��
           4-exitָ��
*/

void FreeAll(Map **p,char *head); //�������ܣ��ͷ�����ռ�������ָ�����ʼ״̬

void main (void)
{
	Map *p=(Map *)malloc(sizeof(Map));
	char *head;
	unsigned size,addr,command;

	// Initializing the map.
	p->m_size=MAX;
	head=p->m_addr=(char*)malloc(MAX);
	p->next=p->prev=p;

	PromptInstructions();
	PrintResult(head,p);
	while(1)
	{
		command=WhichCommand(&size,&addr);
		if(command==0) {printf("Bad command. Retry.\n\n");}
		if(command==4) {break;}
		if(command==1) {lmalloc(&p,head,size);}
		if(command==2) {lfree(&p,head,size,addr);}
		if(command==3) {FreeAll(&p,head);}
	}
}

int lmalloc(Map **p, char *head, unsigned size)
{
	char *a;   //���ڷ��ص�ַ
	Map *bp=*p;  //�ƶ�Ѱ��ָ��

	do
	{
		if(bp->m_size>=size)  //�ҵ���С��С��size�Ŀ�����
		{
			a=bp->m_addr;
			bp->m_addr+=size;
			if( (bp->m_size-=size)==0 ) //��С�������
			{
				if(bp->next==bp) {;}   //ȫ��
				else
				{
				bp->prev->next=bp->next;   //�ͷŸÿ�������ǰ�����
				bp->next->prev=bp->prev;
				*p=bp->next;       //��סָ��λ�ã�Ϊ��һ��ѭ���״�����
				free(bp);
				}
			}
			else {*p=bp;}          //��סָ��λ�ã�Ϊ��һ��ѭ���״�����
			PrintResult(head,*p);    //��ӡ���
			printf("%u bytes of space have been allocated.\n"
				   "The returned address is %u.\n\n", size, a-head);
			return (a-head);
		}
		else {bp=bp->next;}
	}
	while(bp!=*p);  //�Ƿ�����һȦ��û�ҵ�
	printf("\nOut of memory.\n\n");  //����һȦ��û�ҵ�����ʾ�޷�lmalloc
	return NULL;
}

int lfree (Map **p, char *head, unsigned size, unsigned addr)
{
	Map *bp=*p,*insert=(Map *)malloc(sizeof(Map));
	char *before, *after;    //beforeǰ��������β��λ�ã�after���������ͷ��λ��
							 //����ȷ�����������

	if(addr+size > MAX)   //������1000��byte
	{
		printf("\nFreeing not allowed.\n\n");
		return 0;
	}
	else if(bp->m_size==0)    //û�п�������lfree����ִ��
	{
			(*p)->m_addr=addr+head;
			(*p)->m_size=size;
	}
	else
	{
		while(bp->next->m_addr > bp->m_addr)  //�����һ����������m_addr����ߣ�
		{
			bp=bp->next;
		}

		for(1; bp->m_addr > addr+head && bp->prev->m_addr < bp->m_addr; bp=bp->prev);
		//��ǰ�ң��ҵ�addrλ��ǰ��ͣ�£����Ҳ�������addr�ڵ�һ�������ǰ�棩����ͣ���ڵ�һ����������m_addr��С�ߣ�

		if(addr+head < bp->m_addr) {before=head-1;after=bp->m_addr;bp=bp->prev;}
		//addr�ڵ�һ�������ǰ���������������before=head-1��ʾ��������ǰ���������
		else 
		{
			before=bp->m_addr+bp->m_size;
			if(bp->next->m_addr <= bp->m_addr) {after=head+MAX+1;}
			//addr�����һ�����������Ҳ�������������after=head+MAX+1��ʾ�����������������
			else {after=bp->next->m_addr;}
		}
	
		if(addr+head < before || addr+head+size > after)  //lfree���˿�������������
		{
			printf("\nFreeing not allowed.\n\n");
			return 0;
		}

		if(before == addr+head)     // ��� 1,2����ǰ��������ӣ�
		{
			bp->m_size+=size;
			if(after == addr+head+size) // ��� 2��ͬʱ����������ӣ�
			{
				bp->m_size+=bp->next->m_size; 
				if(*p==bp->next) {*p=bp;}
				bp=bp->next;
				bp->prev->next=bp->next;
				bp->next->prev=bp->prev;
				free(bp);              //�ϲ���free��һ�������������
			}
		}
		else
		{
			if(after == addr+head+size)  // ��� 3������������ӣ�
			{
				bp->next->m_addr-=size;
				bp->next->m_size+=size;
			}
			else						// ��� 4��ǰ���������������ӣ�
			{
				insert->m_addr=addr+head;  //����һ���¿����������
				insert->m_size=size;
				insert->next=bp->next;
				insert->prev=bp;
				insert->next->prev=insert;
				insert->prev->next=insert;
			}
		}
	}
	PrintResult(head,*p);             //��ӡ���
	return 1;
}

void PrintResult (char *head, Map *p)
{	
	if(p->m_size==0)
	{
		printf("\nThe memory is completely full. No free spaces.\n\n");     //���û�п�����
		return;
	}
	while(p->prev->m_addr<p->m_addr)
	{
		p=p->prev;
	}

	printf("\n                              Free Spaces            \n");
	printf("                ________________________________________\n");
	printf("                         range          size  \n");
	printf("                ----------------------------------------\n");
	
	do
	{
	printf("%26u ~ %-4u%11u\n",p->m_addr-head,p->m_addr-head+p->m_size-1,p->m_size);
	p=p->next;
	}
	while(p->prev->m_addr<p->m_addr);
	printf("\n\n");
}

void PromptInstructions(void)
{
	printf("\nINSTRUCTIONS:\n\n"
			"Dear user, 1000 bytes of free memory have been allocated for you.\n"
			"You can choose to perform 4 commands.\n\n"
			"To allocate free spaces, please type:\nm size\n"
			"To free used spaces, please type:\nf size address\n"
			"To free all spaces and return to the initial condition, please type:\nfreeall\n"
			"To exit, type 'e'\n"
			"NOTE: Except from using 'freeall', you are not allowed to free spaces which are already freed!\n\n");
}


int WhichCommand(unsigned *size, unsigned *addr)    
{
	char line[20];    //���ڴ洢�û�����������ַ���
	int i;

	gets(line);       //��һ��
	
	switch(line[0])   //�쿴��һ���ַ�
	{
	case 'e':         //��Ϊe,�������ʲô�ַ�Ҳû��
		if(line[1]=='\0') {return 4;}
		return 0;
		break;
	case 'm':         //��Ϊm,���������һ���ո��һ������
		if (line[1]!=' ') {return 0;}
		else
		{
			for(i=2;line[i]!='\0';i++)
			{
				if(!isdigit(line[i])) {return 0;}
			}
			sscanf(line,"m %u",size);
			return !(i==2);
		}
		break;
	case 'f':       //��Ϊf,��������ǿո�+����+�ո�+���� ���� ��'reeall'
		if(line[1]=='r' && line[2]=='e' && line[3]=='e' && 
		line[4]=='a' && line[5]=='l' && line[6]=='l' && line[7]=='\0')
		{return 3;}
		else if (line[1]!=' ') {return 0;}
		else
		{
			for(i=2;line[i]!=' ';i++)
			{
				if(!isdigit(line[i])) {return 0;}
			}
			if (i==2 || line[i+1]=='\0') {return 0;}
			for(i=i+1;line[i]!='\0';i++)
			{
				if(!isdigit(line[i])) {return 0;}
			}
			sscanf(line,"f %u %u",size,addr);
			return 2;
		}
		break;
	default :    //���������һ�����ڴ���ָ��
		return 0;
		break;
	}
}

void FreeAll(Map **p, char *head)
{
	Map *move=(*p)->next;

	while(move->m_addr != (*p)->m_addr)
	{
		move=move->next;
		free(move->prev);   //�����ͷų�һ��������б���
	}
	(*p)->m_addr=head;      //�޸Ĳ���
	(*p)->m_size=MAX;
	(*p)->next=(*p)->prev=(*p);
	PrintResult(head,*p);   //��ӡ���
}




