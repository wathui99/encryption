#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>
using namespace std;
int khoi_tao_gia_tri (int *list, int soLuong);
int swap (int a, int b);
int arranger (int *list, int n_phanTu);
int make_list_rand (int *listRand, int batDau, int ketThuc);
int tao_bo_ma (int *bangMa, ofstream &fileXuat, char *tenFileXuat);
int convert_file (int *boMa, ifstream &fileNhap, ofstream &fileXuat);
int delay_ms(int milisec);
int tao_mat_khau(char *matKhau, int n_kiTu);
int tao_ten_file(char *tenFileGoc, char *tenFileXuat, int stt);
int chu_chay();

int khoi_tao_gia_tri (int *list, int soLuong) {
	for (int i=0; i<soLuong; i++) {
		list[i]=0;
	}
	return 0;
}

int swap (int a, int b) {
	int c=a;
	a=b; b=c;
	return 0;
}

int arranger (int *list, int n_phanTu){
	int *me_list = new int [n_phanTu];
	for (int value=0; value<n_phanTu; value++) {
		for (int iList=0; iList < n_phanTu; iList++) {
			if (value==list[iList]) {
				me_list[value]=iList;
				break;
			}
		}
	}
	for (int i=0; i<n_phanTu; i++) {
		list[i]=me_list[i];
	}
	return 0;
}

int make_list_rand (int *listRand, int batDau, int ketThuc) {
	srand(time(NULL));
	int numRand=batDau+rand()%(ketThuc-batDau+1);
	listRand[0]=numRand;
	for (int iListRand=1; iListRand<(ketThuc-batDau+1); iListRand++) {
		bool trung=false;
		do {
			trung=false;
			numRand=batDau+rand()%(ketThuc-batDau+1);
			for (int iDem=0; iDem<iListRand; iDem++)
				if (listRand[iDem]==numRand) trung = true;
		} while (trung);
		listRand[iListRand]=numRand;
	}
	return 0;
}

int tao_bo_ma (int *bangMa, ofstream &fileXuat, char *tenFileXuat) {
	fileXuat.open(tenFileXuat,ios::out|ios::binary);
	fileXuat.write(reinterpret_cast <char*> (bangMa), sizeof(bangMa));
	fileXuat.close();
	return 0;
}

int convert_file (int *boMa, ifstream &fileNhap, ofstream &fileXuat) {
	char ori_char ='\0';
	while (!fileNhap.eof()) {
		fileNhap.get(ori_char); if(fileNhap.eof()) break;
		unsigned char mainChar=ori_char;
		mainChar=(unsigned char)boMa[mainChar];
		fileXuat.put(mainChar);
	}
	return 0;
}

int delay_ms(int milisec) {
	int start=clock();
	int finish=start;
	while (finish-start < milisec) {
		finish=clock();
	}
	return 0;
}

int tao_mat_khau(char *mk){
	mk[31]='\0';
	char ch_mk='\0';
	cout << "===============Tao mat khau================" << endl;
	int num_pass=-1;
	cout << "nhap mat khau (toi da 30 chu so)\n";
	ch_mk=getch();
    while (ch_mk!='\r')
   	{
        	if ((int)ch_mk==8)
			{
				cout << "\b \b";
				if (num_pass > -1)
				{
					mk[num_pass]='\0';
					num_pass -= 1;
				}
			}
			else if (num_pass<29) //bat dau tu 0 den 29 (30 so)
        	{
				mk[++num_pass]=ch_mk;
 				cout.put('*');
        	}
			ch_mk=getch();
	}
	cout << "\nxac nhan mat khau:\n";
	bool OK;
	do {
		OK=true;
		char pass_confirm[31]={};
		int num_pass_confirm=-1;
		ch_mk=getch();
		while (ch_mk!='\r')
		{
			if ((int)ch_mk==8)
			{
				cout << "\b \b";
				if (num_pass_confirm > -1)
				{
					pass_confirm[num_pass_confirm]='\0';
					num_pass_confirm -= 1;
				}
			}
			else if (num_pass_confirm<num_pass)
			{
				pass_confirm[++num_pass_confirm]=ch_mk;
        		putchar('*');
			}
			ch_mk=getch();
		}
		if (num_pass==num_pass_confirm){
    		for (int i=0;i<=num_pass;++i){
				if (mk[i]!=pass_confirm[i]){
					OK=false;
					break;
				}
			}
		} else OK=false;
		if (!OK) cout << "\nmat khau xac nhan khong dung - nhap lai\n";
	} while (!OK);
	return 0;
}

int tao_ten_file(char *tenFileGoc, char *tenFileXuat, int stt) {
	int lengPass=strlen(tenFileXuat);
	for (int iTen=0; iTen<lengPass; iTen++) {
		tenFileXuat[iTen]='\0';
	}
	char ch_stt[10]={};
	strcat(tenFileXuat,tenFileGoc);
	itoa(stt, ch_stt, 10);
	if (stt<10)
		strcat(tenFileXuat,"0");
	strcat(tenFileXuat,ch_stt);
	strcat(tenFileXuat,".passx");
	return 0;
}

int chu_chay (){
	char tenChay[78]="       Lee's produce - this program is protected by Lee Armed Forces       ";
	char mangChay[81]={}; // do dai man hinh la 80
	for (int iMangChay=0; (iMangChay<80-strlen(tenChay))/2; iMangChay++)
		mangChay[iMangChay]=' ';
	strcat(mangChay,tenChay);
	char kiTuDau='\0';
	while(!kbhit()) {
		system("cls");
		for (int iEnter=0; iEnter<12; iEnter++) cout << endl;
		cout << mangChay;
		kiTuDau=mangChay[0];
		int lengMang=strlen(mangChay);
		for (int iMang=1; iMang<lengMang; iMang++) {
			mangChay[iMang-1]=mangChay[iMang];
		}
		mangChay[lengMang-1]=kiTuDau;
		delay_ms(150);
	}
	return 0;
}