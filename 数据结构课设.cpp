#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MaxSize 80000
using namespace std; 

//交换两个元素；

void swap(int &a,int &b){
	int temp=a;
	a=b;
	b=temp;
}


//直接插入排序On2；算法稳定
void InsertSort(int A[],int n){
	int i,j,temp;
	for(i=1;i<n;i++)             //将各元素插入已排好的序列中
		if(A[i]<A[i-1]){         //若A[i]小于其前驱
			temp=A[i];         
			for(j=i-1;j>=0&&A[j]>temp;j--)   
				A[j+1]=A[j];               //所有大于temp的元素往后挪
			A[j+1]=temp;                   
		} 
}



//冒泡排序(从后往前冒泡，最小的数到前面)；On2 算法稳定
void BubbleSort(int A[],int n){
	for(int i=0;i<n-1;i++){
		bool flag=false;  //表示本趟冒泡是否发生交换的标志
		for(int j=n-1;j>i;j--)  
			if(A[j-1]>A[j]){    
				swap(A[j-1],A[j]);
				flag=true;
			}
			if(flag==false)
				return;   //本趟没有发生交换，说明已经有序
	}
}


//选择排序；
void SelectSort(int A[],int n){
	int i,j;
	for(i=0;i<n-1;i++){
		int min=i;
		for(j=i+1;j<n;j++)
			if(A[j]<A[min])
				min=j;
		swap(A[min],A[i]);
	}
}

//划分；
int  Partition(int A[],int low,int high){
	int pivot=A[low];  //用第一个元素作为枢纽
	while(low<high){            
		while(low<high&&A[high]>=pivot)
			high--;
		A[low]=A[high];       //比枢纽小的元素移动到左端
		while(low<high&&A[low]<=pivot)
			low++;
		A[high]=A[low];       //比枢纽大的元素移动到右端
	}
	A[low]=pivot;               //枢纽元素存放到最终位置
	return low;
}

//快速排序； n log n 不稳定
void QuickSort(int A[],int low,int high){
	if(low<high){    //递归跳出的条件
		int pivotpos=Partition(A,low,high);     //划分  
		QuickSort(A,low,pivotpos-1);
		QuickSort(A,pivotpos+1,high);
	}
}


//将以k为根的子树调整为大根堆；
void HeadAdjust(int A[],int k,int len){
	A[0]=A[k];
	for(int i=2*k;i<=len;i*=2){
		if(i<len&&A[i]<A[i+1])
			i++;
		if(A[0]>=A[i]) break;
		else{
			A[k]=A[i];
			k=i;
		}
	}
	A[k]=A[0];
}


//建立大根堆
void BuildMaxHeap(int A[],int len){
	for(int i=len/2;i>0;i--)
		HeadAdjust(A,i,len);
}


//堆排序   不稳定     建堆 On 排序O nlog n 
void HeapSort(int A[],int len){
	BuildMaxHeap(A,len);
	for(int i=len;i>1;i--){
		swap(A[i],A[1]);
		HeadAdjust(A,1,i-1);
	}
}

int B[MaxSize];
void Merge(int A[],int low,int mid,int high){
	int i,j,k;
	for(k=low;k<=high;k++)
		B[k]=A[k];
	for(i=low,j=mid+1,k=i;i<=mid&&j<=high;k++){
		if(B[i]<=B[j])
			A[k]=B[i++];   //将较小的数复制到A中
		else
			A[k]=B[j++];
	}
	while(i<=mid) A[k++]=B[i++];
	while(j<=high) A[k++]=B[j++];
}


//归并排序；O nlogn 稳定
void MergeSort(int A[],int low,int high){
	if(low<high){
		int mid=(low+high)/2; //从中间划分
		MergeSort(A,low,mid);  //对左半部分归并排序
		MergeSort(A,mid+1,high);  //对右半部分归并排序
		Merge(A,low,mid,high);  //归并；
	}
} 

//辅助函数，求数据的最大位数
int maxbit(int data[], int n) {
    int maxData = data[0];              ///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;

}
 //基数排序 稳 O(d(n+r))
void radixsort(int data[], int n)
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete []tmp;
    delete []count;
}

void Menu(){
		cout<<"************************************************\n";
		cout<<"************欢迎使用排序综合演示系统************\n";
		cout<<"***      插入排序请按 1                      ***\n";
		cout<<"***      冒泡排序请按 2                      ***\n";
		cout<<"***      选择排序请按 3                      ***\n";
		cout<<"***      快速排序请按 4                      ***\n";
		cout<<"***      归并排序请按 5                      ***\n";
		cout<<"***      堆  排序请按 6                      ***\n";
		cout<<"***      基数排序请按 7                      ***\n";
		cout<<"***      综合排序请按 8                      ***\n";
		cout<<"***      退出请按     0                      ***\n";
		cout<<"************************************************\n";
}

void File(int a[],int n){		
	FILE * fp;
	fp= fopen("C:\\Users\\HH\\Desktop\\输出结果.txt","w") ;
	for(int i=0;i<n;i++)
			fprintf(fp,"%-8d ",a[i]) ;
		if(fp!=NULL)
		fclose(fp) ; //关闭文件

}
void main(){
int c;
	int a[MaxSize];
	int b[MaxSize];
	int arr[MaxSize+1];
	int n=-1;
    clock_t start, finish ;
	double duration = 0.0 ;
	double t[8];
	while(1){
		Menu();
		cin>>c;
		switch(c){

		case 1:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			cout<<"请输入"<<n<<"个元素：\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];

			start = clock() ;
				InsertSort(a,n);           //插入排序；	
			finish = clock() ;
			duration =  (double)(finish - start) / CLOCKS_PER_SEC;
			cout<<"排序后的结果为：\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" ";   
			   cout<<"\n";
			   printf("排序所用时间：%lf 秒\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 2:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			cout<<"请输入"<<n<<"个元素：\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			start = clock() ;
			BubbleSort(a,n);           //冒泡排序；
			finish = clock() ;
			duration=  (double)(finish - start) / CLOCKS_PER_SEC;
			   cout<<"排序后的结果为：\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
		printf("排序所用时间：%lf 秒\n",duration) ;
		File(a,n);
		a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 3:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			cout<<"请输入"<<n<<"个元素：\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			   SelectSort(a,n);         //选择排序；
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			     cout<<"排序后的结果为：\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			   printf("排序所用时间：%lf 秒\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 4:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			cout<<"请输入"<<n<<"个元素：\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			   QuickSort(a,0,n-1);       //快速排序；
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			    cout<<"排序后的结果为：\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			   printf("排序所用时间：%lf 秒\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 5:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			cout<<"请输入"<<n<<"个元素：\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			   MergeSort(a,0,n-1);          //归并排序；
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			    cout<<"排序后的结果为：\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			  printf("排序所用时间：%lf 秒\n",duration) ;
			  File(a,n);
			  a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 6:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			cout<<"请输入"<<n<<"个元素：\n";
			   for(int i=1;i<=n;i++)
				cin>>a[i];
			   start = clock() ;
			   HeapSort(a,n);            //堆排序；
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			   cout<<"排序后的结果为：\n";
			   for(int i=1;i<=n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			 printf("排序所用时间：%lf 秒\n",duration) ;
			 FILE * fp;
			 fp= fopen("C:\\Users\\HH\\Desktop\\输出结果.txt","w") ;
			 for(int i=1;i<=n;i++)
				 fprintf(fp,"%-8d ",a[i]) ;
		if(fp!=NULL)
		fclose(fp) ; //关闭文件
		a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 7:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			cout<<"请输入"<<n<<"个元素：\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			radixsort(a,n);    //基数排序；
			finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			 cout<<"排序后的结果为：\n";
			 for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			   printf("排序所用时间：%lf 秒\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 8:
			cout<<"请输入待排序元素个数：\n";
			cin>>n;
			srand((unsigned int)time(0));
			for(int i=0;i<n;i++){
				a[i]=rand();
				b[i]=a[i];
				arr[i+1]=a[i];
			}
						cout<<"\n";

			start = clock() ;
				InsertSort(b,n);           //插入排序；	
			finish = clock() ;
			t[1] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("插入排序所用时间：%lf 秒\n",t[1]) ;
			for(int i=0;i<n;i++)
				b[i]=a[i];
			cout<<"\n";

			
			start = clock() ;
				BubbleSort(b,n);           //冒泡排序；	
			finish = clock() ;
			t[2] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("冒泡排序所用时间：%lf 秒\n",t[2]) ;
			for(int i=0;i<n;i++)
				b[i]=a[i];
			cout<<"\n";

			start = clock() ;
				SelectSort(b,n);           //选择排序；	
			finish = clock() ;
			t[3] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("选择排序所用时间：%lf 秒\n",t[3]) ;
			for(int i=0;i<n;i++)
				b[i]=a[i];
			cout<<"\n";

			start = clock() ;
				  QuickSort(b,0,n-1);       //快速排序；	
			finish = clock() ;
			t[4] =  (double)(finish - start) / CLOCKS_PER_SEC;
			  for(int i=0;i<n;i++)
				b[i]=a[i];
			printf("快速排序所用时间：%lf 秒\n",t[4]) ;
			cout<<"\n";

		       start = clock() ;
			   MergeSort(b,0,n-1);          //归并排序；
			   finish = clock() ;
			t[5] =  (double)(finish - start) / CLOCKS_PER_SEC;
			  for(int i=0;i<n;i++)
				b[i]=a[i];
			printf("归并排序所用时间：%lf 秒\n",t[5]) ;
			cout<<"\n";


			start = clock() ;
				 HeapSort(arr,n);            //堆排序；
			finish = clock() ;
			t[6] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("堆排序所用时间：%lf 秒\n",t[6]) ;
			cout<<"\n";


			start = clock() ;
				 radixsort(a,n);    //基数排序；
			finish = clock() ;
			t[7] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("基数排序所用时间：%lf 秒\n",t[7]) ;
			   cout<<"\n";

			  // 输出排序结果；
			  /* cout<<"排序的结果为：\n";
			   for(int i=0;i<n;i++)
				   printf("%d ",a[i]);
			    cout<<"\n";*/
			
			    {int i,k=0,j,k2=0; 
				double t1[8];
					double min1=t[1],min2=99.99;
			   				   for( i=1;i<=7;i++){
								   t1[i]=t[i];
					   if(t[i]<min1){
						   min1=t[i];
						   k=i;
					   }
				   }
							   t1[k]=999.99;
							   
							   for(j=7;j>0;j--){
								   if(t1[j]<=min2){
									   min2=t1[j];
									   k2=j;
								   }
							   }
							
	 
			   FILE * fp2;
			   fp2= fopen("C:\\Users\\HH\\Desktop\\综合排序输出结果.txt","w") ;
			       fprintf(fp2,"\n") ;
				   fprintf(fp2,"插入排序所用时间：%lf 秒\n",t[1]) ;
				   fprintf(fp2,"冒泡排序所用时间：%lf 秒\n",t[2]) ;
				   fprintf(fp2,"选择排序所用时间：%lf 秒\n",t[3]) ;
				   fprintf(fp2,"快速排序所用时间：%lf 秒\n",t[4]) ;
				   fprintf(fp2,"归并排序所用时间：%lf 秒\n",t[5]) ;
				   fprintf(fp2,"堆    排序所用时间：%lf 秒\n",t[6]) ;
				   fprintf(fp2,"基数排序所用时间：%lf 秒\n",t[7]) ;
				   fprintf(fp2,"\n") ;
				   fprintf(fp2,"最快两种的排序为：\n") ;
				   if(k==1)
					    fprintf(fp2,"插入排序：%lf 秒\n",t[1]) ;
				    else if(k==2)
					   fprintf(fp2,"冒泡排序：%lf 秒\n",t[2]) ;
				    else if(k==3)
					   fprintf(fp2,"选择排序：%lf 秒\n",t[3]) ;
				    else if(k==4)
					    fprintf(fp2,"快速排序：%lf 秒\n",t[4]) ;
				    else if(k==5)
					   fprintf(fp2,"归并排序：%lf 秒\n",t[5]) ;
				    else if(k==6)
					    fprintf(fp2,"堆    排序：%lf 秒\n",t[6]) ;
				    else if(k==7)
					   fprintf(fp2,"基数排序：%lf 秒\n",t[7]) ;
					 fprintf(fp2,"\n") ;
					if(k2==1)
					    fprintf(fp2,"插入排序：%lf 秒\n",t[1]) ;
				    else if(k2==2)
					   fprintf(fp2,"冒泡排序：%lf 秒\n",t[2]) ;
				    else if(k2==3)
					   fprintf(fp2,"选择排序：%lf 秒\n",t[3]) ;
				    else if(k2==4)
					    fprintf(fp2,"快速排序：%lf 秒\n",t[4]) ;
				    else if(k2==5)
					   fprintf(fp2,"归并排序：%lf 秒\n",t[5]) ;
				    else if(k2==6)
					    fprintf(fp2,"堆    排序：%lf 秒\n",t[6]) ;
				    else if(k2==7)
					   fprintf(fp2,"基数排序：%lf 秒\n",t[7]) ;
					 fprintf(fp2,"\n") ;
					 fprintf(fp2,"\n") ;
					fprintf(fp2,"排序的结果为：\n") ;
					for(int i=1;i<=n;i++)
						fprintf(fp2,"%-8d ",arr[i]) ;
			   if(fp2!=NULL)
				   fclose(fp2) ; //关闭文件
				}
			system("pause");
			system("cls");
			break ;

		case 0:exit(0);

		default:cout<<"没有你选择的项目请重新选择！\n";
			system("pause");
			system("cls");
	}//switch
	}//while;
}//return；