#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//定义一个数据类型，名字为
typedef struct Arr
{
	int* p_Base;	//存储数组第一个元素的地址
	size_t len;	//数组所能容纳的最大元素个数
	size_t cnt;	//当前数组有效元素的个数
	size_t increment;	//自动增长因子
}Arr;

void Init_Arr(Arr* arr, size_t lenght)	//初始化数组
{
	arr->p_Base = (int*)malloc(sizeof(int) * lenght);
	if (NULL == arr->p_Base) {
		return;
	}
	arr->len = lenght;
	arr->cnt = 0;
	return;
}

bool Is_Full(Arr* arr)	//判断数组是否为满
{
	if (arr->cnt == arr->len) {
		return true;
	}
	else {
		return false;
	}
}

bool Is_Empty(Arr* arr)	//判断数组是否为空
{
	if (0 == arr->cnt) {
		return true;
	}
	else {
		return false;
	}
}

void Show_Arr(Arr* arr)	//输出数组
{
	if (Is_Empty(arr)) {
		printf("数组为空。\n");
	}
	else {
		for (int i = 0; i < arr->cnt; i++) {
			printf("%d ", arr->p_Base[i]);
		}
		printf("\n");
	}
	return;
}

bool Append_Arr(Arr* arr, int val)
{
	if (Is_Full(arr)) {
		return false;
	}
	else {
		arr->p_Base[arr->cnt++] = val;
		return true;
	}
}

bool Inset_Arr(Arr* arr, size_t pos, int val)	//pos表示要在第pos个数前面插入val
{
	if (Is_Full(arr) || 1 > pos || pos > arr->cnt) {
		return false;
	}
	size_t i;
	for (i = arr->cnt - 1; i >= pos - 1; i--) {
		arr->p_Base[i + 1] = arr->p_Base[i];
	}
	arr->p_Base[pos - 1] = val;
	arr->cnt++;
	return true;
}

bool Delete_Arr(Arr* arr, size_t pos, int* dval)	//pos表示要删除第pos个元素
{
	if (Is_Empty(arr) || arr->cnt < pos || pos < 0) {
		return false;
	}
	size_t i;
	*dval = arr->p_Base[pos - 1];
	for (i = pos - 1; i < arr->cnt - 1; i++) {
		arr->p_Base[i] = arr->p_Base[i + 1];
	}
	arr->cnt--;
	return true;
}

void Inversion_Arr(Arr* arr)
{
	for (size_t i = 0, j = arr->cnt - 1; i < j; i++, j--) {
		int temp = arr->p_Base[i];
		arr->p_Base[i] = arr->p_Base[j];
		arr->p_Base[j] = temp;
	}
	return;
}

void Sort_Arr(Arr* arr)
{
	for (int i = 0; i < arr->cnt - 1; i++) {
		for (int j = 0; j < arr->cnt - i - 1; j++) {
			if (arr->p_Base[j] > arr->p_Base[j + 1]) {
				int temp = arr->p_Base[j];
				arr->p_Base[j] = arr->p_Base[j + 1];
				arr->p_Base[j + 1] = temp;
			}
		}
	}
}

int main()
{
	Arr arr;
	int dval;
	Init_Arr(&arr, 6);
	Append_Arr(&arr, 1);
	Append_Arr(&arr, 2);
	Append_Arr(&arr, 3);
	Append_Arr(&arr, 4);
	Append_Arr(&arr, 5);
	Append_Arr(&arr, 6);
	Append_Arr(&arr, 7);
	Inset_Arr(&arr, 3, 99);
	if (Delete_Arr(&arr, 3, &dval)) {
		printf("%d\n", dval);
	}
	else {
		printf("删除失败。\n");
	}
	Inversion_Arr(&arr);
	Show_Arr(&arr);
	Sort_Arr(&arr);
	Show_Arr(&arr);
	return 0;
}