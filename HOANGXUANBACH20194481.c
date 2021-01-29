#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>


typedef struct _QUEUE_ELEMENT
{
	char id[1024];
    char ram[1024];
	struct _QUEUE_ELEMENT* link;
}QUEUE_ELEMENT, *PQUEUE_ELEMENT;

typedef struct _QUEUE
{
	PQUEUE_ELEMENT Front;
	PQUEUE_ELEMENT Rear;	
	int size;
}QUEUE, *PQUEUE;


int IsEmpty(PQUEUE pQueue)
{
	if (pQueue->Front == NULL && pQueue->Rear == NULL)
		return 1;
	else
		return 0;
}
void Enqueue(PQUEUE pQueue, char* id,char* ram)
{
	PQUEUE_ELEMENT newElement = (PQUEUE_ELEMENT)calloc(1, sizeof(QUEUE_ELEMENT));
	strcpy(newElement->id, id);
    strcpy(newElement->ram, ram);
	newElement->link = NULL;
	if (IsEmpty(pQueue))
	{
		pQueue->Front = newElement;
		pQueue->Rear = newElement;
	}else{
		pQueue->Rear->link = newElement;
		pQueue->Rear = newElement;
	}
	pQueue->size += 1;
}
void Pushqueue(PQUEUE pQueue, char* id,char* ram)
{
	PQUEUE_ELEMENT newElement = (PQUEUE_ELEMENT)calloc(1, sizeof(QUEUE_ELEMENT));
	strcpy(newElement->id, id);
    strcpy(newElement->ram, ram);
	newElement->link = NULL;
	if (IsEmpty(pQueue))
	{
		pQueue->Front = newElement;
		pQueue->Rear = newElement;
	}else{
		newElement->link = pQueue->Front;
		pQueue->Front = newElement;
	}
	pQueue->size += 1;
}
PQUEUE_ELEMENT Dequeue(PQUEUE pQueue)
{
	if (IsEmpty(pQueue))
		return NULL; //Khong lay duoc
	else
	{
		PQUEUE_ELEMENT oldElement = pQueue->Front;
		pQueue->Front = pQueue->Front->link;
		if (pQueue->Front == NULL)
		{
			pQueue->Rear = NULL;
		}
		pQueue->size -= 1;
		return oldElement; //Lay thanh cong
	}
}
void Free(PQUEUE pQueue)
{
	while (Dequeue(pQueue) != NULL);
}

void printqueue(PQUEUE danhsach)
{
    QUEUE_ELEMENT* tmp = (PQUEUE_ELEMENT)calloc(1,sizeof(QUEUE_ELEMENT));
    tmp = danhsach->Front;
    while(tmp != NULL)
    {
        printf("%-5s%-5s\n",tmp->id,tmp->ram);
        tmp = tmp->link;
    }
}

void Chuyeni(char* id)
{
    id[0] = 'i';
}
void DocFile(PQUEUE danhsach)
{
	{
        int slvao = 0;
        int slx;
        char* file = (char*)calloc(1024,sizeof(char));
        printf("Nhap ten file :");
        __fpurge(stdin);
        fgets(file,1024,stdin);
        file[strlen(file) - 1] = '\0';
		FILE* f = fopen(file,"rt");
		if(f == NULL)
		{
			printf("Khong mo duoc file.\n");
            return;
		}
		else
		{
			char* sl = (char*)calloc(30,sizeof(char));  
 			char* id = (char*)calloc(1024,sizeof(char));
			char* ram = (char*)calloc(1024,sizeof(char));
			QUEUE_ELEMENT* new = NULL;
            __fpurge(stdin);
			fgets(sl,30,f);
            sl[strlen(sl) - 1] = '\0';
			printf("so nguoi trong danh ba : %s\n",sl);
            slx = atoi(sl);
			while(danhsach->size < 20)
			{
				memset(id,0,1024);
				memset(ram,0,1024);
                __fpurge(stdin);
                fscanf(f,"%s", id);
                if(strlen(id) == 0)
				{
					break;
				}
                else{
                    Chuyeni(id);
                    __fpurge(stdin);
                    fscanf(f,"%s", ram);
				    Enqueue(danhsach, id, ram);
                    slvao++;
                }
			}
			free(id);
			free(ram);
		}
		fclose(f);
        if(slx > slvao)
        {
            printf("File day khong them dc.\n");
        }
        printf("So luong vao danh sach la : %d \n",slvao);
        printqueue(danhsach);
	}
} 



/*void Themmay(QUEUE* danhsach)
{
    char* name = (char*)calloc(1024,sizeof(char));
    char* phone = (char*)calloc(1024,sizeof(char));
    printf("Nhap ten nguoi mua : ");
    __fpurge(stdin);
    fgets(name,1024,stdin);
    name[strlen(name) - 1] = '\0';
    printf("Nhap so dien thoai nguoi mua : ");
    __fpurge(stdin);
    fgets(phone,1024,stdin);
    phone[strlen(phone) - 1] = '\0';
    Enqueue(danhsach, name, phone);
}
*/
/*void banhang(QUEUE** danhsach,int argc,char** argv)
{
    if(argc < 3)
	{
		printf("Khong du tham so.\n");
	}
	else
	{
        int a,b,c;
		char* desfile = argv[2];
		FILE* f = fopen(desfile,"at");
        PQUEUE_ELEMENT tmp = (PQUEUE_ELEMENT)calloc(1, sizeof(QUEUE_ELEMENT));
        tmp = Dequeue(*danhsach);
        if(tmp == NULL)
        {
            printf("Het khach hang.\n");
            return;
        }
        printf("Khach hang : %s \nSDT : %s \n",tmp->name,tmp->phone);
        printf("Loai A mua : ");
        __fpurge(stdin);
        scanf("%d",&a);
        while(a < 0)
        {
            printf("Khong hop le nhap lai : ");
            __fpurge(stdin);
            scanf("%d",&a);
        }
        printf("Loai B mua : ");
        __fpurge(stdin);
        scanf("%d",&b);
        while(b < 0)
        {
            printf("Khong hop le nhap lai : ");
            __fpurge(stdin);
            scanf("%d",&b);
        }
        printf("Loai C mua : ");
        __fpurge(stdin);
        scanf("%d",&c);
        while(c < 0)
        {
            printf("Khong hop le nhap lai : ");
            __fpurge(stdin);
            scanf("%d",&c);
        }
        fprintf(f,"%d %d %d\n",a,b,c);
        fclose(f);
    }
}*/
/*void ghiFile(QUEUE* danhsach,int argc,char** argv)
{
    if(argc < 3)
	{
		printf("Khong du tham so.\n");
	}
	else
	{
		char* desfile = argv[1];
		FILE* f = fopen(desfile,"wt");
		if(f == NULL)
		{
			printf("Khong mo duoc file.\n");
		}
		else
        {
            QUEUE_ELEMENT* tmp = (PQUEUE_ELEMENT)calloc(1,sizeof(QUEUE_ELEMENT));
            tmp = danhsach->Front;
            while(tmp != NULL)
            {
                fprintf(f,"%s %s\n",tmp->name,tmp->phone);
                tmp = tmp->link;
            }
        }
        fclose(f);
        char* file2 = argv[2];
        FILE* f2 = fopen(file2,"at");
        if(f2 == NULL)
		{
			printf("Khong mo duoc file.\n");
		}
		else
        {
            fprintf(f2,"%d\n",-1);
        }
        fclose(f2);
    }
}
*/
/*void Delete(QUEUE** danhsach,char* id,char* ram)
{
    QUEUE_ELEMENT* tmp = (QUEUE_ELEMENT*)calloc(1,sizeof(QUEUE_ELEMENT));
    QUEUE_ELEMENT* prev = (QUEUE_ELEMENT*)calloc(1,sizeof(QUEUE_ELEMENT));
    tmp = (*danhsach)->Front;
    prev = NULL;
    while (tmp != NULL)
    {
        if(strcmp(tmp->id,name) == 0 && strcmp(tmp->phone,phone) == 0)
        {
            if(prev == NULL)
            {
                (*danhsach)->Front = tmp->link;
            }else
            {
                prev->link = tmp->link;
            }
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = tmp->link;   
    }
}*/
/*void Khachangdacbiet(QUEUE** danhsach)
{
*char* name = (char*)calloc(1024,sizeof(char));
    char* phone = (char*)calloc(1024,sizeof(char));
    printf("Nhap ten nguoi uu tien : ");
    __fpurge(stdin);
    fgets(name,1024,stdin);
    name[strlen(name) - 1] = '\0';
    printf("Nhap so dien thoai nguoi uu tien : ");
    __fpurge(stdin);
    fgets(phone,1024,stdin);
    phone[strlen(phone) - 1] = '\0';
    Delete(danhsach,name,phone);
    Pushqueue(*danhsach, name, phone);   
}
*/
void Tongket(int argc,char** argv)
{
	if(argc < 3)
	{
		printf("Khong du tham so.\n");
	}
	else
	{
		char* desfile = argv[2];
		FILE* f = fopen(desfile,"rt");
		if(f == NULL)
		{
			printf("Khong mo duoc file.\n");
		}
		else
		{
            int a,b,c;
            int spA = 0,spB = 0,spC = 0;
            int sum = 0;
            int ngay = 1;
            char* A = (char*)calloc(1024,sizeof(char));   
 			char* B = (char*)calloc(1024,sizeof(char));
			char* C = (char*)calloc(1024,sizeof(char));
			while(!feof(f))
			{
				memset(A,0,1024);
				memset(B,0,1024);
                memset(C,0,1024);
                __fpurge(stdin);
                fscanf(f,"%s", A);
                if(strlen(A) == 0)
				{
					break;
				}
                else{
                    a = atoi(A);
                    if(a == -1)
                    {
                        printf("Tong san pham cac loai ngay %d\n",ngay);
                        ngay++;
                        printf("%-5d%-5d%-5d \n",spA,spB,spC);
                        sum = 10*spA + 50*spB + 80*spC;
                        printf("Tong so tien ban duoc : %d \n",sum);
                        spC = 0;
                        spA = 0;
                        spB = 0;
                        continue;
                    }
                    __fpurge(stdin);
                    fscanf(f,"%s", B);
                    b = atoi(B);
                    __fpurge(stdin);
                    fscanf(f,"%s", C);
                    c = atoi(C);
                    printf("%-5d%-5d%-5d \n",a,b,c);
                    spA += a;
                    spB += b;
                    spC += c; 
                }
			}
			free(A);
			free(B);
            free(C);
		}
		fclose(f);
	}
} 

void Ucpu(QUEUE** danhsach)
{
    QUEUE_ELEMENT* tmp = (*danhsach)->Front;
    char* ram = (char*)calloc(1024,sizeof(char));
    int stt;
    printf("Nhap ID muon den :");
    __fpurge(stdin);
    scanf("%d",&stt);
    while (stt < 1 || stt > (*danhsach)->size)
    {
        printf("Nhap sai ID nhap lai :");
        __fpurge(stdin);
        scanf("%d",&stt);
    }
    for(int i = 1;i < stt; i++)
    {
        tmp = tmp->link;
    }
    do
    {
        printf("Nhap CPU may %d: ",stt);
        __fpurge(stdin);
		fgets(ram,1024,stdin);
        ram[strlen(ram) - 1] = '\0';
        /*Chuyeni(ram);
        while (ram[0] != 'i' && ram[0] != 'I')
        {
            printf("Gia tri tim khong hop le nhap lai.\n");
            __fpurge(stdin);
		    fgets(ram,1024,stdin);
            ram[strlen(ram) - 1] = '\0';
        }*/
        if(strcmp(ram,"STOP") == 0)
        {
            break ;
        }
        Chuyeni(ram);
        stt++;
        strcpy(tmp->id,ram);
        tmp = tmp->link;
    }while(tmp != NULL);
    printqueue(*danhsach);
}

void Uram(QUEUE** danhsach)
{
    QUEUE_ELEMENT* tmp = (*danhsach)->Front;
    char* ram = (char*)calloc(1024,sizeof(char));
    int stt;
    printf("Nhap ID muon den :");
    __fpurge(stdin);
    scanf("%d",&stt);
    while (stt < 1 || stt > (*danhsach)->size)
    {
        printf("Nhap sai ID nhap lai :");
        __fpurge(stdin);
        scanf("%d",&stt);
    }
    for(int i = 1;i < stt; i++)
    {
        tmp = tmp->link;
    }
    do
    {
        printf("Nhap Ram may %d: ",stt);
        __fpurge(stdin);
		fgets(ram,1024,stdin);
        ram[strlen(ram) - 1] = '\0';
        if(strcmp(ram,"STOP") == 0)
        {
            break ;
        }
        while (strcmp(ram,"1") != 0 && strcmp(ram,"2") != 0  &&strcmp(ram,"4") != 0  && strcmp(ram,"8") != 0  &&strcmp(ram,"16") != 0  &&strcmp(ram,"32") != 0  )
        {   
            printf("Ram khong ton tai nhap lai :");
            __fpurge(stdin);
            fgets(ram,1024,stdin);
            ram[strlen(ram) - 1] = '\0';
        }
        strcpy(tmp->ram,ram);
        tmp = tmp->link;
        stt++;
    }while(tmp != NULL);
    printqueue(*danhsach);
}

void SearchCPU(QUEUE** danhsach)
{
    int sl = 0;
    char* cpu = (char*)calloc(1024,sizeof(char));
    printf("Nhap cpu :");
    __fpurge(stdin);
    fgets(cpu,1024,stdin);
    cpu[strlen(cpu) - 1] = '\0';
    Chuyeni(cpu);
    if(cpu[0] != 'i' && cpu[0] != 'I')
    {
        printf("Gia tri tim khong hop le.\n");
        return ;
    }
    QUEUE_ELEMENT* tmp = (*danhsach)->Front;
    while(tmp != NULL)
    {
        if(strcmp(tmp->id,cpu) == 0)
        {
            printf("%-5s%-5s\n",tmp->id,tmp->ram);
            sl++;
        }
        tmp = tmp->link;
    }
    if(sl == 0)
    {
        printf("<Khong tim thay>");
    }
}

void SearchRam(QUEUE** danhsach)
{
    int sl = 0;
    char* ram = (char*)calloc(1024,sizeof(char));
    printf("Nhap Ram :");
    __fpurge(stdin);
    fgets(ram,1024,stdin);
    ram[strlen(ram) - 1] = '\0';
    if(strcmp(ram,"1") != 0 && strcmp(ram,"2") != 0  &&strcmp(ram,"4") != 0  && strcmp(ram,"8") != 0  &&strcmp(ram,"16") != 0  &&strcmp(ram,"32") != 0  )
    {   
        printf("Gia tri tim khong hop le.\n");
        return ;
    }
    QUEUE_ELEMENT* tmp = (*danhsach)->Front;
    while(tmp != NULL)
    {
        if(strcmp(tmp->ram,ram) == 0)
        {
            printf("%-5s%-5s\n",tmp->id,tmp->ram);
            sl++;
        }
        tmp = tmp->link;
    }
    if(sl == 0)
    {
        printf("<Khong tim thay>");
    }
}

void Timkiem(QUEUE** danhsach)
{
    printf("Tim kiem theo ram nhap 0 - theo CPU nhap 1 \n");
    int chuc_nang;
     __fpurge(stdin);
    scanf("%d",&chuc_nang);
    if(chuc_nang == 0)
    {
        SearchRam(danhsach);
    }else
    {
        SearchCPU(danhsach);
    }
    
}

void menu(QUEUE** danhsach)
{
    char yn;
    int chuc_nang;
    printf("Cac chuc nang sinh vien: \n");
    printf("1 : Load. \n");
    printf("2 : Update CPU. \n");
    printf("3 : Update RAM. \n");
    printf("4 : Search. \n");
    printf("5 : Quit. \n");
    do
    {
        printf("Chon chuc muon chon chuc nang nao : ");
        __fpurge(stdin);
        scanf("%d",&chuc_nang);
		printf("\n");
        switch (chuc_nang)
        {
		case 1 :
			DocFile(*danhsach);
            printf("\n");
			break;
        case 2 : 
            Ucpu(danhsach);
            printf("\n");
            break;
        case 3 :
            Uram(danhsach);
            printf("\n");
            break;
        case 4 :
			Timkiem(danhsach);
			break;
        case 5 :
			exit(0);
			break;
        default : 
            printf("Khong co thao tac nay.\n"); 
            break;
        }
        printf("Ban muon chon chuc nang nao khac khong[y/n] : ");
		__fpurge(stdin);
        scanf("%c", &yn);
        printf("\n");
        if(yn == 'n')
        {
            break;
        }
    }while( 0 == 0);     
}

void main()
{
    QUEUE* danhsach = (PQUEUE)calloc(1,sizeof(QUEUE));
    menu(&danhsach);
}