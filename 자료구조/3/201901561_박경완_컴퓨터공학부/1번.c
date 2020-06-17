#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//Ʈ�����
typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;


//��ȯ���� Ž�� �Լ�

TreeNode *search(TreeNode *node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

/*
// �ݺ����� Ž�� �Լ� (��ȯ�� �Լ��� �̿��ϰڽ��ϴ�)
TreeNode *search(TreeNode *node, int key)
{
	while(node != NULL){
		if( key == node->key ) return node;
		else if( key < node->key )
			node = node->left;
		else
			node = node->right;
	}
	return NULL; // Ž���� �������� ��� NULL ��ȯ
}
*/

//����Ž��Ʈ�������� ���Կ���


TreeNode * new_node(int item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}


TreeNode * insert_node(TreeNode * node, int key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (node == NULL) return new_node(key);
	// �׷��� ������ ��ȯ������ Ʈ���� ��������.
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
	return node;
}

//���� �Լ�


TreeNode * min_value_node(TreeNode * node)
{
	TreeNode * current = node;
	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;
	return current;
}

// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ�
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�.
TreeNode * delete_node(TreeNode * root, int key)
{
	if (root == NULL) return root;
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��

	else {
		// ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode * temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode * temp = root->left;
			free(root);
			return temp;
		}
		// �� ��° ���
		TreeNode * temp = min_value_node(root->right);
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

// ���� ��ȸ
TreeNode * inorder(TreeNode *root) {
	if (root) {
		inorder(root->left); // ���ʼ���Ʈ�� ��ȸ
		printf("[ %d ]", root->key); // ��� �湮
		inorder(root->right); // �����ʼ���Ʈ�� ��ȸ
	}
}




int main(void)
{
	TreeNode * root = NULL;
	TreeNode * tmp = NULL;
	root = insert_node(root, 15);
	root = insert_node(root, 10);
	root = insert_node(root, 16);
	root = insert_node(root, 4);
	root = insert_node(root, 12);
	root = insert_node(root, 20);
	root = insert_node(root, 7);
	root = insert_node(root, 17);
	root = insert_node(root, 25);
	root = insert_node(root, 6);
	root = insert_node(root, 8);
	root = insert_node(root, 18);
	root = insert_node(root, 21);
	root = insert_node(root, 27);

	printf("���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n");

	printf("4 -> 13 \n");
	//4�� �����, 13�� ���� �־��ݴϴ�.
	root = delete_node(root, 4);
	root = insert_node(root, 13);
	inorder(root);
	printf("\n\n");


	printf("20 -> 5 \n");
	//20�� �����, 5�� ���� �־��ݴϴ�.
	root = delete_node(root, 20);
	root = insert_node(root, 5);
	inorder(root);
	printf("\n\n");

	return 0;
}