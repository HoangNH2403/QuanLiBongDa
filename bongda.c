#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct Team
{
    int id;
    char ten[31];
    int diem;
    int bthang;
    int bthua;
    struct Team *next;
} Team;

int n;
Team *first, *last;

char vong[MAX][8];
int sovong[MAX];
int a[MAX][MAX];

// Tao ra 1 profile moi
Team *makenode(int id, char *ten, int diem, int bthang, int bthua)
{
    Team *node = (Team *)malloc(sizeof(Team));
    node->id = id;
    strcpy(node->ten, ten);
    node->diem = diem;
    node->bthang = bthang;
    node->bthua = bthua;
    node->next = NULL;
    return node;
}

// Khoi tao
void initList()
{
    first = NULL;
    last = NULL;
}

// Kiem tra xem danh sach co rong khong?
int listEmpty()
{
    return (first == NULL && last == NULL);
}

// Chen them 1 profile vao cuoi danh sach
void insertToLast(int id, char *ten, int diem, int bthang, int bthua)
{
    Team *profile = makenode(id, ten, diem, bthang, bthua);
    if (listEmpty())
    {
        first = profile;
        last = profile;
    }
    else
    {
        // profile->next = first;
        // first = profile;
        last->next = profile;
        last = profile;
    }
}

// In thong tin cac doi
void printList()
{
    printf("%-8s%-25s%-10s%-16s%-16s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    for (Team *p = first; p != NULL; p = p->next)
    {
        printf("%-8d%-25s%-10d%-16d%-16d\n", p->id, p->ten, p->diem, p->bthang, p->bthua);
    }
}

// Doc du lieu tu file roi ghi vao danh sach
void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found!\n");
    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        int ID;
        char name[31];
        fscanf(f, "%d\t", &ID);
        fgets(name, 31, f);
        name[strlen(name) - 1] = '\0';
        insertToLast(ID, name, 0, 0, 0);
    }

    for (int i = 0; i < n - 1; i++)
    {
        fscanf(f, "%s", &vong[i]);
        fscanf(f, "%d", &sovong[i]);
        for (int j = 0; j < n; j++)
        {
            fscanf(f, "%d", &a[i][j]);
        }
    }

    fclose(f);
}

// Chuc nang 2 in lich thi dau
void lich()
{
    printf("\n**Lich thi dau:\n");
    for (int i = 0; i < n - 1; i++)
    {
        printf("%s %d\n", vong[i], sovong[i]);
        for (int j = 0; j < n; j++)
        {
            for (Team *p = first; p != NULL; p = p->next)
            {
                if (p->id == a[i][j])
                {
                    if (j % 2 == 0)
                        printf("%s - ", p->ten);
                    else
                        printf("%s\n", p->ten);
                }
            }
        }
        // printf("\n");
    }
}

// Ham thay doi 1 node
void thaydoi(int a, int b, int c)
{
    for (Team *p = first; p != NULL; p = p->next)
    {
        if (p->id == a)
        {
            p->bthang += b;
            p->bthua += c;
            if (b > c)
                p->diem += 3;
            if (b < c)
                p->diem += 0;
            if (b == c)
                p->diem += 1;
        }
    }
}

// Chuc nang 3 cap nhat ket qua
void capnhat()
{
    int x;
    printf("\n**Lich thi dau:\n");
    for (int i = 0; i < n - 1; i++)
    {
        printf("%s %d\n", vong[i], sovong[i]);
        for (int j = 0; j < n; j++)
        {
            for (Team *p = first; p != NULL; p = p->next)
            {
                if (p->id == a[i][j])
                {
                    if (j % 2 == 0)
                    {
                        printf("%s - ", p->ten);
                        x = a[i][j];
                    }
                    else
                    {
                        printf("%s: ", p->ten);
                        int u, v;
                        scanf("%d - %d", &u, &v);
                        thaydoi(x, u, v);
                        thaydoi(a[i][j], v, u);
                    }
                }
            }
        }
        // printf("\n");
    }
}

// Ham xoa di 1 doi
Team *removeTeam(Team *f, int diem)
{
    if (listEmpty())
        return NULL;

    if (f->diem == diem)
    {
        Team *tmp = f->next;
        free(f);
        if (tmp == NULL)
            last = NULL;
        return tmp;
    }
    else
    {
        f->next = removeTeam(f->next, diem);
        return f;
    }
}

// Chuc nang 4 thong ke nhung doi diem thap nhat roi xoa di va con lai
void thongke()
{
    int min = first->diem;
    for (Team *p = first; p != NULL; p = p->next)
    {
        if (p->diem < min)
            min = p->diem;
    }
    printf("**Danh sach nhung doi diem thap nhat:\n");
    printf("%-8s%-25s%-10s%-16s%-16s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    for (Team *p = first; p != NULL; p = p->next)
    {
        if (p->diem == min)
        {
            printf("%-8d%-25s%-10d%-16d%-16d\n", p->id, p->ten, p->diem, p->bthang, p->bthua);

            // Xoa di cac doi diem thap nhat
            first = removeTeam(first, min);
        }
    }
    // Xoa di cac doi diem thap nhat
    // first = removeTeam(first, min);

    printf("\n**Cac doi con lai la:\n");
    printf("%-8s%-25s%-10s%-16s%-16s\n", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    for (Team *p = first; p != NULL; p = p->next)
    {
        if (p->diem != min)
            printf("%-8d%-25s%-10d%-16d%-16d\n", p->id, p->ten, p->diem, p->bthang, p->bthua);
    }
}

int main()
{
    initList();
    load("bongda.txt");
    int m;

    while (1)
    {

        printf("       *** MENU ***         ");
        printf("\n   -------------------------------");
        printf("\n   1.Thong tin cac doi bong          ");
        printf("\n   2.Lich thi dau                    ");
        printf("\n   3.Cap nhat ket qua                ");
        printf("\n   4.Thong ke                        ");
        printf("\n   5.Thoat                           ");
        printf("\n\nBan muon chon so: ");
        scanf("%d", &m);
        getchar();
        if (m == 5)
        {
            printf("Chuong trinh ket thuc!");
            printf("\n");
            break;
        }
        else if (m == 1)
        {
            printList();
            printf("\n");
        }
        else if (m == 2)
        {
            lich();
            printf("\n");
        }
        else if (m == 3)
        {
            capnhat();
            printList();
            printf("\n");
        }
        else if (m == 4)
        {
            thongke();
            printf("\n");
        }
        else
        {
            printf("\nBan chon sai so.");
        }
    }
}