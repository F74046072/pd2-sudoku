#include"Sudoku.h"
using namespace std;
void Sudoku::giveQuestion(){ //�H���ͦ��@�ӼƿW�L 
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
void Sudoku::printOut(int arr[]){ //�L�X�L 
	for(int i=0;i<sudokuSize;i++){
		cout<<arr[i]<<((i%9==8)?'\n':' '); //��9�Ӵ���άO�C�ӪŮ� 
	}
}
void Sudoku::readIn(){ //�ƻs��� 
	int num,i=0;
	for(int p=0;p<sudokuSize;p++) ques[p]=0; //��l�� 
	while(cin>>num){
		ques[i]=num;
		i++;
	}
}
void Sudoku::solve(){ //���D 
	possibility();
	if(ansCount==1){ //�w�ѥX
		cout<<"1"<<endl; 
		printOut(ques);
		return;
	}
	int a=violence();
	cout<<a<<endl;
	if(a==1) printOut(tempAns);
} 
bool Sudoku::checkNoRepeat(int p){ //�ˬd��mp���Ʀr���L���� 
	for(int i=p/9,j=0;j<9;j++){ //�ˬd�C				
		int location=9*i+j;
		int num=ques[location];
		if(location==p||num==0) continue; //���L��ƩM�Ů� 
		if(ques[p]==num) return false;
	}
	for(int i=0,j=p%9;i<9;i++){ //�ˬd�� 
		int location=9*i+j;
		int num=ques[location];
		if(location==p||num==0) continue;
		if(ques[p]==num) return false;
	}
	for(int k=0,i=(p/9)/3,j=(p%9)/3;k<9;k++){ //i,j�����T�j�C,�T�j��,k�p��  
		int location=27*i+3*j+9*(k/3)+(k%3);
		int num=ques[location]; //�e��ӨM�w�c���Ĥ@�Ӽ�,���ӨM�w�c�̪���C 
		if(location==p||num==0) continue;
		if(ques[p]==num) return false;
	}
	return true;
}
bool Sudoku::isCorrect(){ //�ˬd�Ť��ŦX�ƿW�W�h 
	for(int p=0;p<sudokuSize;p++){
		if(checkNoRepeat(p)==false) return false;
	}
	return true;
}
void Sudoku::possibility(){ //�Կ�k 
	ansCount=0;	 
	for(int p=0;p<sudokuSize;p++){ //��l�� 
		for(int j=0;j<9;j++){
			possible[p][j]=true;
		}
		remainNum[p]=0;
	}
	int done; //������n�X�� 
	do{
		done=0; //���s�p�� 
		for(int p=0;p<sudokuSize;p++){
			int num;
			if(ques[p]!=0) done++; //�w���Ʀr 
			else{ //���Ŧ� 
				//�z��P�C(i�T�w) 
				for(int i=p/9,j=0;j<9;j++){
					num=ques[9*i+j];
					if(num!=0) possible[p][num-1]=false; //�Y�ӦC�w���Ʀr�h�簣 
				}
				//�z��P��(j�T�w) 
				for(int i=0,j=p%9;i<9;i++){
					num=ques[9*i+j];
					if(num!=0) possible[p][num-1]=false;
				}	
				//�z��P�c
				for(int k=0,i=(p/9)/3,j=(p%9)/3;k<9;k++){ //i,j�����T�j�C,�T�j��,k�p�� 
					num=ques[27*i+3*j+9*(k/3)+(k%3)]; //�e��ӨM�w�c���Ĥ@�Ӽ�,���ӨM�w�c�̪���C 
					if(num!=0) possible[p][num-1]=false;
				}
				//�p��Ѿl�Ʀr�Ӽ� 
				int count=0;
				for(int k=0;k<9;k++){
					if(possible[p][k]==true){
						count++;
						num=k+1; //�O�d�i��Ʀr
					}
				}
				remainNum[p]=count;
				if(remainNum[p]==1){ //�u���ߤ@�i��h��J
					ques[p]=num;
					done++;
				}	
			}
		}
		int minRemain=9; //�p���ӽL�Ů檺�ֳ̤Ѿl
		int space=0; //�p��Ѿl�Ů� 
		for(int p=0;p<sudokuSize;p++){
			if(ques[p]!=0) continue; //�w���Ʀr 
			else space++;
			if(remainNum[p]<minRemain) minRemain=remainNum[p];
		}
		if(space>1&&minRemain>1) break;	//��L�S���ߤ@�i��]���ѳ̫�@�Ů�h���X
	}while(done<sudokuSize);
	if(done==sudokuSize) ansCount=1;
}
int Sudoku::violence(){ //�ɤO�k 
	if(isCorrect()==false) return 0;
	if(ansCount==1) return 1; //�Կ�w�ѧ� 
	else ansCount=0;
	
	int space=0; //�p�⦳�X�ӪŮ�
	for(int p=0;p<sudokuSize;p++){
		if(ques[p]==0) space++;
	}
	int pos_0[space]; //�����Ů��m
	for(int p=0,i=0;p<sudokuSize;p++){
		if(ques[p]==0){
			pos_0[i]=p; 
			i++;			
		}
	} 		
	int ans,i=0,last_i=space-1; //�q�Ĥ@�ӪŮ�}�l0~space-1
	do{
		int filled; //�T�O����ʦ��Ů�				
		int p; //�����ثe�Ҷ�Ů��m				
		do{
			p=pos_0[i];
			filled=0;
			for(int k=0;k<9;k++){ //���ոӮ�Ҧ��i�� 
				if(possible[p][k]==true){
					ans=k+1;
					ques[p]=ans; //����J 
					if(checkNoRepeat(p)==true){ //�A�ˬd�Ť��ŦX 
						filled++;
						break;
					}
					ques[p]=0; //���ŦX�h�]�^0
				}
			}
			if(filled!=0&&i!=last_i) i++; //����J�h���U�@�Ů�,����]�X�̫�@�� 
			if(ques[pos_0[last_i]]!=0&&i==last_i&&isCorrect()){ //�]��̫�@�Ů�h�T�{�O�_��1��						
				ansCount++;
				copyAns();
				filled=0; //���s�]�^����J���A 
				ques[pos_0[last_i]]=0; //�]�^0�ϯ���^�h�� 
				if(ansCount>1) return 2; 
			}
		}while(filled!=0);		
		
		int changed; //�T�O����ʤW�@�Ů� 		
		if(filled==0){ //�Y�ӪŮ�S����ʫh�^�W�@�Ů� 
			do{
				i--;
				p=pos_0[i];
				changed=0;
				for(int k=0;k<9;k++){ //�ˬd�Ѿl�i�� 
					if(possible[p][k]==true){
						ans=k+1;
						if(ans>ques[p]){ //�Y���h����J
							int temp=ques[p];
							ques[p]=ans;
							if(checkNoRepeat(p)==true){ //�A�ˬd�Ť��ŦX 
								changed++;
								i++; //�����ܤU�@�Ů� 
								break;
							}
							ques[p]=temp; //���ŦX�h�]�^��� 
						}
					}
				}
				if(changed==0) ques[p]=0; //�F�̫�i��,���s�]��0 
			}while(changed==0&&i!=0); //�w�F�̫�i��h�A���W,�Y�]�^�Ĥ@�Ů�B����ʫh���X�L�� 
		}
		if(ansCount==0&&changed==0&&i==0) return 0; //�L�� 
		else if(ansCount==1&&changed==0&&i==0) return 1; //�u���ߤ@�� 
	}while(i>=0&&i<=last_i); //0~space-1��i�d��
}
void Sudoku::copyAns(){
	for(int p=0;p<sudokuSize;p++){
		tempAns[p]=ques[p];
	}
}
void Sudoku::changeNum(int a,int b){
	for(int i=0;i<sudokuSize;i++){
		if(ques[i]==a) ques[i]=b; //�ܤ@���� 
		else if(ques[i]==b) ques[i]=a;
	}
}
void Sudoku::changeRow(int a,int b){
	a=27*a; //�T�C���Ĥ@�Ӥ�����m 
	b=27*b;
	for(int i=0;i<27;i++){ //i�p�� 
		int temp=ques[a+i];
		ques[a+i]=ques[b+i];
		ques[b+i]=temp;
	}
}
void Sudoku::changeCol(int a,int b){
	a=3*a; //�T�椤�Ĥ@�Ӥ�����m 
	b=3*b;
	for(int j=0;j<3;j++,a++,b++){ //��a+j,b+j�� 
		for(int i=0;i<9;i++){ //��i�C 
			int temp=ques[9*i+a];
			ques[9*i+a]=ques[9*i+b];
			ques[9*i+b]=temp;
		}
	}
}
void Sudoku::rotate(int n){
	int tempBoard[sudokuSize];
	for(n=n%4;n>0;n--){ //��n�� 
		for(int i=0;i<9;i++){ //��i�C(�ܲ�8-i��) 
			for(int j=0;j<9;j++){ //��j��(�ܲ�j�C) 
				tempBoard[9*j+(8-i)]=ques[9*i+j];
			}
		}
		for(int k=0;k<sudokuSize;k++){ //�h�� 
			ques[k]=tempBoard[k];
		}
	}
}
void Sudoku::flip(int n){
	if(n==0){ //�W�U�A��
		for(int i=0;i<4;i++){ //�W��i�C 
			for(int j=0;j<9;j++){
				int temp=ques[9*i+j];
				ques[9*i+j]=ques[9*(8-i)+j];
				ques[9*(8-i)+j]=temp;
			}
		}
	}
	else if(n==1){ //���k�A�� 
		for(int j=0;j<4;j++){ //����j�� 
			for(int i=0;i<9;i++){
				int temp=ques[9*i+j];
				ques[9*i+j]=ques[9*i+(8-j)];
				ques[9*i+(8-j)]=temp;
			}
		}
	}
}	
void Sudoku::transform(){ //�ഫ�L 
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	printOut(ques);
}
