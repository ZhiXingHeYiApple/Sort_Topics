//
//  SortClass.hpp
//  SortTopics
//
//  Created by 赖德朴 on 16/8/31.
//  Copyright © 2016年 yisinian1. All rights reserved.
//

#ifndef SortClass_hpp
#define SortClass_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;


template <class numtype> //声明一个模板，虚拟类型名为numtype
class SortClass{
public:
    //生成长度为n，数据范围在low～high中的数据
    void generateRandomArray(vector<numtype> &array,int n, int low, int high)
    {
        int i=0;
        array.resize(n);
        //time(0)或者time(NULL)返回的是系统的时间（从1970.1.1午夜算起），单位：秒
        srand( (unsigned)time( NULL ) );   //设置rand()产生随机数时的随机数种子,默认值为1
        while(i<n)
        {
            array[i++]= (numtype)((rand()%(high-low)+low)+rand()%10000/10000.0);
        }
    }
    
    //冒泡排序 (Bubble Sort)
    void bubbleSort(vector<numtype> &array);
    //选择排序（Selection Sort
    void selectionSort(vector<numtype> &array);
    //插入排序（Insertion Sort）
    void insertSort(vector<numtype> &array);
    //希尔排序（Shell Sort）
    void shellSort(vector<numtype> &array);
    //归并排序（Merge Sort）
    void mergeSort(vector<numtype> &array, int low,int high);
    //快速排序（Quick Sort）
    void quickSort(vector<numtype> &array,int p,int r);
    //堆排序（Heap Sort）
    void heapSort(vector<numtype> &array);
    //比较计数排序（Count Sort）
    void comparisonCountingSort(vector<numtype> &array);
    
    //分布计数排序（数据类型应该为整形，要能作为数组的下标）
    void distributionCountingSort(vector<int> &array);
    
    //STL sort
    //STL的sort函数在数据量大时采用快排，分段递归排序，一旦分段后的数据小于某个值，就改用插入排序。如果递归层次过深，还会改用堆排序。这样就结合了各类算法的所有优点。
    void stlSort(vector<numtype> &array);
    
private:
    //进行元素交换操作
    void exchange(numtype &num1,numtype &num2){
        numtype temp = num1;
        num1 = num2;
        num2 = temp;
    }
    
    //归并排序时，对两个有序数组的归并操作
    void merge(vector<numtype> &array, int low,int m,int high){
        vector<numtype> arr1(array.begin()+low,array.begin()+m+1);  //注意迭代器区间为左闭右开
        vector<numtype> arr2(array.begin()+m+1,array.begin()+high+1);
        int len1 = arr1.size();
        int len2 = arr2.size();
        int index1=0,index2=0;
        int index=low;
        while (index1<len1&&index2<len2) {
            if (arr1[index1]<arr2[index2]) {
                array[index++] = arr1[index1++];
            } else {
                array[index++] = arr2[index2++];
            }
        }
        if (index1<len1) {
            while (index1<len1) {
                array[index++] = arr1[index1++];
            }
        } else {
            while (index2<len2) {
                array[index++] = arr2[index2++];
            }
        }
    }
    
    //快速排序的分区函数
    int partition(vector<numtype> &array,int p, int r){  //区间都是左右闭合的 array[p...r]
        int j=p-1;
        for (int i=p; i<r; i++) {
            if (array[i]<array[r]) {
                j++;
                exchange(array[j], array[i]);
            }
        }
        exchange(array[r], array[j+1]);
        return j+1;  //返回基准云所在的下标
    }
    
    //堆排序的操作函数
    //求父节点，孩子节点的下标索引(从0开始)
    int parent(int i){
        return (i-1)>>1;
    }
    int leftChild(int i){
        return 2*i+1;
    }
    int rightChild(int i){
        return 2*(i+1);
    }
    //建立堆操作(大顶堆)
    void buildHeap(vector<numtype> &array){
        int k = (array.size()-1)/2;  //从倒数的第一个非叶节点开始调整
        for (int i=k; i>=0; i--) {
            siftDown(array, array.size(), i);
        }
    }
    //上滤操作
    void siftUp(vector<numtype> &array,int size,int index){
        int p=parent(index);
        if (p>=0 && array[index]>array[p]) {  //需要调整
            exchange(array[index], array[p]);
            siftUp(array, size, p);
        }
    }
    //下滤操作
    //注意：需要传入一个参数size，标示无序区的范围
    void siftDown(vector<numtype> &array,int size,int index){
        int largest = index;
        int l = leftChild(index);
        int r = rightChild(index);
        //l<size很关键，避免数组越界
        if (l<size && array[l]>array[largest]) {   //错误写法 array[l]>array[index]
            largest=l;
        }//错误else if(){}  ,两部分都需要执行到
        //r<size很关键，避免数组越界
        if (r<size && array[r]>array[largest]){  //错误写法 array[r]>array[index]
            largest=r;
        }
        if (largest!=index) {  //需要调整
            exchange(array[largest], array[index]);
            siftDown(array, size, largest);
        }
    }
    
};
//各种排序的实现(全部以升序排序)
//冒泡排序 (Bubble Sort)
template<class numtype> void SortClass<numtype>::bubbleSort(vector<numtype> &array){
    int len = array.size();
    for (int i=len-1; i>0; i--) {
        bool doSwap = false;
        for (int j=0; j<i; j++) {
            if (array[j]>array[j+1]) {
                exchange(array[j], array[j+1]);
                doSwap = true;
            }
        }
        if(!doSwap) break;
    }
}

//选择排序（Selection Sort）
template<class numtype> void SortClass<numtype>::selectionSort(vector<numtype> &array){
    int len = array.size();
    for (int i=0; i<len-1; i++) {
        int minIndex = i;
        for (int j=i+1; j<len; j++) {
            if (array[j]<array[minIndex]) {
                minIndex = j;
            }
        }
        exchange(array[i], array[minIndex]);
    }
}

//插入排序（Insertion Sort）
template<class numtype> void SortClass<numtype>::insertSort(vector<numtype> &array){
    int len = array.size();
    for(int i=1;i<len;i++){
        int key = array[i];
        int j=i-1;
        while (j>=0&&key<array[j]) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1]=key;
    }
}

//希尔排序（Shell Sort）
//对于希尔排序来说，步长为 1， 4， 13， 40， 121的效率是最高的
template<class numtype> void SortClass<numtype>::shellSort(vector<numtype> &array){
    int step[5] = {1,4,13,40,121};    //步长最终应该为1,才能收敛
    int len = array.size();
    if (len==0) {
        return;
    }
    int index=4;
    int gap;
    //确定初始采用哪个步长
    while (index>=0) {
        if(step[index]<len){
            gap = step[index];
            break;
        }
        index--;
    }
    //shell sort
    while (index>=0) {
        for (int i=gap; i<len; i++) {  //以gap作为步长进行插入排序
            numtype key = array[i];
            int j=i-gap;
            while (j>=0&&key<array[j]) {
                array[j+gap] = array[j];
                j -= gap;
            }
            array[j+gap] = key;
        }
        gap = step[--index];   //调整步长
    }
}

//归并排序（Merge Sort）递归方式
template<class numtype> void SortClass<numtype>::mergeSort(vector<numtype> &array, int low,int high){
    if (low<high) {
        int m = (low+high)>>1;
        mergeSort(array, low, m);
        mergeSort(array, m+1, high);
        merge(array, low, m, high);
    }
}

//快速排序（Quick Sort）递归方式
template<class numtype> void SortClass<numtype>::quickSort(vector<numtype> &array,int p,int r){
    if (p<r) {
        int q = partition(array, p, r);
        quickSort(array, p, q-1);
        quickSort(array, q+1, r);
    }
}


//堆排序（Heap Sort）

template<class numtype> void SortClass<numtype>::heapSort(vector<numtype> &array){
    int len = array.size();
    if (len==0) {
        return;
    }
    //建立大顶堆
    buildHeap(array);
    //heap sort
    for (int i=len-1; i>0; i--) {
        //取出堆顶元素，放入有序区，然后对无序区调整重新得到堆结构
        exchange(array[0], array[i]);
        siftDown(array,i, 0);
    }
}

//比较计数排序
template<class numtype> void SortClass<numtype>::comparisonCountingSort(vector<numtype> &array){
    int len = array.size();
    if (len==0) {
        return;
    }
    vector<numtype> copyArr(array);  //拷贝
    vector<int> countV(len,0);
    //计数过程
    for (int i=0; i<len; i++) {
        for (int j=i+1; j<len; j++) {
            if (array[i]<array[j]) {
                countV[j]++;
            }else{
                countV[i]++;
            }
        }
    }
    //
    for (int i=0; i<len; i++) {
        array[countV[i]] = copyArr[i];
    }
}

//分布计数排序
template<class numtype> void SortClass<numtype>::distributionCountingSort(vector<int> &array){
    int len = array.size();
    if (len==0) {
        return;
    }
    vector<int> copyArr(array);
    //确定数组元素集合的上下限
    int minV=array[0],maxV = array[0];
    for (int i=1; i<len; i++) {
        if (array[i]<minV) {
            minV = array[i];
        }
        if (array[i]>maxV) {
            maxV = array[i];
        }
    }
    //初始化频率数组
    vector<int> d(maxV-minV+1,0);
    //计算频率值
    for (int i=0; i<len; i++) {
        d[array[i]-minV]++;
    }
    //重用于分布
    for (int i=1; i<d.size(); i++) {
        d[i] += d[i-1];
    }
    //分布值指出了在最后的有序数组中，分不值对应的元素的“最后一次”出现时的正确位置
    
    for (int i=len-1; i>=0; i--) {
        int index = copyArr[i]-minV;  //d数组的下标索引
        array[d[index]-1] = copyArr[i];
        d[index]--;
    }
}


template<class numtype> void SortClass<numtype>::stlSort(vector<numtype> &array){
    sort(array.begin(), array.end());
}


#endif /* SortClass_hpp */
