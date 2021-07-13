#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <random>
#include <stdlib.h>  
#include <typeinfo>

using namespace std;

random_device device;
mt19937 generator(device());
uniform_int_distribution<int> dis(0,100000);
uniform_real_distribution<float> disf(0,100);
uniform_real_distribution<double> disd(0,100);

int a=0;
int b=0;

const string CHARACTERS="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int SIZE=63;

template<typename T>
class Sorting{
    private:

        int Partition(T t[],int start,int end,string comp){
            // cerr<<"SET"<<endl
            b++;
            T pivot=t[end];
            int i=start;
            if(comp.compare("<=")==0){
                for(int j=start;j<end;j++){
                    // cerr<<"COMP:"<<endl
                    a++;
                    if(t[j]<=pivot){
                        swap(&t[i],&t[j]);
                        i++;
                    
                    }
                }
            }
            else if(comp.compare(">=")==0){
                for(int j=start;j<end;j++){
                    // cerr<<"COMP:"<<endl
                    a++;
                    if(t[j]>=pivot){
                        swap(&t[i],&t[j]);
                        i++;
                    
                    }
                }
            }
            swap(&t[i],&t[end]);
            return i; 
        }
        
        int Partition2(T t[],int start,int end,string comp,int* secondPart){
            int s=0;
            int l=0;
            int i=start+1;
            int j=i;
            if(comp.compare("<=")==0){
                a++;
                if(t[start]>t[end]){
                    swap(&t[start],&t[end]);
                }
                T pivotS=t[start];
                T pivotL=t[end];
                b+=2;
                while(j<=*secondPart){
                    if(l<=s){
                        a++;
                        if(t[j]<pivotS){
                            swap(&t[j],&t[i]);
                            i++;
                            s++;
                            j++;
                        }
                        else if(t[j]>=pivotL){
                            a++;
                            while(*secondPart>j && t[*secondPart]>=pivotL){
                                (*secondPart)--;
                                l++;
                                a++;
                            }
                            swap(&t[*secondPart],&t[j]);
                            (*secondPart)--;
                            l++;
                            a++;
                        }
                        else{
                            j++;
                            a++;
                        }
                    }
                    else{
                        a++;
                        if(t[j]>=pivotL){
                            a++;
                            while(*secondPart>j && t[*secondPart]>=pivotL){
                                (*secondPart)--;
                                l++;
                                a++;
                            }
                            swap(&t[*secondPart],&t[j]);
                            (*secondPart)--;
                            l++;
                        }
                        else if(t[j]<pivotS){
                            swap(&t[j],&t[i]);
                            i++;
                            s++;
                            j++;
                            a++;
                        }
                        else{
                            j++;
                            a++;
                        }
                    }
                }
            }
            else if(comp.compare(">=")==0){
                a++;
                if(t[start]<t[end]){
                    swap(&t[start],&t[end]);
                }
                T pivotL=t[start];
                T pivotS=t[end];
                b+=2;
                while(j<=*secondPart){
                    if(l<=s){
                        a++;
                        if(t[j]>pivotL){
                            swap(&t[j],&t[i]);
                            i++;
                            s++;
                            j++;
                        }
                        else if(t[j]<=pivotS){
                            a++;
                            while(*secondPart>j && t[*secondPart]<=pivotS){
                                (*secondPart)--;
                                l++;
                                a++;
                            }
                            swap(&t[*secondPart],&t[j]);
                            (*secondPart)--;
                            l++;
                            a++;
                        }
                        else{
                            j++;
                            a++;
                        }
                    }
                    else{
                        a++;
                        if(t[j]<=pivotS){
                            a++;
                            while(*secondPart>j && t[*secondPart]<=pivotS){
                                (*secondPart)--;
                                l++;
                                a++;
                            }
                            swap(&t[*secondPart],&t[j]);
                            (*secondPart)--;
                            l++;
                        }
                        else if(t[j]>pivotL){
                            swap(&t[j],&t[i]);
                            i++;
                            s++;
                            j++;
                            a++;
                        }
                        else{
                            j++;
                            a++;
                        }
                    }
                }
            }
            swap(&t[start],&t[i-1]);
            swap(&t[end],&t[(*secondPart)+1]);
            (*secondPart)++;
            return i-1;
        }
        
    public:

        void InsertionSort(T t[],int start,int end,string comp){
            if(comp.compare("<=")==0){
                for(int i=start+1;i<=end;i++){
                    int j=i-1;
                    // cerr<<"SET"<<endl
                // cerr<<"SET: key to t["<<i<<"]("<<t[i]<<")\n";
                    b++;
                    T key=t[i];
                    // cerr<<"COMP"<<endl
                //  cerr<<"COMP: key("<<key<<") with t["<<j<<"]("<<t[j]<<")\n";
                    a++;
                    while(j>=0 && key<t[j]){
                        // cerr<<"SET"<<endl
                    //  cerr<<"SET: t["<<j+1<<"]("<<t[j+1]<<") to t["<<j<<"]("<<t[j]<<")\n";
                        b++;
                        t[j+1]=t[j];
                        j--;
                        if(j>=0){
                            // cerr<<"COMP"<<endl
                        //  cerr<<"COMP: key("<<key<<") with t["<<j<<"]("<<t[i]<<")\n";
                            a++;
                        }
                    }
                    // cerr<<"SET"<<endl
                // cerr<<"SET: t["<<j+1<<"] to key("<<key<<")\n";
                    b++;
                    t[j+1]=key;
                }
            }
            else if(comp.compare(">=")==0){
                for(int i=start+1;i<=end;i++){
                    int j=i-1;
                    // cerr<<"SET"<<endl
                    //cerr<<"SET: key to t["<<i<<"]("<<t[i]<<")\n";
                    b++;
                    T key=t[i];
                    // cerr<<"COMP"<<endl
                //  cerr<<"COMP: key("<<key<<") with t["<<j<<"]("<<t[j]<<")\n";
                    a++;
                    while(j>=0 && key>t[j]){
                        // cerr<<"SET"<<endl
                    //   cerr<<"SET: t["<<j+1<<"]("<<t[j+1]<<") to t["<<j<<"]("<<t[j]<<")\n";
                        b++;
                        t[j+1]=t[j];
                        j--;
                        if(j>=0){
                            // cerr<<"COMP"<<endl
                        //   cerr<<"COMP: key("<<key<<") with t["<<j<<"]("<<t[i]<<")\n";
                            a++;
                        }
                    }
                    // cerr<<"SET"<<endl
                // cerr<<"SET: t["<<j+1<<"] to key("<<key<<")\n";
                    b++;
                    t[j+1]=key;
                }
            }
        }

        void Merge(T t[],int start,int center,int end,string comp){
            int n1=center-start+1;
            int n2=end-center;
            T l[n1];
            T r[n2];
            for(int i=0;i<n1;i++){
                // cerr<<"SET"<<endl;
                b++;
                l[i]=t[start+i];
            }
            for(int i=0;i<n2;i++){
                // cerr<<"SET"<<endl;
                b++;
                r[i]=t[center+i+1];
            }
            int i=0;
            int j=0;
            int k=start;
            if(comp.compare("<=")==0){
                while(i<n1 && j<n2){
                    // cerr<<"COMP"<<endl
                // cerr<<"COMP: l["<<i<<"]("<<l[i]<<") with r["<<j<<"]("<<r[j]<<")\n";
                    a++;
                    if(l[i]<r[j]){
                        // cerr<<"SET"<<endl
                    // cerr<<"SET: t["<<k<<"] to l["<<i<<"]("<<l[i]<<")\n";
                        b++;
                        t[k]=l[i];
                        i++;
                    }
                    else{
                        // cerr<<"SET"<<endl
                    // cerr<<"SET: t["<<k<<"] to r["<<j<<"]("<<r[j]<<")\n";
                        b++;
                        t[k]=r[j];
                        j++;
                    }
                    k++;
                }
            }
            else if(comp.compare(">=")==0){
                while(i<n1 && j<n2){
                    // cerr<<"COMP"<<endl
                // cerr<<"COMP: l["<<i<<"]("<<l[i]<<") with r["<<j<<"]("<<r[j]<<")\n";
                    a++;
                    if(l[i]>r[j]){
                        // cerr<<"SET"<<endl
                    //  cerr<<"SET: t["<<k<<"] to l["<<i<<"]("<<l[i]<<")\n";
                        b++;
                        t[k]=l[i];
                        i++;
                    }
                    else{
                        // cerr<<"SET"<<endl
                    //  cerr<<"SET: t["<<k<<"] to r["<<j<<"]("<<r[j]<<")\n";
                        b++;
                        t[k]=r[j];
                        j++;
                    }
                    k++;
                }
            }
            while(i<n1){
                // cerr<<"SET"<<endl
            // cerr<<"SET: t["<<k<<"] to l["<<i<<"]("<<l[i]<<")\n";
                b++;
                t[k]=l[i];
                i++;
                k++;
            }     
            while(j<n2){
                // cerr<<"SET"<<endl
            // cerr<<"SET: t["<<k<<"] to r["<<j<<"]("<<r[j]<<")\n";
                b++;
                t[k]=r[j];
                j++;
                k++;
            }
        }

        void MergeSort(T t[],int start,int end,string comp){
            if(end<=start){
                return;
            }
            int center=(start+end)/2;
            MergeSort(t,start,center,comp);
            MergeSort(t,center+1,end,comp);
            Merge(t,start,center,end,comp);
        }

        void swap(T *c,T *d){
            // cerr<<"SET"<<endl
            T tmp=*c;
            // cerr<<"SET"<<endl
            *c=*d;
            // cerr<<"SET"<<endl
            *d=tmp;
            b+=3;

        }

        void QuickSort(T t[],int start,int end,string comp){
            if(end<=start){
                return;
            }
            int part=Partition(t,start,end,comp);
            QuickSort(t,start,part-1,comp);
            QuickSort(t,part+1,end,comp);
        }

        /*void QuickSort(T t[],int start,int end,string comp){
            if(end<=start){
                return;
            }
            // cerr<<"SET"<<endl
        // cerr<<"SET: pivot to t["<<(start+end)/2<<"]("<<t[(start+end)/2]<<")\n";
            b++;
            T pivot=t[(start+end)/2];
            int i=start;
            int j=end;
            if(comp.compare("<=")==0){
                while(i<j){
                    // cerr<<"COMP"<<endl
                //  cerr<<"COMP: t["<<i<<"]("<<t[i]<<") with pivot("<<pivot<<")\n";
                    a++;
                    while(t[i]<pivot){
                        i++;
                        // cerr<<"COMP"<<endl
                    //   cerr<<"COMP: t["<<i<<"]("<<t[i]<<") with pivot("<<pivot<<")\n";
                        a++;
                    }
                    // cerr<<"COMP"<<endl
                //  cerr<<"COMP: t["<<j<<"]("<<t[j]<<") with pivot("<<pivot<<")\n";
                    a++;
                    while(t[j]>pivot){
                        j--;
                        // cerr<<"COMP"<<endl
                //     cerr<<"COMP: t["<<j<<"]("<<t[j]<<") with pivot("<<pivot<<")\n";
                        a++;
                    }
                    if(i<=j){
                        if(i<j){
                            // cerr<<"SET"<<endl
                        //    cerr<<"SET: tmp to t["<<i<<"]("<<t[i]<<")\n";
                            b++;
                            T tmp=t[i];
                            // cerr<<"SET"<<endl
                        //   cerr<<"SET t["<<i<<"]("<<t[i]<<") to t["<<j<<"]("<<t[j]<<")\n";
                            b++;
                            t[i]=t[j];
                            // cerr<<"SET"<<endl
                        //   cerr<<"SET t["<<j<<"]("<<t[j]<<") to tmp("<<tmp<<")\n";
                            b++;
                            t[j]=tmp;
                        }
                        i++;
                        j--;
                    }
                }
            }
            else if(comp.compare(">=")==0){
                while(i<j){
                    // cerr<<"COMP"<<endl
                //  cerr<<"COMP: t["<<i<<"]("<<t[i]<<") with pivot("<<pivot<<")\n";
                    a++;
                    while(t[i]>pivot){
                        i++;
                        // cerr<<"COMP"<<endl
                //     cerr<<"COMP: t["<<i<<"]("<<t[i]<<") with pivot("<<pivot<<")\n";
                        a++;
                    }
                    while(t[j]<pivot){
                        j--;
                    //  cerr<<"COMP: t["<<j<<"]("<<t[j]<<") with pivot("<<pivot<<")\n";
                        a++;
                    }
                    if(i<=j){
                        if(i<j){
                            // cerr<<"SET"<<endl
                        //cerr<<"SET: tmp to t["<<i<<"]("<<t[i]<<")\n";
                            b++;
                            T tmp=t[i];
                            // cerr<<"SET"<<endl
                        //   cerr<<"SET t["<<i<<"]("<<t[i]<<") to t["<<j<<"]("<<t[j]<<")\n";
                            b++;
                            t[i]=t[j];
                            // cerr<<"SET"<<endl
                        //    cerr<<"SET t["<<j<<"]("<<t[j]<<") to tmp("<<tmp<<")\n";
                            b++;
                            t[j]=tmp;
                        }
                        i++;
                        j--;
                    }
                }
            }
            QuickSort(t,start,j,comp);
            QuickSort(t,i,end,comp);
        }*/

        void DualPivotQuickSort(T t[],int start,int end,string comp){
            if(end<=start){
                return;
            }
            int secondPart=end-1;
            int firstPart=Partition2(t,start,end,comp,&secondPart);
            DualPivotQuickSort(t,start,firstPart-1,comp);
            DualPivotQuickSort(t,firstPart+1,secondPart-1,comp);
            DualPivotQuickSort(t,secondPart+1,end,comp);
        }

        void HybridSort(T t[],int start,int end,string comp){
            if(end-start+1<=32){
                InsertionSort(t,start,end,comp);
                return;
            }
                int part=Partition(t,start,end,comp);
                HybridSort(t,start,part-1,comp);
                HybridSort(t,part+1,end,comp);
        }
};

void test1(int t[],int n){
    for(int i=0;i<n;i++){
        t[i]=i;
    }
}

void test2(int t[],int n){
   for(int i=0;i<n;i++){
       t[i]=dis(generator);
   }
}

void randomFloat(float t[],int n){
    for(int i=0;i<n;i++){
        t[i]=disf(generator);
    }
}

void randomDouble(double t[],int n){
    for(int i=0;i<n;i++){
        t[i]=disd(generator);
    }
}

void randomChar(char t[],int n){
    for(int i=0;i<n;i++){
        t[i]=CHARACTERS[dis(generator)%SIZE];
    }
}

void randomString(string t[],int n,int s){
    for(int i=0;i<n;i++){
        string word="";
        for(int j=0;j<s;j++){
            word+=CHARACTERS[dis(generator)%SIZE];
    }
        t[i]=word;
    }
}

template <class T>
int go1(T t[],int n,Sorting<T> sort,string type,string comp,int option){
    if(option==1){
        cout<<"Elements: \n";
        for(int i=0;i<n;i++){
            cin>>t[i];
        }
    }
    clock_t begin;
    clock_t end;
    if(type.compare("insert")==0){
        cout<<"Insertion sort\n";
        begin=clock();
        sort.InsertionSort(t,0,n-1,comp);
        end=clock();         
    }
    else if(type.compare("merge")==0){
        cout<<"Merge sort\n";
        begin=clock();
        sort.MergeSort(t,0,n-1,comp);
        end=clock();      
    }
    else if(type.compare("quick")==0){
        cout<<"Quick sort\n";
        begin=clock();
        sort.QuickSort(t,0,n-1,comp);
        end=clock();       
    }
    else if(type.compare("quick2")==0){
        cout<<"Dual pivot quick sort\n";
        begin=clock();
        sort.DualPivotQuickSort(t,0,n-1,comp);
        end=clock();       
    }
    else if(type.compare("hybrid")==0){
        cout<<"Quick sort\n";
        T cpy[n];
        for(int i=0;i<n;i++){
            cpy[i]=t[i];
        }
        begin=clock();
        sort.HybridSort(cpy,0,n-1,comp);
        end=clock();  
        cerr<<"COMP: "<<a<<endl;
        cerr<<"SET: "<<b<<endl;
        cerr<<"Time: "<<(end-begin)*1000/(double)CLOCKS_PER_SEC<< "ms\n";   
        a=0;
        b=0;
        cout<<"Hybrid sort\n";
        begin=clock();
        sort.HybridSort(t,0,n-1,comp);
        end=clock();       
    }
    else{
        cout<<"Invalid sort type\n";
        return 1;
    }
    cerr<<"COMP: "<<a<<endl;
    cerr<<"SET: "<<b<<endl;
    cerr<<"Time: "<<(end-begin)*1000/(double)CLOCKS_PER_SEC<< "ms\n";  
    cout<<"Sorted "<<n<<" elements:\n";    
    for(int i=0;i<n;i++){
        cout<<t[i]<<endl;
    }
    return 0;
}

void go2(int k,string filename){
    Sorting<int> sort;
    clock_t begin;
    clock_t end;
    ofstream file;
    file.open(filename+": "+to_string(k));
    file<<"Alg;n;k;comp;set;time(ms)\n";
    for(int i=100;i<=10000;i+=100){
        for(int s=1;s<=k;s++){
            int t[i];
            int cpy[i];
            test2(t,i);
            for(int j=0;j<i;j++){
                cpy[j]=t[j];
            }
            a=0;
            b=0;
            begin=clock();
            sort.InsertionSort(cpy,0,i-1,"<=");
            end=clock();
            file<<"Insertion;"<<i<<";"<<s<<";"<<a<<";"<<b<<";"<<(end-begin)*1000/(double)CLOCKS_PER_SEC<<endl;
            for(int j=0;j<i;j++){
                cpy[j]=t[j];;
            }
            a=0;
            b=0;
            begin=clock();
            sort.MergeSort(cpy,0,i-1,"<=");
            end=clock();
            file<<"Merge;"<<i<<";"<<s<<";"<<a<<";"<<b<<";"<<(end-begin)*1000/(double)CLOCKS_PER_SEC<<endl;
            for(int j=0;j<i;j++){
                cpy[j]=t[j];
            }
            a=0;
            b=0;
            begin=clock();
            sort.QuickSort(cpy,0,i-1,"<=");
            end=clock();
            file<<"Quick;"<<i<<";"<<s<<";"<<a<<";"<<b<<";"<<(end-begin)*1000/(double)CLOCKS_PER_SEC<<endl;
        }
    }
    file.close();
}

int main(int argc,char* argv[]){
    int n;
    int k;
    string type;
    string comp;
    string filename;
    string data;
    bool extra=false;
    if(argc!=5 && argc!=4){
        cout<<"Incorrect number or arguments\n";
        return 1; 
    }
    for(int i=1;i<argc;i=i+2){
        if(strcmp(argv[i],"--type")==0){
            type=argv[i+1];
        }
        else if(strcmp(argv[i],"--comp")==0){
            comp=argv[i+1];
        }
        else if(strcmp(argv[i],"--stat")==0){
            extra=true;
            filename=argv[i+1];
            try{
                k=stoi(argv[i+2]);
            }
            catch(invalid_argument ex){
                cout<<"Invalid argument\n";
                return 1;
            }
        }
    } 
    if(!extra){
        if(comp.compare("<=")!=0 && comp.compare(">=")!=0){
            cout<<"Invalid sort comparing\n";
            return 1;
        }
        cout<<"Size: \n";
        cin>>n;
        if(n<0){
            cout<<"Invalid array size\n";
            return 1;
        }
        cout<<"Data type: \n";
        cin>>data;
        if(data.compare("int")==0){
            int t[n];
            //test1(t,n);
            test2(t,n);
            Sorting<int> sort;
            go1(t,n,sort,type,comp,0);
        }
        else if(data.compare("float")==0){
            float t[n];
            randomFloat(t,n);
            Sorting<float> sort;
            go1(t,n,sort,type,comp,0);
        }
        else if(data.compare("double")==0){
            double t[n];
            randomDouble(t,n);
            Sorting<double> sort;
            go1(t,n,sort,type,comp,0);
        }
        else if(data.compare("char")==0){
            char t[n];
            randomChar(t,n);
            Sorting<char> sort;
            go1(t,n,sort,type,comp,0);
        }
        else if(data.compare("string")==0){
            string t[n];
            randomString(t,n,8);
            Sorting<string> sort;
            go1(t,n,sort,type,comp,0);
        }
        else{
            cout<<"Unknown data type\n";
            return 1;
        }
    }
    else{
        go2(k,filename);
    }
    
    return 0;
}