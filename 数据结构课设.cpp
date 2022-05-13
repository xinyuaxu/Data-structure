#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MaxSize 80000
using namespace std; 

//��������Ԫ�أ�

void swap(int &a,int &b){
	int temp=a;
	a=b;
	b=temp;
}


//ֱ�Ӳ�������On2���㷨�ȶ�
void InsertSort(int A[],int n){
	int i,j,temp;
	for(i=1;i<n;i++)             //����Ԫ�ز������źõ�������
		if(A[i]<A[i-1]){         //��A[i]С����ǰ��
			temp=A[i];         
			for(j=i-1;j>=0&&A[j]>temp;j--)   
				A[j+1]=A[j];               //���д���temp��Ԫ������Ų
			A[j+1]=temp;                   
		} 
}



//ð������(�Ӻ���ǰð�ݣ���С������ǰ��)��On2 �㷨�ȶ�
void BubbleSort(int A[],int n){
	for(int i=0;i<n-1;i++){
		bool flag=false;  //��ʾ����ð���Ƿ��������ı�־
		for(int j=n-1;j>i;j--)  
			if(A[j-1]>A[j]){    
				swap(A[j-1],A[j]);
				flag=true;
			}
			if(flag==false)
				return;   //����û�з���������˵���Ѿ�����
	}
}


//ѡ������
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

//���֣�
int  Partition(int A[],int low,int high){
	int pivot=A[low];  //�õ�һ��Ԫ����Ϊ��Ŧ
	while(low<high){            
		while(low<high&&A[high]>=pivot)
			high--;
		A[low]=A[high];       //����ŦС��Ԫ���ƶ������
		while(low<high&&A[low]<=pivot)
			low++;
		A[high]=A[low];       //����Ŧ���Ԫ���ƶ����Ҷ�
	}
	A[low]=pivot;               //��ŦԪ�ش�ŵ�����λ��
	return low;
}

//�������� n log n ���ȶ�
void QuickSort(int A[],int low,int high){
	if(low<high){    //�ݹ�����������
		int pivotpos=Partition(A,low,high);     //����  
		QuickSort(A,low,pivotpos-1);
		QuickSort(A,pivotpos+1,high);
	}
}


//����kΪ������������Ϊ����ѣ�
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


//���������
void BuildMaxHeap(int A[],int len){
	for(int i=len/2;i>0;i--)
		HeadAdjust(A,i,len);
}


//������   ���ȶ�     ���� On ����O nlog n 
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
			A[k]=B[i++];   //����С�������Ƶ�A��
		else
			A[k]=B[j++];
	}
	while(i<=mid) A[k++]=B[i++];
	while(j<=high) A[k++]=B[j++];
}


//�鲢����O nlogn �ȶ�
void MergeSort(int A[],int low,int high){
	if(low<high){
		int mid=(low+high)/2; //���м仮��
		MergeSort(A,low,mid);  //����벿�ֹ鲢����
		MergeSort(A,mid+1,high);  //���Ұ벿�ֹ鲢����
		Merge(A,low,mid,high);  //�鲢��
	}
} 

//���������������ݵ����λ��
int maxbit(int data[], int n) {
    int maxData = data[0];              ///< �����
    /// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
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
 //�������� �� O(d(n+r))
void radixsort(int data[], int n)
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //������
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //����d������
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //ÿ�η���ǰ��ռ�����
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
        for(j = n - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete []tmp;
    delete []count;
}

void Menu(){
		cout<<"************************************************\n";
		cout<<"************��ӭʹ�������ۺ���ʾϵͳ************\n";
		cout<<"***      ���������밴 1                      ***\n";
		cout<<"***      ð�������밴 2                      ***\n";
		cout<<"***      ѡ�������밴 3                      ***\n";
		cout<<"***      ���������밴 4                      ***\n";
		cout<<"***      �鲢�����밴 5                      ***\n";
		cout<<"***      ��  �����밴 6                      ***\n";
		cout<<"***      ���������밴 7                      ***\n";
		cout<<"***      �ۺ������밴 8                      ***\n";
		cout<<"***      �˳��밴     0                      ***\n";
		cout<<"************************************************\n";
}

void File(int a[],int n){		
	FILE * fp;
	fp= fopen("C:\\Users\\HH\\Desktop\\������.txt","w") ;
	for(int i=0;i<n;i++)
			fprintf(fp,"%-8d ",a[i]) ;
		if(fp!=NULL)
		fclose(fp) ; //�ر��ļ�

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
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			cout<<"������"<<n<<"��Ԫ�أ�\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];

			start = clock() ;
				InsertSort(a,n);           //��������	
			finish = clock() ;
			duration =  (double)(finish - start) / CLOCKS_PER_SEC;
			cout<<"�����Ľ��Ϊ��\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" ";   
			   cout<<"\n";
			   printf("��������ʱ�䣺%lf ��\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 2:
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			cout<<"������"<<n<<"��Ԫ�أ�\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			start = clock() ;
			BubbleSort(a,n);           //ð������
			finish = clock() ;
			duration=  (double)(finish - start) / CLOCKS_PER_SEC;
			   cout<<"�����Ľ��Ϊ��\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
		printf("��������ʱ�䣺%lf ��\n",duration) ;
		File(a,n);
		a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 3:
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			cout<<"������"<<n<<"��Ԫ�أ�\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			   SelectSort(a,n);         //ѡ������
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			     cout<<"�����Ľ��Ϊ��\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			   printf("��������ʱ�䣺%lf ��\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 4:
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			cout<<"������"<<n<<"��Ԫ�أ�\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			   QuickSort(a,0,n-1);       //��������
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			    cout<<"�����Ľ��Ϊ��\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			   printf("��������ʱ�䣺%lf ��\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 5:
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			cout<<"������"<<n<<"��Ԫ�أ�\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			   MergeSort(a,0,n-1);          //�鲢����
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			    cout<<"�����Ľ��Ϊ��\n";
			   for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			  printf("��������ʱ�䣺%lf ��\n",duration) ;
			  File(a,n);
			  a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 6:
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			cout<<"������"<<n<<"��Ԫ�أ�\n";
			   for(int i=1;i<=n;i++)
				cin>>a[i];
			   start = clock() ;
			   HeapSort(a,n);            //������
			   finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			   cout<<"�����Ľ��Ϊ��\n";
			   for(int i=1;i<=n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			 printf("��������ʱ�䣺%lf ��\n",duration) ;
			 FILE * fp;
			 fp= fopen("C:\\Users\\HH\\Desktop\\������.txt","w") ;
			 for(int i=1;i<=n;i++)
				 fprintf(fp,"%-8d ",a[i]) ;
		if(fp!=NULL)
		fclose(fp) ; //�ر��ļ�
		a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 7:
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			cout<<"������"<<n<<"��Ԫ�أ�\n";
			   for(int i=0;i<n;i++)
				cin>>a[i];
			   start = clock() ;
			radixsort(a,n);    //��������
			finish = clock() ;
			duration= (double)(finish - start) / CLOCKS_PER_SEC;
			 cout<<"�����Ľ��Ϊ��\n";
			 for(int i=0;i<n;i++)
				   cout<<a[i]<<" "; 
			   cout<<"\n";
			   printf("��������ʱ�䣺%lf ��\n",duration) ;
			   File(a,n);
			   a[MaxSize]=0;
		system("pause");
		system("cls");   
		break;

		case 8:
			cout<<"�����������Ԫ�ظ�����\n";
			cin>>n;
			srand((unsigned int)time(0));
			for(int i=0;i<n;i++){
				a[i]=rand();
				b[i]=a[i];
				arr[i+1]=a[i];
			}
						cout<<"\n";

			start = clock() ;
				InsertSort(b,n);           //��������	
			finish = clock() ;
			t[1] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("������������ʱ�䣺%lf ��\n",t[1]) ;
			for(int i=0;i<n;i++)
				b[i]=a[i];
			cout<<"\n";

			
			start = clock() ;
				BubbleSort(b,n);           //ð������	
			finish = clock() ;
			t[2] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("ð����������ʱ�䣺%lf ��\n",t[2]) ;
			for(int i=0;i<n;i++)
				b[i]=a[i];
			cout<<"\n";

			start = clock() ;
				SelectSort(b,n);           //ѡ������	
			finish = clock() ;
			t[3] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("ѡ����������ʱ�䣺%lf ��\n",t[3]) ;
			for(int i=0;i<n;i++)
				b[i]=a[i];
			cout<<"\n";

			start = clock() ;
				  QuickSort(b,0,n-1);       //��������	
			finish = clock() ;
			t[4] =  (double)(finish - start) / CLOCKS_PER_SEC;
			  for(int i=0;i<n;i++)
				b[i]=a[i];
			printf("������������ʱ�䣺%lf ��\n",t[4]) ;
			cout<<"\n";

		       start = clock() ;
			   MergeSort(b,0,n-1);          //�鲢����
			   finish = clock() ;
			t[5] =  (double)(finish - start) / CLOCKS_PER_SEC;
			  for(int i=0;i<n;i++)
				b[i]=a[i];
			printf("�鲢��������ʱ�䣺%lf ��\n",t[5]) ;
			cout<<"\n";


			start = clock() ;
				 HeapSort(arr,n);            //������
			finish = clock() ;
			t[6] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("����������ʱ�䣺%lf ��\n",t[6]) ;
			cout<<"\n";


			start = clock() ;
				 radixsort(a,n);    //��������
			finish = clock() ;
			t[7] =  (double)(finish - start) / CLOCKS_PER_SEC;
			printf("������������ʱ�䣺%lf ��\n",t[7]) ;
			   cout<<"\n";

			  // �����������
			  /* cout<<"����Ľ��Ϊ��\n";
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
			   fp2= fopen("C:\\Users\\HH\\Desktop\\�ۺ�����������.txt","w") ;
			       fprintf(fp2,"\n") ;
				   fprintf(fp2,"������������ʱ�䣺%lf ��\n",t[1]) ;
				   fprintf(fp2,"ð����������ʱ�䣺%lf ��\n",t[2]) ;
				   fprintf(fp2,"ѡ����������ʱ�䣺%lf ��\n",t[3]) ;
				   fprintf(fp2,"������������ʱ�䣺%lf ��\n",t[4]) ;
				   fprintf(fp2,"�鲢��������ʱ�䣺%lf ��\n",t[5]) ;
				   fprintf(fp2,"��    ��������ʱ�䣺%lf ��\n",t[6]) ;
				   fprintf(fp2,"������������ʱ�䣺%lf ��\n",t[7]) ;
				   fprintf(fp2,"\n") ;
				   fprintf(fp2,"������ֵ�����Ϊ��\n") ;
				   if(k==1)
					    fprintf(fp2,"��������%lf ��\n",t[1]) ;
				    else if(k==2)
					   fprintf(fp2,"ð������%lf ��\n",t[2]) ;
				    else if(k==3)
					   fprintf(fp2,"ѡ������%lf ��\n",t[3]) ;
				    else if(k==4)
					    fprintf(fp2,"��������%lf ��\n",t[4]) ;
				    else if(k==5)
					   fprintf(fp2,"�鲢����%lf ��\n",t[5]) ;
				    else if(k==6)
					    fprintf(fp2,"��    ����%lf ��\n",t[6]) ;
				    else if(k==7)
					   fprintf(fp2,"��������%lf ��\n",t[7]) ;
					 fprintf(fp2,"\n") ;
					if(k2==1)
					    fprintf(fp2,"��������%lf ��\n",t[1]) ;
				    else if(k2==2)
					   fprintf(fp2,"ð������%lf ��\n",t[2]) ;
				    else if(k2==3)
					   fprintf(fp2,"ѡ������%lf ��\n",t[3]) ;
				    else if(k2==4)
					    fprintf(fp2,"��������%lf ��\n",t[4]) ;
				    else if(k2==5)
					   fprintf(fp2,"�鲢����%lf ��\n",t[5]) ;
				    else if(k2==6)
					    fprintf(fp2,"��    ����%lf ��\n",t[6]) ;
				    else if(k2==7)
					   fprintf(fp2,"��������%lf ��\n",t[7]) ;
					 fprintf(fp2,"\n") ;
					 fprintf(fp2,"\n") ;
					fprintf(fp2,"����Ľ��Ϊ��\n") ;
					for(int i=1;i<=n;i++)
						fprintf(fp2,"%-8d ",arr[i]) ;
			   if(fp2!=NULL)
				   fclose(fp2) ; //�ر��ļ�
				}
			system("pause");
			system("cls");
			break ;

		case 0:exit(0);

		default:cout<<"û����ѡ�����Ŀ������ѡ��\n";
			system("pause");
			system("cls");
	}//switch
	}//while;
}//return��