//
//  main.cpp
//  SortTopics
//
//  Created by yisinian1 on 16/8/27.
//  Copyright © 2016年 yisinian1. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include<iomanip>
using std::setw;
using std::fixed;
#include<fstream>
using std::ifstream;
using std::ofstream;
using std::flush;
#include "SortClass.hpp"

using namespace std;

#define LENGTH 100000//排序长度为10000的数组
typedef float dataType;

//定义一个计时的类。
class Time_count//时间计时类，需要#include< ctime>
{
private:
    clock_t start_,end_;
    double duration;//记录时间
public:
    Time_count()
    {
        start_=clock();   //实例化时就开始计时
    }
    void show_time()  //输出时间间隔
    {
        end_=clock();
        duration = (double)(end_-start_)/CLOCKS_PER_SEC;
        cout<<"spend time "<< duration<< " seconds"<< endl;
    }
    double getSortDuration(){
        return this->duration;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    /*****************************************************************
     *随机生成20个长度为LENGTH数组，测试各种排序算法在20次排序所花费的平均时间
     ***************************************************************/
    ofstream *ofs;
    string fileName = "/Users/laidepo/Desktop/SortTopics/sortResult.txt";  //设置成当前项目所在的路径
    ofs = new ofstream(fileName.c_str(),ios::out|ios::app);
    vector<dataType> array;
    SortClass<dataType> testSort;
    SortClass<int> testSort2;
    ofs->close();
    map<string,double> timeMap; //计算平均时间
    ofs->open(fileName.c_str(),ios::out|ios::app);
    if( ofs->fail()){
        cout<<"!!";
        ofs->close();
    }
    for(int i = 0; i < 20;i++){
        //生成随机数组
        testSort.generateRandomArray(array, LENGTH,0,999999);
        int len = array.size();
        
        vector<dataType> ans(array);
        Time_count t1;
        testSort.bubbleSort(ans);    //冒泡排序
        cout<<"1.after bubble sort:"<<endl;
        t1.show_time();
        *ofs<<"第"<<i<<"次冒泡排序:\n " <<"        Time:    " << t1.getSortDuration() <<  " seconds\n";
        timeMap["bubble sort"] += t1.getSortDuration();
        
        
        ans.assign(array.begin(),array.end());
        Time_count t2;
        testSort.selectionSort(ans);    //直接选择排序
        cout<<"2.after selection sort:"<<endl;
        t2.show_time();
        *ofs<<"第"<<i<<"次直接选择排序:\n " <<"        Time:    " << t2.getSortDuration() <<  " seconds\n";
        timeMap["selection sort"] += t2.getSortDuration();
        
        ans.assign(array.begin(),array.end());
        Time_count t3;
        testSort.insertSort(ans);   //插入排序
        cout<<"3.after insertion sort:"<<endl;
        t3.show_time();
        *ofs<<"第"<<i<<"次插入排序:\n " <<"        Time:    " << t3.getSortDuration() <<  " seconds\n";
        timeMap["insertion sort"] += t3.getSortDuration();
        
        ans.assign(array.begin(),array.end());
        Time_count t4;
        testSort.shellSort(ans);    //希尔排序
        cout<<"4.after shell sort:"<<endl;
        t4.show_time();
        *ofs<<"第"<<i<<"次希尔排序:\n " <<"        Time:    " << t4.getSortDuration() <<  " seconds\n";
        timeMap["shell sort"] += t4.getSortDuration();
        
        ans.assign(array.begin(),array.end());
        Time_count t5;
        testSort.mergeSort(ans, 0, len-1);    //归并排序
        cout<<"5.after merge sort:"<<endl;
        t5.show_time();
        *ofs<<"第"<<i<<"次归并排序:\n " <<"        Time:    " << t5.getSortDuration() <<  " seconds\n";
        timeMap["merge sort"] += t5.getSortDuration();
        
        ans.assign(array.begin(),array.end());
        Time_count t6;
        testSort.quickSort(ans, 0, len-1);   //快速排序
        cout<<"6.after quick sort:"<<endl;
        t6.show_time();
        *ofs<<"第"<<i<<"次快速排序:\n " <<"        Time:    " << t6.getSortDuration() <<  " seconds\n";
        timeMap["quick sort"] += t6.getSortDuration();
        
        ans.assign(array.begin(),array.end());
        Time_count t7;
        testSort.heapSort(ans);   //堆排序
        cout<<"7.after heap sort:"<<endl;
        t7.show_time();
        *ofs<<"第"<<i<<"次堆排序:\n " <<"        Time:    " << t7.getSortDuration() <<  " seconds\n";
        timeMap["heap sort"] += t7.getSortDuration();
        
        ans.assign(array.begin(),array.end());
        Time_count t8;
        testSort.comparisonCountingSort(ans);     //比较计数排序
        cout<<"8.after comparisonCounting sort:"<<endl;
        t8.show_time();
        *ofs<<"第"<<i<<"次比较计数排序:\n " <<"        Time:    " << t8.getSortDuration() <<  " seconds\n";
        timeMap["comparisonCounting sort"] += t8.getSortDuration();
        
        //分布计数排序
        vector<int> ans2;
        testSort2.generateRandomArray(ans2, LENGTH, -24, 100);
        Time_count t9;
        testSort2.distributionCountingSort(ans2);
        cout<<"9.after distributionCounting sort:"<<endl;
        t9.show_time();
        *ofs<<"第"<<i<<"次分布计数排序:\n " <<"        Time:    " << t9.getSortDuration() <<  " seconds\n";
        timeMap["distributionCounting sort"] += t9.getSortDuration();
        
        //STL库函数排序
        ans.assign(array.begin(),array.end());
        Time_count t10;
        testSort.stlSort(ans);     //stl库函数排序
        cout<<"10.after STL sort:"<<endl;
        t10.show_time();
        *ofs<<"第"<<i<<"次STL排序:\n " <<"        Time:    " << t10.getSortDuration() <<  " seconds\n";
        timeMap["STL sort"] += t10.getSortDuration();
        
        
        cout<<endl;
    }
    
    //求20次的平均时间
    for (int i=1; i<11; i++) {
        double avergeT;
        switch (i) {
            case 1:
                avergeT = timeMap["bubble sort"]/20;
                *ofs<<"冒泡排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 2:
                avergeT = timeMap["selection sort"]/20;
                *ofs<<"选择排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 3:
                avergeT = timeMap["insertion sort"]/20;
                *ofs<<"插入排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 4:
                avergeT = timeMap["shell sort"]/20;
                *ofs<<"希尔排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 5:
                avergeT = timeMap["merge sort"]/20;
                *ofs<<"归并排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 6:
                avergeT = timeMap["quick sort"]/20;
                *ofs<<"快速排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 7:
                avergeT = timeMap["heap sort"]/20;
                *ofs<<"堆排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 8:
                avergeT = timeMap["comparisonCounting sort"]/20;
                *ofs<<"比较计数排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 9:
                avergeT = timeMap["distributionCounting sort"]/20;
                *ofs<<"分布计数排序的平均时间为： " << avergeT << " seconds\n";
                break;
            case 10:
                avergeT = timeMap["STL sort"]/20;
                *ofs<<"STL库排序的平均时间为： " << avergeT << " seconds\n";
                break;
            default:
                break;
        }
        
    }
    
    ofs->close();  //关闭文件
    
    return 0;
}
