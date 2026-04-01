#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NotFound NULL
typedef struct {
    int Coef; // 系数
    int Exp;  // 指数
} ElementType;



// 通过链式存储方式实现线性表，带头结点
typedef struct LNode{
   ElementType Data; 
   struct LNode* next;
} *List, *Position;



 
// 初始化线性表， 返回头结点
List MakeEmpty(){
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->next = NULL;
    return L;
}

// 尾插，在p后插入X
bool Insert(ElementType* X, Position p){
    if(!p){
        printf("位置不合法");
        return false;
    }
    Position newNode = (Position)malloc(sizeof(struct LNode));
    newNode->Data = *X;
    newNode->next = p->next;
    p->next = newNode;
    return true;
}



// 读入线性表
List Read(){
    List L = MakeEmpty();
    Position tail = L;
    int n = 0;
    scanf("%d", &n); // 非零项的个数
    for(int i = 0; i < n; i++){
        ElementType elem;
        scanf("%d %d", &elem.Coef, &elem.Exp);
        Insert(&elem, tail);
        tail = tail->next;
    }
    return L;
}

// 输出线性表
void Print(List L){
    Position p = L->next;
    if(!p){ // 如果空多项式，输出0 0
        printf("0 0\n");
        return;
    }
    while(p -> next){
        if(p->Data.Coef != 0) // 如果系数为0，则不输出
            printf("%d %d ", p->Data.Coef, p->Data.Exp);
        p = p->next;
    }
    printf("%d %d\n", p->Data.Coef, p->Data.Exp);
}

// 多项式相加
List Add(List L1, List L2){
    List sum = MakeEmpty();
    Position tail = sum;
    Position p1 = L1->next, p2 = L2->next;
    while(p1 && p2){
        if(p1->Data.Exp == p2->Data.Exp){ // 如果指数相同，系数相加
            if(p1->Data.Coef + p2->Data.Coef != 0){ // 如果系数不为0（同类项相消）
                ElementType elem = {p1->Data.Coef + p2->Data.Coef, p1->Data.Exp};
                Insert(&elem, tail);
                tail = tail->next;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->Data.Exp > p2->Data.Exp){ // 如果p1的指数较大，插入p1的项
            Insert(&p1->Data, tail);
            tail = tail->next;
            p1 = p1->next;
        }
        else{ // 如果p2的指数较大，插入p2的项
            Insert(&p2->Data, tail);
            tail = tail->next;
            p2 = p2->next;
        }
    }
    while(p1){ // 如果p1还有剩余项
        Insert(&p1->Data, tail);
        tail = tail->next;
        p1 = p1->next;
    }
    while(p2){ // 如果p2还有剩余项
        Insert(&p2->Data, tail);
        tail = tail->next;
        p2 = p2->next;
    }
    return sum;
}

// 多项式相乘
List Multiply(List L1, List L2){
    List product = MakeEmpty();
    for(Position p1 = L1->next; p1; p1 = p1->next){
        List temp = MakeEmpty();
        Position tail = temp;
        for(Position p2 = L2->next; p2; p2 = p2->next){
            ElementType elem = {p1->Data.Coef * p2->Data.Coef, p1->Data.Exp + p2->Data.Exp};
            Insert(&elem, tail);
            tail = tail->next;
        }
        List newProduct = Add(product, temp);
        free(product);
        free(temp);
        product = newProduct;
    }
    return product;

}

int main(){
    List L1 = Read();
    List L2 = Read();
    
    Print(Multiply(L1, L2));
    Print(Add(L1, L2));
    return 0;
}