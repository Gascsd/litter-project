#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TREE_HT 50

// 用结构体表示哈夫曼的树结构
struct TreeNode {
    char data;
    unsigned frequency;
    struct TreeNode* left, * right;
};

// 哈夫曼编码的结构体
struct HuffmanCode {
    char c;
    char code[MAX_TREE_HT];
    int length;
};

// 构建哈夫曼树，并返回根节点
struct TreeNode* build_huffman_tree(char data[], unsigned frequency[], int size)
{
    struct TreeNode* left, * right, * top;
    top = NULL;

    //创建优先队列，元素为指向哈夫曼树节点的指针
    struct TreeNode** queue = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    int queue_size = 0;

    // 创建节点并添加到优先队列中
    for (int i = 0; i < size; i++) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->data = data[i];
        node->frequency = frequency[i];
        node->left = node->right = NULL;
        queue[queue_size++] = node;
    }

    // 不断从优先队列中取出最小的两个元素，合并为一个新的元素，并将其插入到优先队列中
    while (queue_size > 1) {
        left = queue[0];
        right = queue[1];

        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->data = '@';
        node->frequency = left->frequency + right->frequency;
        node->left = left;
        node->right = right;
        top = node;

        // 把新节点插入到队列中
        queue_size--;
        int i;
        for (i = 2; i <= queue_size; i++) {
            if (node->frequency <= queue[i - 1]->frequency) {
                queue[i - 2] = node;
                break;
            }
            else {
                queue[i - 2] = queue[i - 1];
            }
        }
        if (i == queue_size + 1) {
            queue[i - 2] = node;
        }
    }

    // 释放队列内存
    free(queue);

    return top;
}

// 递归地遍历哈夫曼树，生成哈夫曼编码表并返回哈夫曼编码的结构体数组
void build_codec_table(struct TreeNode* root, char* arr, int top, struct HuffmanCode* table)
{
    // 如果节点是叶子节点，则生成哈夫曼编码，保存到哈夫曼编码表中
    if (root->left == NULL && root->right == NULL) {
        table[root->data].c = root->data;
        table[root->data].length = top;
        memcpy(table[root->data].code, arr, top);
        return;
    }

    // 处理左子树，将编码位添加到arr中
    arr[top] = '0';
    build_codec_table(root->left, arr, top + 1, table);

    // 处理右子树，将编码位添加到arr中
    arr[top] = '1';
    build_codec_table(root->right, arr, top + 1, table);
}

// 对输入的字符串进行哈夫曼编码
void encode(char* message, struct TreeNode* root, struct HuffmanCode* table, char* code)
{
    int i = 0, j = 0;
    while (message[i] != '\0') {
        int k = message[i];
        for (int n = 0; n < table[k].length; n++) {
            code[j++] = table[k].code[n];
        }
        i++;
    }
    code[j] = '\0';
}

// 对哈夫曼编码串进行译码，返回译码的字符串
char* decode(char* code, struct TreeNode* root, int n)
{
    int i = 0, j = 0;
    char* message = (char*)malloc(n * sizeof(char));
    struct TreeNode* p = root;
    while (i < n) {
        if (code[i] == '0') {
            p = p->left;
        }
        else {
            p = p->right;
        }
        if (p->left == NULL && p->right == NULL) {
            message[j++] = p->data;
            p = root;
        }
        i++;
    }
    message[j] = '\0';
    return message;
}

// 打印哈夫曼编码表
void print_table(struct HuffmanCode* table)
{
    printf("Character\tCode\n---------------------\n");
    for (int i = 0; i < 256; i++) {
        if (table[i].length > 0) {
            printf("%c\t\t", table[i].c);
            for (int j = 0; j < table[i].length; j++) {
                printf("%c", table[i].code[j]);
            }
            printf("\n");
        }
    }
}


void menu()
{
    printf("********************************\n");
    printf("********哈夫曼编码译码器********\n");
    printf("**********1.编码****************\n");
    printf("**********2.译码****************\n");
    printf("**********3.打印编码表**********\n");
    printf("**********0.退出****************\n");
    printf("请选择：>");
}
void read_message(char* message)//读取原始信息
{
    FILE* fp = fopen("message.txt", "r");
    fscanf(fp, "%s", message);
    fclose(fp);
}
//从文件中读取编码后的串
void read_code(char* code)
{
    FILE* fp = fopen("code.txt", "r");
    fscanf(fp, "%s", code);
    fclose(fp);
}
char* Encode(char* message, char* code, struct TreeNode* root, struct HuffmanCode* table)//编码
{
    // 根据哈夫曼编码表对输入的字符串进行编码

    encode(message, root, table, code);

    printf("Original Message: %s\n", message);
    printf("Encoded Message:  %s\n", code);
    return code;
}
void Decode(struct TreeNode* root)//译码
{
    char code[128];
    read_code(code);
    // 对编码后的字符串进行解码
    char* decoded = decode(code, root, strlen(code));
    printf("Decoded Message:  %s\n", decoded);
}
void Print(struct HuffmanCode* table)// 打印哈夫曼编码表
{
    print_table(table);
}
void System()
{
    char data[] = "abcde";
    unsigned int frequency[] = { 5, 9, 12, 13, 16 };
    int size = sizeof(data) / sizeof(data[0]);

    // 构建哈夫曼树
    struct TreeNode* root = build_huffman_tree(data, frequency, size);

    // 构建哈夫曼编码表
    struct HuffmanCode* table = (struct HuffmanCode*)calloc(256, sizeof(struct HuffmanCode));
    char arr[MAX_TREE_HT];
    int top = 0;
    build_codec_table(root, arr, top, table);


    char message[128] = { 0 };
    read_message(message);
    char* code = (char*)malloc(strlen(message) * MAX_TREE_HT * sizeof(char));
    int input = 0;
    do
    {
        menu();
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            Encode(message, code, root, table);
            break;
        case 2:
            Decode(root);
            break;
        case 3:
            Print(table);
            break;
        case 0:
            printf("exit\n");
            exit(0);
        default:
            printf("输入错误！\n");
        }
    } while (input);
}

int main()
{
    System();
    return 0;
}