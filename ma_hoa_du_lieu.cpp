#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "ham_bo_xung.h"
using namespace std;
int khoi_tao_gia_tri (int *list, int soLuong);
int swap (int a, int b);
int arranger (int *list, int n_phanTu);
int make_list_rand (int *listRand, int batDau, int ketThuc);
int tao_bo_ma (int *bangMa, ofstream &fileXuat, char *tenFileXuat);
int convert_file (int *boMa, ifstream &fileNhap, ofstream &fileXuat);
int delay_ms(int milisec);
int tao_mat_khau(char *mk);
int tao_ten_file(char *tenFileGoc, char *tenFileXuat, int stt);
int main_func();
int chu_chay();
int main () {
	chu_chay();
	int luaChon=0;
	do {
		system("cls");
		main_func();
		cout << "Tiep tuc hay dung lai? (1.tiep tuc | 2.dung lai)";
		do cin >> luaChon; while (luaChon!=2&&luaChon!=1);
	} while (luaChon!=2);
	return 0;
}
int main_func(){
	int luaChon=0;
	system("cls");
	cout << "Ban muon \"Ma Hoa\" hay \"Giai Ma\" file? (1.Ma Hoa|2.Giai Ma): ";
	do cin >> luaChon; while (luaChon!=1 && luaChon!=2);
	if (luaChon==1) {
		system("cls");
		char tenFileGoc[101]={}; //nhap ten file
		cout << "Nhap ten file can ma hoa(khong qua 100 ki tu, bao gom duoi file. vd: file.dx)\n";
		fflush(stdin);
		cin.getline(tenFileGoc,100,'\n');
		ifstream mainFile; //kiem tra file
		mainFile.open(tenFileGoc,ios::in);
		if (mainFile.fail()) {
			do {
				mainFile.close();
				cout << "File khong ton tai-yeu cau nhap lai: ";
				fflush(stdin);
				cin.getline(tenFileGoc,100,'\n');
				mainFile.open(tenFileGoc,ios::in);
			} while(mainFile.fail());
		}
		mainFile.close();
		int soLop=0;
		cout << "Nhap so Lop ma hoa(0 < x <= 50): ";
		do cin >> soLop; while (soLop<=0 && soLop>50);
		char mk[40]={};
		tao_mat_khau(mk);
		//========tao mang nguon=========
		cout << "\nDang tao file.pass . . . .\n";
		int mangNguon[256]={};
		for (int i=0; i<256; i++) {
			mangNguon[i]=rand()%256+1;
		}
		mangNguon[3]=soLop; //so lop(3)
		mangNguon[6]=strlen(mk); //do dai mat khau(6)
		//bat dau tu mangNguon[15] sao chep thu tu doc file passx
		int *tt_docFile=new int [soLop];
		tt_docFile[0]=1;
		if (soLop==1) mangNguon[15]=1;
		else {
			make_list_rand(tt_docFile, 1, soLop);
			for (int iLop=0; iLop<soLop; iLop++) {
				mangNguon[15+iLop]=tt_docFile[iLop];
			}
		}
		int a=15+soLop, b=256-strlen(mk);
		delay_ms(1000);
		mangNguon[7]=a+rand()%(b-a+1); // vi tri cua mat khau(7)
		for (int iMk=0; iMk<strlen(mk); iMk++) {
			mangNguon[mangNguon[7]+iMk]=mk[iMk];
		}
		ofstream fileXuat;
		char tenFileXuat[101]={};
		tao_ten_file(tenFileGoc,tenFileXuat,0);
		fileXuat.open(tenFileXuat,ios::out|ios::binary);
		fileXuat.write(reinterpret_cast <char*> (mangNguon), sizeof(mangNguon));
		fileXuat.close();
		//============tao file mat ma================
		int boMa[256]={};
		for (int iBoMa=0; iBoMa<256; iBoMa++) {
			boMa[iBoMa]=iBoMa;
		}
		for (int iLop=0; iLop<soLop; iLop++) {
			int trungGian[256]={};
			delay_ms(200);
			make_list_rand(trungGian,0,255);
			int leng=strlen(tenFileXuat);
			for (int iTen=0; iTen<leng; iTen++){
				tenFileXuat[iTen]='\0';
			}
			tao_ten_file(tenFileGoc,tenFileXuat,tt_docFile[iLop]);
			fileXuat.open(tenFileXuat,ios::out|ios::binary);
			fileXuat.write(reinterpret_cast <char*> (trungGian), sizeof(trungGian));
			fileXuat.close();
			for (int iBoMa=0; iBoMa<256; iBoMa++) {
				boMa[iBoMa]=trungGian[boMa[iBoMa]];
			}
		}
		cout << "Tao file thanh cong!\nDang Ma Hoa file . . . .\n";
		int leng=strlen(tenFileXuat);
		for (int iTen=0; iTen<leng; iTen++){
				tenFileXuat[iTen]='\0';
		}
		strcat(tenFileXuat,tenFileGoc);
		strcat(tenFileXuat,".source");
		mainFile.open(tenFileGoc,ios::in|ios::binary);
		fileXuat.open(tenFileXuat,ios::out|ios::binary);
		convert_file(boMa,mainFile,fileXuat);
		mainFile.close();
		fileXuat.close();
		cout << "Ma hoa file hoan tat!\n";
		cout << "Chu y!: giu that ky + khong doi ten cac file.passx va file.source\n";
		cout << "\n\n";
	}
	if(luaChon==2) {
		system("cls");
		char tenFileGoc[101]={}; //nhap ten file.source
		cout << "Nhap ten file.source: ";
		fflush(stdin);
		cin.getline(tenFileGoc,100,'\n');
		ifstream mainFile; //kiem tra file
		mainFile.open(tenFileGoc,ios::in);
		if (mainFile.fail()) {
			do {
				mainFile.close();
				cout << "File khong ton tai-yeu cau nhap lai: ";
				fflush(stdin);
				cin.getline(tenFileGoc,100,'\n');
				mainFile.open(tenFileGoc,ios::in);
			} while(mainFile.fail());
		}
		mainFile.close();
		for (int i=0; i<7; i++) { // ".source co 7 ki tu-xoa chuoi ".source
			tenFileGoc[strlen(tenFileGoc)-1]='\0';
		}
		char tenFilePass[101]={};
		tao_ten_file(tenFileGoc,tenFilePass,0);
		ifstream filePass; //kiem tra cac file.passx
		filePass.open(tenFilePass,ios::in|ios::binary);
		if (!filePass.fail()) {
			int mangNguon[256];
			filePass.read(reinterpret_cast <char*> (mangNguon), sizeof(mangNguon)); //lay du lieu file
			int soLop=mangNguon[3];
			int lengMk=mangNguon[6];
			int viTriMk=mangNguon[7];
			int *tt_doc=new int [soLop];
			for (int iLop=0; iLop<soLop; iLop++) {
				tt_doc[iLop]=mangNguon[15+iLop];
			}
			char *mkGoc=new char [lengMk+1];
			mkGoc[lengMk]='\0';
			for (int iMk=0; iMk<lengMk; iMk++) {
				mkGoc[iMk]=(char)mangNguon[viTriMk+iMk];
			}
			filePass.close();
			char mkNhap[40]={};
			char ch_mk='\0';
			int num_pass=-1;
			cout << "nhap mat khau cho file (toi da 30 chu so)\n";
			ch_mk=getch();
			while (ch_mk!='\r')
   			{
        		if ((int)ch_mk==8)
				{
					cout << "\b \b";
					if (num_pass > -1)
					{
						mkNhap[num_pass]='\0';
						num_pass -= 1;
					}
				}
				else if (num_pass<29) //bat dau tu 0 den 29 (30 so)
        		{
					mkNhap[++num_pass]=ch_mk;
 					cout.put('*');
        		}
				ch_mk=getch();
			}
			if(strcmp(mkGoc,mkNhap)!=0) {
				cout << "Mat khau sai\n";
				goto exixt;
			} 
			else {
				int lengPass=strlen(tenFilePass);
				for (int iLop=0; iLop<=soLop; iLop++){
					tao_ten_file(tenFileGoc,tenFilePass,iLop);
					filePass.open(tenFilePass,ios::in);
					if (filePass.fail()) {
						goto khongDuFile;
						break;
					} else filePass.close();
				}
				int boMa[256]={};
				for (int iBoMa=0; iBoMa<256; iBoMa++) {
						boMa[iBoMa]=iBoMa;
				}
				for (int iLop=0; iLop<soLop; iLop++){
					tao_ten_file(tenFileGoc,tenFilePass,tt_doc[iLop]);
					filePass.open(tenFilePass,ios::in|ios::binary);
					int trungGian[256];
					filePass.read(reinterpret_cast<char*> (trungGian),sizeof(trungGian));
					filePass.close();
					for (int iBoMa=0; iBoMa<256; iBoMa++) {
						boMa[iBoMa]=trungGian[boMa[iBoMa]];
					}
				}
				arranger(boMa,256);
				char tenFileSource[256]={};
				strcat(tenFileSource,tenFileGoc);
				strcat(tenFileSource,".source");
				ofstream fileXuat;
				ifstream fileKiem;
				fileKiem.open(tenFileGoc,ios::in);
				if (!fileKiem.fail()) {
					fileKiem.close();
					cout << "\nTen file " << tenFileGoc << " ton tai!\n";
					cout << "Ban muon \"GHI DE\" hay \"TAO FILE MOI\"? (1.ghi de | 2.tao file moi)\n";
					int lua_chon=0;
					do {
						cin >> lua_chon;
					} while (lua_chon!=1 && lua_chon!=2);
					if (lua_chon==2) strcat(tenFileGoc,"(2)"); else remove(tenFileGoc);
				}
				mainFile.open(tenFileSource,ios::in|ios::binary);
				fileXuat.open(tenFileGoc,ios::out|ios::binary);
				cout << "\nDang giai ma file . . . . \n";
				convert_file(boMa,mainFile,fileXuat);
				mainFile.close();
				fileXuat.close();
				cout << "\nGiai ma hoan tat!\n";
				cout << "\n\n";
			}
		} 
		else {
			khongDuFile:cout << "\nKhong du file-vui long kiem tra lai cac file.passx\n";
			cout << "\n\n";
		}
		exixt:;
	}
	return 0;
}