#include <stdio.h>
#include <stdlib.h>
#define M 100
struct node {
    struct node* lchild;
    int ltag;
    char data;
    struct node* rchild;
    int rtag;
};
typedef struct node tree;
typedef struct node * BTREE;//定义节点

struct STACK{
    BTREE pot;
    struct STACK * next;
};
typedef struct STACK ST;
typedef struct STACK * pointS;//定义栈
void Push(BTREE T, pointS S);
BTREE Top(pointS S);
void Pop(pointS S);
int isEmpty(pointS S);//栈操作

struct STACK1{
    BTREE pot;
    int flag;
    struct STACK1 * next;
};
typedef struct STACK1 ST1;
typedef struct STACK1 * pointS1;//定义栈
void Push1(BTREE T, pointS1 S);
BTREE Top1(pointS1 S);
void Pop1(pointS1 S);
int isEmpty1(pointS1 S);//栈操作

struct celltype{
    BTREE element;
    struct celltype * next;
};
typedef struct celltype celltype;
typedef struct celltype *pcell;

struct QUEUE {
    pcell pfront;
    pcell prear;//队尾
};
typedef struct QUEUE DL;
typedef struct QUEUE *dui;//定义队列；
void MakeNull(dui Q);
int Empty(dui Q);
void EnQueue( BTREE p, dui Q);
void DeQueue(  dui Q);
BTREE outQueue( dui Q);


void CreatBT1( BTREE *T, FILE * fp );
BTREE CreatBT2( );//创建二叉链表
void PreOrderd(BTREE T);//先序遍历递归
void PreOrderfd(BTREE T);//先序遍历非递归；
void InOrderd( BTREE T);//中序遍历递归；
void InOrderfd( BTREE T);//中序遍历非递归；
void PostOrderd( BTREE T);//后序遍历递归；
void PostOrderfd( BTREE); //后序遍历非递归
void LeverOrder(BTREE T);//层序遍历二叉树
void in_Threading( BTREE p );//以P为根节点进行中序线索化
BTREE inorder_Threading( BTREE T);//带头结点的中序线索化，返回线索化后的头结点指针；

BTREE PreNext( BTREE p);//求p的中序线索的先序遍历的后继结点
BTREE InNext(BTREE p);//求p得中序后继结点
BTREE PostNext(BTREE p);//求p的中序线索的后序遍历的后继结点
void inOrderth_Traverse( BTREE T);//中序遍历中序线索化树
void inOrderTh_Traverse( BTREE T);//中序遍历中序线索化树
void preOrderTh_Traverse( BTREE T);//先序遍历中序线索化树
void postOrderTh_Traverse( BTREE T);//后序遍历中序线索化树
BTREE Creatnode( char ch, BTREE l, BTREE r);
BTREE changeto();

void pisNULL( BTREE p);


BTREE pre;//全局变量指向前驱；
//FILE * fp ;

int main()
{
    BTREE T1, T2, T3;
    FILE *fp = fopen("D:\\in1.txt","r");
    //CreatBT1(&T2, fp);//第一种方法

    T2 = CreatBT2();//第二种方法
    printf("建立的树为（显示为满二叉树 #表示空节点）：  ");
    T3 = changeto();
    LeverOrder(T3);

    printf("\n\n\n");

    printf("先序遍历递归：");
    PreOrderd(T2);
    printf("\n");
    printf("中序遍历递归：");
    InOrderd(T2);
    printf("\n");
    printf("后序遍历递归：");
    PostOrderd(T2);
    printf("\n");
    printf("层序遍历：");
    LeverOrder(T2);
    printf("\n\n\n");

    printf("先序遍历非递归：");
    PreOrderfd(T2);
    printf("\n");
    printf("中序遍历非递归：");
    InOrderfd(T2);
    printf("\n");
    printf("后序遍历非递归：");
    PostOrderfd(T2);
    printf("\n\n\n");

    T1 = inorder_Threading(T2);//中序线索化


    printf("线索化先序遍历：");
    preOrderTh_Traverse(T1);
    printf("\n");
    printf("线索化中序遍历：");

    inOrderTh_Traverse(T1);
    printf("\n");
    printf("线索化后序遍历：");
    postOrderTh_Traverse(T1);
    printf("\n");

    return 0;
}

BTREE Creatnode(char ch, BTREE l, BTREE r){//建立节点存放数据ch,
    BTREE p = (BTREE) malloc(sizeof(tree));
    p ->data = ch;
    p ->lchild = l;
    p ->rchild = r;
    return p;
}

void pisNULL(BTREE p){//判断指针是否为空
    if( p == NULL){
        printf("point is NULL");
        exit(0);
    }
}

void CreatBT1( BTREE *T, FILE *fp){//第一种建树
    char ch;
    fscanf(fp, "%c", &ch);
    if( ch == '#' ){//如果读入数据为#，则代表该指针指向为空
        (*T) = NULL;
    }
    else{//否则指向存有ch的节点
        (*T) = (BTREE) malloc(sizeof(tree));//创建存放ch的节点
        (*T) ->data = ch;
        CreatBT1(&((*T) ->lchild), fp);//递归建立左子树
        CreatBT1(&((*T) ->rchild), fp);//递归建立右子树
    }
}

BTREE CreatBT2(){//第二种建树
    int i=1, j=0;
    char ch;
    BTREE bt, p, s[M];//bt为根，p用于建立节点
    FILE *fp = fopen("D:\\in.txt", "r");
    while(fscanf(fp, "%c", &ch) != EOF && i != 0){
        p = Creatnode(ch, NULL, NULL);
        s[i] = p;
        if( i == 1){
            bt = p;//为根节点；
        }
        else{
            if(p ->data == '#'){//如果传入为#，则代表相应节点的指针域为空
                j = i/2;

                if(i%2 == 0 )
                    s[j] ->lchild = NULL;
                else
                    s[j] ->rchild = NULL;
            }else{

                j = i/2;//父节点的编号

                if(i%2 == 0 )
                    s[j] ->lchild = p;//i是j的左儿子
                else
                    s[j] ->rchild = p;//i是j的右儿子
            }
        }
        i++;
    }
    return bt;
}

BTREE changeto(){//第二种建树
    int i=1, j=0;
    char ch;
    BTREE bt, p, s[M];//bt为根，p用于建立节点
    FILE *fp = fopen("D:\\in.txt", "r");
    while(fscanf(fp, "%c", &ch) != EOF && i != 0){
        p = Creatnode(ch, NULL, NULL);
        s[i] = p;
        if( i == 1){
            bt = p;//为根节点；
        }
        else{
            if(p ->data == '#'){//如果传入为#，则代表相应节点的指针域为空
                j = i/2;

                if(i%2 == 0 )
                    s[j] ->lchild = p;
                else
                    s[j] ->rchild = p;
            }else{

                j = i/2;//父节点的编号

                if(i%2 == 0 )
                    s[j] ->lchild = p;//i是j的左儿子
                else
                    s[j] ->rchild = p;//i是j的右儿子
            }
        }
        i++;
    }
    return bt;
}

void PreOrderd(BTREE T){//先序递归遍历
    if(T != NULL)
    {
        printf("%c", T -> data);//先访问当前节点数据，对应先序遍历
        PreOrderd(T -> lchild);//递归访问左子树
        PreOrderd(T -> rchild);//递归访问右子树
    }
}

void PreOrderfd(BTREE T){//先序非递归遍历
    pointS st1 = (pointS)malloc(sizeof(ST));
    st1 -> next = NULL;
    int u = 0;
    while( T != NULL || !isEmpty(st1))//循环直到指针为空切栈为空
    {
        while( T != NULL )//当指针不为空是循环
        {
            printf("%c", T ->data);//打印数据域
            u++;
            Push( T, st1);//将指针值保存入栈中
            T = T ->lchild;//继续遍历左儿子
        }
        if( st1 -> next != NULL){//当栈非空
            T = Top(st1);//取出栈顶元素给T
            Pop(st1);//删除栈顶元素
            u++;//统计栈操作
            T = T ->rchild;//继续遍历右儿子
        }
    }
    printf("    steps:%d", u);
}

void InOrderd(BTREE T){//中序递归遍历
    if(T != NULL)
    {
        InOrderd( T ->lchild);//递归访问当前节点左子树
        printf("%c", T ->data);//访问完左子树后访问当前节点数据，对应中序遍历
        InOrderd( T ->rchild);//递归访问当前节点右子树
    }
}

void InOrderfd(BTREE T){
    pointS st1 = (pointS) malloc(sizeof(ST));
    st1 ->next = NULL;
    int u = 0;
    while( T != NULL || !isEmpty(st1)){//循环直到指针为空切栈为空
        u++;
        while( T != NULL){//当指针不为空是循环
            Push( T, st1);//将指针值保存入栈中
            T = T ->lchild;//继续遍历左儿子
            u++;
        }
        if(!isEmpty(st1)){//当栈非空
            T = Top(st1);//取出栈顶元素给T
            Pop(st1);//删除栈顶元素
            printf("%c", T ->data);//打印数据域
            T = T ->rchild;//继续遍历右儿子
        }
    }
    printf("    steps:%d", u);
}

void PostOrderd(BTREE T){//后序递归遍历
    if( T != NULL){
        PostOrderd(T ->lchild);
        PostOrderd(T ->rchild);
        printf("%c", T ->data);//访问完左右子树后访问当前节点数据，对应后序遍历
    }
}

void PostOrderfd(BTREE T){
    pointS1 st2 = (pointS1)malloc(sizeof(ST1));
    st2 ->next = NULL;
    BTREE T1 = T;
    int u = 0;
    while( T != NULL || !isEmpty1(st2)){//循环直到指针为空且栈为空
        u++;
        while( T != NULL){//当指针非空时循环
            Push1( T , st2);//将当前节点指针入栈
            st2 ->next ->flag = 1;//将栈顶元素标志位改为1
            T = T ->lchild;//继续遍历当前节点左子树
            u++;
        }
        while( !isEmpty1(st2) && st2 ->next ->flag == 2){//当栈非空且栈顶元素标志位为2时，出栈并输出栈顶节点数据
            T = Top1(st2);
            if(T == T1){//如果栈顶节点时根节点，代表遍历结束
                printf("%c", T ->data);
                printf("    steps:%d", u);
                return;
            }
            Pop1(st2);
            u++;
            printf("%c", T ->data);
        }
        if(!isEmpty1(st2)){//若栈非空，将栈顶元素标志改为2，遍历栈顶节点的右子树
            st2 ->next ->flag = 2;
            T = Top1(st2) ->rchild;
        }
    }

}

void LeverOrder(BTREE T){//层序遍历
    dui Q = (dui)malloc(sizeof(DL));
    Q->pfront = (pcell)malloc(sizeof(celltype));
    Q->pfront ->next = NULL;
    Q->prear = Q->pfront;
    BTREE q;

    if(T == NULL)//如果二叉树非空，将跟指针入队
        return;
    EnQueue( T, Q );
    while(!Empty(Q))//循环直到队列为空
    {
        q = outQueue(Q);//队首元素出队
        DeQueue(Q);//删除队首元素
        printf("%c", q ->data);//访问节点数据域
        if(q ->lchild != NULL)//若节点有左儿子，则左儿子入队
        {
            EnQueue(q ->lchild, Q);
        }
        if(q ->rchild != NULL)//若节点有右儿子，则右儿子入队
        {
            EnQueue(q ->rchild, Q);
        }

    }


}


BTREE inorder_Threading(BTREE T){//对树进行中序线索化
    BTREE head, p;
    head = (BTREE) malloc(sizeof(tree));//建立头结点
    head ->ltag = 1;
    head ->rtag = 1;
    head ->rchild = head;//对头结点进行初始化
    if( T == NULL)
    {
        head ->lchild = head;//根结点空，则头结点左指针指向自身
    }
    else
    {
        head ->lchild = T;//根结点非空，则头结点左指针指向根节点
        pre = head;//初始化前驱节点为头指针
        in_Threading(T);//调用中序线索化函数对根节点线索化
        head ->rchild = pre;
        pre ->rtag = 0;
        pre ->rchild = head;
    }
    head ->ltag = 1;
    head ->rtag = 1;
    head ->rchild = head;
    return head;
}

void in_Threading( BTREE p ){
    if(p)
    {
        in_Threading(p ->lchild);//递归对左子树线索化
        if(!p ->lchild)//如果没有左儿子，则左标志位为0，指向前驱
        {
            p ->ltag = 0;
            p ->lchild = pre;
        }
        else//否则左标志位为1
        {
            p ->ltag = 1;
        }
        if(!pre ->rchild)//如果前驱没有右儿子，则前驱右标志位为0，指向当前节点
        {
            pre ->rtag = 0;
            pre ->rchild = p;
        }
        else//否则前驱右标志位为1
        {
            pre ->rtag = 1;
        }
        pre = p;//更新前驱
        in_Threading(p ->rchild);//递归对右子树线索化
    }
}

/*void inOrderth_Traverse( BTREE T){//
    BTREE p;
    p = T ->lchild;
    while( p!= T)
    {
        while( p ->ltag == 1)
        {
            p = p ->lchild;
        }
        printf("%c", p ->data);
        while( p ->rtag == 0 &&  p ->rchild != T)
        {
            p = p ->rchild;
            printf("%c", p ->data);
        }
        p = p ->rchild;
    }
    printf("\n");
}*/

BTREE InNext(BTREE p){//中序线索化树的中序遍历的后继节点
    BTREE q;
    q = p ->rchild;
    if( p ->rtag == 1)//当无右儿子，右线索节点即为所求
    {
        while(q ->ltag == 1)//所求节点时右子树的最左节点
        {
            q = q ->lchild;
        }
    }
    return q;
}

BTREE PreNext(BTREE p){//中序线索化树的先序遍历的后继节点
    BTREE q;
    q = p;
    if( p  ->ltag != 0)//有左儿子，左儿子即为所求
    {
        return p ->lchild;
    }else
    {
        while(q ->rtag == 0)//有右儿子，右儿子即为所求，否则就是第一个具有右儿子线索节点的右儿子
            q = q ->rchild;
        return q ->rchild;
    }
}

BTREE PostNext(BTREE p){//中序线索化树的后序遍历的后继节点
    BTREE q = p, t, r, r1, s;
    while( q ->rtag == 1)//先循环找到当前节点右子树的最右节点
    {
        q = q ->rchild;
    }
    t = q ->rchild;//为最右节点的线索节点
    r = t ->lchild;//为线索节点的左儿子
    if( r != p)//如果线索节点的左儿子不等于p
    {
        while(r != p)
        {
            r1 = r;//所求节点就是p的父节点
            r = r ->rchild;
        }
        return r1;
    }
    else
    {
        if( t ->rtag == 0)//如果线索节点没有右儿子
            return t;//那么线索节点就是所求
        else
        {
            s = t ->rchild;//s是线索节点右儿子
            while( s ->ltag == 1 || s ->rtag == 1){//循环直到线索节点左右儿子均为空
                if(s ->ltag == 1){//当左儿子不为空，就向左深入
                    s = s ->lchild;
                }
                else if(s ->rtag == 1){//若没有左儿子，有右儿子，就向右深入
                    s = s ->rchild;
                }
            }

            return s;
        }
    }
}

void inOrderTh_Traverse(BTREE T){//利用后继节点的中序遍历
    BTREE p;
    p = T;
    int u = 0;
    do{
        p = InNext(p);//获取后继节点
        u++;
        if( p != T )//
            printf("%c", p ->data);//访问节点数据域
    }while( p != T);//循环直到回到根节点
    printf("    steps:%d", u);
}

void preOrderTh_Traverse(BTREE T){//利用后继节点的先序遍历
    BTREE p;
    //BTREE p;
    p = T;
    int o1 = 0;
    do{
        p = PreNext(p);//获取后继节点
        if( p != T )
            printf("%c", p ->data);//访问节点数据域
        o1++;//统计循环次数
    }while( p != T);//循环直到回到根节点
    printf("    steps:%d", o1);
}

void postOrderTh_Traverse( BTREE T){//利用后继节点的后序遍历
    BTREE p;
    int u = 0;
    p = T ->lchild;
    do{
        p = PostNext(p);//获取后继节点
        u++;
        if( p != T )
            printf("%c", p ->data);//访问节点数据域
    }while( p != T ->lchild);//循环直到回到根节点
        printf("    steps:%d", u);
}

/*void printTree( BTREE T, int nLayer){
    int i =0;
    if( T == NULL){
        return;
    }else
    {
        printTree(T ->rchild, nLayer + 1);
        for(i = 0; i<nLayer; i++ ){
            printf("  a ");
        }
        printf("%c\n",T ->data);
        printTree(T->lchild, nLayer + 1);
    }

}*/

int isEmpty(pointS S){
    if(S ->next == NULL)
    {
        return 1;
    }else
    {
        return 0;
    }
}

int isEmpty1(pointS1 S){
    if(S ->next == NULL)
    {
        return 1;
    }else
    {
        return 0;
    }
}

void Push(BTREE ch, pointS S){
    pisNULL(S);
    pointS p = (pointS) malloc(sizeof(ST));
    p ->pot = ch;
    p ->next = S ->next;
    S ->next = p;
}

void Push1(BTREE ch, pointS1 S){
    pisNULL(S);
    pointS1 p = (pointS1) malloc(sizeof(ST1));
    p ->pot = ch;
    p ->next = S ->next;
    S ->next = p;
}



BTREE Top(pointS S){
    if( isEmpty(S)){
        printf("the stack is empty");
    }else
    {
        return S ->next ->pot;
    }
}

BTREE Top1(pointS1 S){
    if( isEmpty1(S)){
        printf("the stack is empty");
    }else
    {
        return S ->next ->pot;
    }
}

void Pop(pointS S){
    pointS temp;
    if(isEmpty(S)){
        printf("the stack is empty");
    }else
    {
        temp = S ->next;
        S ->next = S ->next ->next;
        free(temp);
    }
}

void Pop1(pointS1 S){
    pointS1 temp;
    if(isEmpty1(S)){
        printf("the stack is empty");
    }else
    {
        temp = S ->next;
        S ->next = S ->next ->next;
        free(temp);
    }
}




int Empty(dui Q){
    if(Q->pfront == Q->prear)
        return 1;
    else
        return 0;
}

BTREE outQueue(dui Q){
    if(Empty(Q))
        printf("Queue is empty");
    else
    {
        return Q -> pfront ->next ->element;
    }
}

void EnQueue(BTREE p, dui Q){
    pcell a = (pcell)malloc(sizeof(celltype));
    a ->element = p;
    a ->next = NULL;
    Q->prear->next = a;
    Q->prear = Q->prear->next;
}

void DeQueue(dui Q){
    pcell temp;
    if(Empty(Q))
    {
        printf("dui is empty");
        exit(0);
    }else
    {
        temp = Q->pfront ->next;
        Q->pfront ->next = temp ->next;
        free(temp);
        if(Q->pfront ->next == NULL)
        {
            Q->prear = Q->pfront;
        }
    }
}


