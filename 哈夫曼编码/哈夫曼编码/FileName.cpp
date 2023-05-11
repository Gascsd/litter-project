#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TREE_HT 50

// �ýṹ���ʾ�����������ṹ
struct TreeNode {
    char data;
    unsigned frequency;
    struct TreeNode* left, * right;
};

// ����������Ľṹ��
struct HuffmanCode {
    char c;
    char code[MAX_TREE_HT];
    int length;
};

// �������������������ظ��ڵ�
struct TreeNode* build_huffman_tree(char data[], unsigned frequency[], int size)
{
    struct TreeNode* left, * right, * top;
    top = NULL;

    //�������ȶ��У�Ԫ��Ϊָ����������ڵ��ָ��
    struct TreeNode** queue = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    int queue_size = 0;

    // �����ڵ㲢��ӵ����ȶ�����
    for (int i = 0; i < size; i++) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->data = data[i];
        node->frequency = frequency[i];
        node->left = node->right = NULL;
        queue[queue_size++] = node;
    }

    // ���ϴ����ȶ�����ȡ����С������Ԫ�أ��ϲ�Ϊһ���µ�Ԫ�أ���������뵽���ȶ�����
    while (queue_size > 1) {
        left = queue[0];
        right = queue[1];

        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->data = '@';
        node->frequency = left->frequency + right->frequency;
        node->left = left;
        node->right = right;
        top = node;

        // ���½ڵ���뵽������
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

    // �ͷŶ����ڴ�
    free(queue);

    return top;
}

// �ݹ�ر����������������ɹ�������������ع���������Ľṹ������
void build_codec_table(struct TreeNode* root, char* arr, int top, struct HuffmanCode* table)
{
    // ����ڵ���Ҷ�ӽڵ㣬�����ɹ��������룬���浽�������������
    if (root->left == NULL && root->right == NULL) {
        table[root->data].c = root->data;
        table[root->data].length = top;
        memcpy(table[root->data].code, arr, top);
        return;
    }

    // ������������������λ��ӵ�arr��
    arr[top] = '0';
    build_codec_table(root->left, arr, top + 1, table);

    // ������������������λ��ӵ�arr��
    arr[top] = '1';
    build_codec_table(root->right, arr, top + 1, table);
}

// ��������ַ������й���������
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

// �Թ��������봮�������룬����������ַ���
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

// ��ӡ�����������
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
    printf("********����������������********\n");
    printf("**********1.����****************\n");
    printf("**********2.����****************\n");
    printf("**********3.��ӡ�����**********\n");
    printf("**********0.�˳�****************\n");
    printf("��ѡ��>");
}
void read_message(char* message)//��ȡԭʼ��Ϣ
{
    FILE* fp = fopen("message.txt", "r");
    fscanf(fp, "%s", message);
    fclose(fp);
}
//���ļ��ж�ȡ�����Ĵ�
void read_code(char* code)
{
    FILE* fp = fopen("code.txt", "r");
    fscanf(fp, "%s", code);
    fclose(fp);
}
char* Encode(char* message, char* code, struct TreeNode* root, struct HuffmanCode* table)//����
{
    // ���ݹ�����������������ַ������б���

    encode(message, root, table, code);

    printf("Original Message: %s\n", message);
    printf("Encoded Message:  %s\n", code);
    return code;
}
void Decode(struct TreeNode* root)//����
{
    char code[128];
    read_code(code);
    // �Ա������ַ������н���
    char* decoded = decode(code, root, strlen(code));
    printf("Decoded Message:  %s\n", decoded);
}
void Print(struct HuffmanCode* table)// ��ӡ�����������
{
    print_table(table);
}
void System()
{
    char data[] = "abcde";
    unsigned int frequency[] = { 5, 9, 12, 13, 16 };
    int size = sizeof(data) / sizeof(data[0]);

    // ������������
    struct TreeNode* root = build_huffman_tree(data, frequency, size);

    // ���������������
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
            printf("�������\n");
        }
    } while (input);
}

int main()
{
    System();
    return 0;
}