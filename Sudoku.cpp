#include"Sudoku.h"
using namespace std;
void Sudoku::giveQuestion(){ //隨機生成一個數獨盤 
	int arr[]={
	0,0,0,0,0,0,0,0,0,
	0,0,0,8,4,0,0,0,0,
	0,0,1,0,0,0,2,0,0,
	0,0,0,0,1,0,0,9,0,
	7,0,0,0,0,2,0,0,0,
	5,6,0,0,0,0,0,8,0,
	0,0,0,0,0,0,0,0,0,
	8,4,0,0,0,0,1,0,0,
	3,0,0,6,0,0,5,0,0};
	printOut(arr);
}	
void Sudoku::printOut(int arr[]){ //印出盤 
	for(int i=0;i<sudokuSize;i++){
		cout<<arr[i]<<((i%9==8)?'\n':' '); //第9個換行或是每個空格 
	}
}
void Sudoku::readIn(){ //複製資料 
	int num,i=0;
	for(int p=0;p<sudokuSize;p++) ques[p]=0; //初始化 
	while(cin>>num){
		ques[i]=num;
		i++;
	}
}
void Sudoku::solve(){ //解題 
	possibility();
	if(ansCount==1){ //已解出
		cout<<"1"<<endl; 
		printOut(ques);
		return;
	}
	int a=violence();
	cout<<a<<endl;
	if(a==1) printOut(tempAns);
} 
bool Sudoku::checkNoRepeat(int p){ //檢查位置p的數字有無重複 
	for(int i=p/9,j=0;j<9;j++){ //檢查列				
		int location=9*i+j;
		int num=ques[location];
		if(location==p||num==0) continue; //跳過原數和空格 
		if(ques[p]==num) return false;
	}
	for(int i=0,j=p%9;i<9;i++){ //檢查行 
		int location=9*i+j;
		int num=ques[location];
		if(location==p||num==0) continue;
		if(ques[p]==num) return false;
	}
	for(int k=0,i=(p/9)/3,j=(p%9)/3;k<9;k++){ //i,j分成三大列,三大行,k計數  
		int location=27*i+3*j+9*(k/3)+(k%3);
		int num=ques[location]; //前兩個決定宮的第一個數,後兩個決定宮裡的行列 
		if(location==p||num==0) continue;
		if(ques[p]==num) return false;
	}
	return true;
}
bool Sudoku::isCorrect(){ //檢查符不符合數獨規則 
	for(int p=0;p<sudokuSize;p++){
		if(checkNoRepeat(p)==false) return false;
	}
	return true;
}
void Sudoku::possibility(){ //候選法 
	ansCount=0;	 
	for(int p=0;p<sudokuSize;p++){ //初始化 
		for(int j=0;j<9;j++){
			possible[p][j]=true;
		}
		remainNum[p]=0;
	}
	int done; //紀錄填好幾格 
	do{
		done=0; //重新計算 
		for(int p=0;p<sudokuSize;p++){
			int num;
			if(ques[p]!=0) done++; //已有數字 
			else{ //有空位 
				//篩選同列(i固定) 
				for(int i=p/9,j=0;j<9;j++){
					num=ques[9*i+j];
					if(num!=0) possible[p][num-1]=false; //若該列已有數字則剔除 
				}
				//篩選同行(j固定) 
				for(int i=0,j=p%9;i<9;i++){
					num=ques[9*i+j];
					if(num!=0) possible[p][num-1]=false;
				}	
				//篩選同宮
				for(int k=0,i=(p/9)/3,j=(p%9)/3;k<9;k++){ //i,j分成三大列,三大行,k計數 
					num=ques[27*i+3*j+9*(k/3)+(k%3)]; //前兩個決定宮的第一個數,後兩個決定宮裡的行列 
					if(num!=0) possible[p][num-1]=false;
				}
				//計算剩餘數字個數 
				int count=0;
				for(int k=0;k<9;k++){
					if(possible[p][k]==true){
						count++;
						num=k+1; //保留可能數字
					}
				}
				remainNum[p]=count;
				if(remainNum[p]==1){ //只有唯一可能則填入
					ques[p]=num;
					done++;
				}	
			}
		}
		int minRemain=9; //計算整個盤空格的最少剩餘
		int space=0; //計算剩餘空格 
		for(int p=0;p<sudokuSize;p++){
			if(ques[p]!=0) continue; //已有數字 
			else space++;
			if(remainNum[p]<minRemain) minRemain=remainNum[p];
		}
		if(space>1&&minRemain>1) break;	//整盤沒有唯一可能也不剩最後一空格則跳出
	}while(done<sudokuSize);
	if(done==sudokuSize) ansCount=1;
}
int Sudoku::violence(){ //暴力法 
	if(isCorrect()==false) return 0;
	if(ansCount==1) return 1; //候選已解完 
	else ansCount=0;
	
	int space=0; //計算有幾個空格
	for(int p=0;p<sudokuSize;p++){
		if(ques[p]==0) space++;
	}
	int pos_0[space]; //紀錄空格位置
	for(int p=0,i=0;p<sudokuSize;p++){
		if(ques[p]==0){
			pos_0[i]=p; 
			i++;			
		}
	} 		
	int ans,i=0,last_i=space-1; //從第一個空格開始0~space-1
	do{
		int filled; //確保有更動此空格				
		int p; //紀錄目前所填空格位置				
		do{
			p=pos_0[i];
			filled=0;
			for(int k=0;k<9;k++){ //嘗試該格所有可能 
				if(possible[p][k]==true){
					ans=k+1;
					ques[p]=ans; //先填入 
					if(checkNoRepeat(p)==true){ //再檢查符不符合 
						filled++;
						break;
					}
					ques[p]=0; //不符合則設回0
				}
			}
			if(filled!=0&&i!=last_i) i++; //有填入則往下一空格,不能跑出最後一格 
			if(ques[pos_0[last_i]]!=0&&i==last_i&&isCorrect()){ //跑到最後一空格則確認是否為1解						
				ansCount++;
				copyAns();
				filled=0; //重新設回未填入狀態 
				ques[pos_0[last_i]]=0; //設回0使能夠回去試 
				if(ansCount>1) return 2; 
			}
		}while(filled!=0);		
		
		int changed; //確保有更動上一空格 		
		if(filled==0){ //若該空格沒有更動則回上一空格 
			do{
				i--;
				p=pos_0[i];
				changed=0;
				for(int k=0;k<9;k++){ //檢查剩餘可能 
					if(possible[p][k]==true){
						ans=k+1;
						if(ans>ques[p]){ //若有則先填入
							int temp=ques[p];
							ques[p]=ans;
							if(checkNoRepeat(p)==true){ //再檢查符不符合 
								changed++;
								i++; //先移至下一空格 
								break;
							}
							ques[p]=temp; //不符合則設回原數 
						}
					}
				}
				if(changed==0) ques[p]=0; //達最後可能,重新設為0 
			}while(changed==0&&i!=0); //已達最後可能則再往上,若跑回第一空格且未更動則跳出無解 
		}
		if(ansCount==0&&changed==0&&i==0) return 0; //無解 
		else if(ansCount==1&&changed==0&&i==0) return 1; //只有唯一解 
	}while(i>=0&&i<=last_i); //0~space-1為i範圍
}
void Sudoku::copyAns(){
	for(int p=0;p<sudokuSize;p++){
		tempAns[p]=ques[p];
	}
}
void Sudoku::changeNum(int a,int b){
	for(int i=0;i<sudokuSize;i++){
		if(ques[i]==a) ques[i]=b; //擇一執行 
		else if(ques[i]==b) ques[i]=a;
	}
}
void Sudoku::changeRow(int a,int b){
	a=27*a; //三列中第一個元素位置 
	b=27*b;
	for(int i=0;i<27;i++){ //i計數 
		int temp=ques[a+i];
		ques[a+i]=ques[b+i];
		ques[b+i]=temp;
	}
}
void Sudoku::changeCol(int a,int b){
	a=3*a; //三行中第一個元素位置 
	b=3*b;
	for(int j=0;j<3;j++,a++,b++){ //第a+j,b+j行 
		for(int i=0;i<9;i++){ //第i列 
			int temp=ques[9*i+a];
			ques[9*i+a]=ques[9*i+b];
			ques[9*i+b]=temp;
		}
	}
}
void Sudoku::rotate(int n){
	int tempBoard[sudokuSize];
	for(n=n%4;n>0;n--){ //轉n次 
		for(int i=0;i<9;i++){ //第i列(變第8-i行) 
			for(int j=0;j<9;j++){ //第j行(變第j列) 
				tempBoard[9*j+(8-i)]=ques[9*i+j];
			}
		}
		for(int k=0;k<sudokuSize;k++){ //搬移 
			ques[k]=tempBoard[k];
		}
	}
}
void Sudoku::flip(int n){
	if(n==0){ //上下顛倒
		for(int i=0;i<4;i++){ //上面i列 
			for(int j=0;j<9;j++){
				int temp=ques[9*i+j];
				ques[9*i+j]=ques[9*(8-i)+j];
				ques[9*(8-i)+j]=temp;
			}
		}
	}
	else if(n==1){ //左右顛倒 
		for(int j=0;j<4;j++){ //左邊j行 
			for(int i=0;i<9;i++){
				int temp=ques[9*i+j];
				ques[9*i+j]=ques[9*i+(8-j)];
				ques[9*i+(8-j)]=temp;
			}
		}
	}
}	
void Sudoku::transform(){ //轉換盤 
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	printOut(ques);
}
