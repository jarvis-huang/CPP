#include "stdio.h"
#include "stdlib.h"  //用到malloc(),free()函数
#include "ctype.h"   //用到isdigit()函数

#define MAX 1000    //初始时malloc的byte数

typedef struct Map
{
	unsigned m_size;
	char *m_addr;
	struct Map *next,*prev;    //next后表项，prev前表项
} Map;

void PromptInstructions(void);   //开始时显示用户提示信息

int lmalloc(Map **p,char *head, unsigned size);
int lfree   (Map **p,char *head, unsigned size, unsigned addr);
//head是程序一开始malloc 1000个byte的首地址,是世纪内存地址（绝对地址），而addr是相对地址，即偏移量。
//lmalloc返回分配到的空间的首地址，若没找到，返回NULL
//lfree返回 1（释放成功），0（释放失败）

void PrintResult (char *head, Map *p);  //打印表格，显示内存状态

int WhichCommand(unsigned *size, unsigned *addr);   
/* 处理用户输入的指令，判别是哪条指令（lmalloc, lfree, exit还是free）并提取参数 
   返回值：0-用户输入有误  1-lmalloc指令  2-lfree指令  3-freeall指令
           4-exit指令
*/

void FreeAll(Map **p,char *head); //新增功能，释放所有占用区，恢复到初始状态

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
	char *a;   //用于返回地址
	Map *bp=*p;  //移动寻找指针

	do
	{
		if(bp->m_size>=size)  //找到大小不小于size的空闲区
		{
			a=bp->m_addr;
			bp->m_addr+=size;
			if( (bp->m_size-=size)==0 ) //大小正好相等
			{
				if(bp->next==bp) {;}   //全满
				else
				{
				bp->prev->next=bp->next;   //释放该空闲区，前后相接
				bp->next->prev=bp->prev;
				*p=bp->next;       //记住指针位置，为下一次循环首次所用
				free(bp);
				}
			}
			else {*p=bp;}          //记住指针位置，为下一次循环首次所用
			PrintResult(head,*p);    //打印表格
			printf("%u bytes of space have been allocated.\n"
				   "The returned address is %u.\n\n", size, a-head);
			return (a-head);
		}
		else {bp=bp->next;}
	}
	while(bp!=*p);  //是否找了一圈还没找到
	printf("\nOut of memory.\n\n");  //找了一圈还没找到，表示无法lmalloc
	return NULL;
}

int lfree (Map **p, char *head, unsigned size, unsigned addr)
{
	Map *bp=*p,*insert=(Map *)malloc(sizeof(Map));
	char *before, *after;    //before前空闲区的尾部位置，after后空闲区的头部位置
							 //用来确定是哪种情况

	if(addr+size > MAX)   //超过了1000个byte
	{
		printf("\nFreeing not allowed.\n\n");
		return 0;
	}
	else if(bp->m_size==0)    //没有空闲区，lfree总能执行
	{
			(*p)->m_addr=addr+head;
			(*p)->m_size=size;
	}
	else
	{
		while(bp->next->m_addr > bp->m_addr)  //找最后一个空闲区（m_addr最大者）
		{
			bp=bp->next;
		}

		for(1; bp->m_addr > addr+head && bp->prev->m_addr < bp->m_addr; bp=bp->prev);
		//往前找，找到addr位置前面停下，若找不到（如addr在第一块空闲区前面），则停留在第一个空闲区（m_addr最小者）

		if(addr+head < bp->m_addr) {before=head-1;after=bp->m_addr;bp=bp->prev;}
		//addr在第一块空闲区前面是特殊情况，令before=head-1表示不可能与前空闲区相接
		else 
		{
			before=bp->m_addr+bp->m_size;
			if(bp->next->m_addr <= bp->m_addr) {after=head+MAX+1;}
			//addr在最后一块空闲区后面也是特殊情况，令after=head+MAX+1表示不可能与后空闲区相接
			else {after=bp->next->m_addr;}
		}
	
		if(addr+head < before || addr+head+size > after)  //lfree到了空闲区，不允许
		{
			printf("\nFreeing not allowed.\n\n");
			return 0;
		}

		if(before == addr+head)     // 情况 1,2（与前空闲区相接）
		{
			bp->m_size+=size;
			if(after == addr+head+size) // 情况 2（同时与后空闲区相接）
			{
				bp->m_size+=bp->next->m_size; 
				if(*p==bp->next) {*p=bp;}
				bp=bp->next;
				bp->prev->next=bp->next;
				bp->next->prev=bp->prev;
				free(bp);              //合并后，free掉一个空闲区（表项）
			}
		}
		else
		{
			if(after == addr+head+size)  // 情况 3（与后空闲区相接）
			{
				bp->next->m_addr-=size;
				bp->next->m_size+=size;
			}
			else						// 情况 4（前、后空闲区都不相接）
			{
				insert->m_addr=addr+head;  //建立一个新空闲区（表项）
				insert->m_size=size;
				insert->next=bp->next;
				insert->prev=bp;
				insert->next->prev=insert;
				insert->prev->next=insert;
			}
		}
	}
	PrintResult(head,*p);             //打印表格
	return 1;
}

void PrintResult (char *head, Map *p)
{	
	if(p->m_size==0)
	{
		printf("\nThe memory is completely full. No free spaces.\n\n");     //如果没有空闲区
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
	char line[20];    //用于存储用户输入的整个字符串
	int i;

	gets(line);       //读一行
	
	switch(line[0])   //察看第一个字符
	{
	case 'e':         //若为e,后面必须什么字符也没有
		if(line[1]=='\0') {return 4;}
		return 0;
		break;
	case 'm':         //若为m,后面必须是一个空格加一个整数
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
	case 'f':       //若为f,后面必须是空格+整数+空格+整数 或者 是'reeall'
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
	default :    //其它情况，一概属于错误指令
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
		free(move->prev);   //依次释放除一个外的所有表项
	}
	(*p)->m_addr=head;      //修改参数
	(*p)->m_size=MAX;
	(*p)->next=(*p)->prev=(*p);
	PrintResult(head,*p);   //打印表格
}




