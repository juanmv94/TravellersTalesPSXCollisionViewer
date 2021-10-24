#include "RNC.c"
#include <stdio.h>

char buf[MAX_BUF_SIZE];
char *filecontent;

FILE *raw;

int RNCenc2(char* input, int size) {
	vars_t *v = init_vars();
	v->puse_mode ='p';
	v->method=2;
	v->dict_size = 0x1000;
	v->max_matches = 0xFF;
	v->file_size=size;
	v->input=input;
	v->output = buf;
	v->temp = (uint8*)malloc(MAX_BUF_SIZE);
	do_pack(v);
	size=v->output_offset;
	free(v->temp);
	free(v);
	return size;
}

void toraw(char* input, int size) {
	size=RNCenc2(input, size);
	fwrite(buf+4,size-4,1,raw);
}

int readfile(char* filename) {
	FILE *in=fopen(filename,"rb");
	fseek(in,0,SEEK_END);
    int size = ftell(in);
    fseek(in,0,SEEK_SET);
	filecontent=malloc(size);
	fread(filecontent,size,1,in);
	fclose(in);
	return size;
}

void setbmp4(unsigned int n) {
	char filename[64];
	unsigned char tex[33548];
	*(unsigned int*)(tex)=n; *(unsigned int*)(tex+4)=0x01000100; *(unsigned int*)(tex+8)=0x0300;
	for (int x=0;x<4;x++) for (int y=0; y<4; y++) {
		sprintf(filename,"TEX_%03u_%03u_%03u.BMP",n,x,y);
		int bmpsize=readfile(filename);	//Assert?
		unsigned char *pal=&tex[12+x*48+y*48*4],*bm=&tex[12+768+x*32+y*8192];
		for (int i=0;i<16;i++) {pal[2+i*3]=filecontent[54+i*4]; pal[1+i*3]=filecontent[55+i*4]; pal[0+i*3]=filecontent[56+i*4];}	//PAL
		for (int i=0;i<64;i++) memcpy(&bm[i*128],&filecontent[*(unsigned short *)(filecontent+0x0A)+(63-i)*32],32);					//BM
		free(filecontent);
	}
	for (int i=12+768;i<33548;i++) tex[i]=tex[i]<<4|tex[i]>>4;		//Rotate pair of pixels
	toraw(tex,33548);
}

void setbmp8(char* filename, unsigned int n) {
	int bmpsize=readfile(filename), width=*(int*)(filecontent+18), height=*(int*)(filecontent+22);
	int texsize=16+256*3+width*height;
	char *tex=malloc(texsize);
	*(unsigned int*)(tex)=0x24; *(unsigned int*)(tex+4)=n; *(unsigned short*)(tex+8)=width; *(unsigned short*)(tex+10)=height; *(unsigned int*)(tex+12)=0x010300;	//BM pointer + flag?
	unsigned char *pal=&tex[16],*bm=&tex[16+768];
	for (int i=0;i<256;i++) {pal[2+i*3]=filecontent[54+i*4]; pal[1+i*3]=filecontent[55+i*4]; pal[0+i*3]=filecontent[56+i*4];}		//PAL
	for (int i=0;i<height;i++) memcpy(&bm[i*width],&filecontent[*(unsigned short *)(filecontent+0x0A)+(height-1-i)*width],width);	//BM
	toraw(tex,texsize);
	free(tex);
	free(filecontent);
}

void setbmp16(char* filename, unsigned int n) {
	int bmpsize=readfile(filename), width=*(int*)(filecontent+18), height=*(int*)(filecontent+22);
	int texsize=16+2*width*height;
	char *tex=malloc(texsize);
	*(unsigned int*)(tex)=0x25; *(unsigned int*)(tex+4)=width; *(unsigned int*)(tex+8)=height; *(unsigned int*)(tex+12)=n;
	for (int y=0;y<height;y++) {
		unsigned short *to=(unsigned short*)(tex+16+(height-1-y)*2*width);
		unsigned char *from=filecontent+54+y*3*width;
		for (int x=0;x<width;x++) to[x]=(from[x*3+2]>>3)|((from[x*3+1]&0xF8)<<2)|((from[x*3]&0xF8)<<7);
	}
	toraw(tex,texsize);
	free(tex);
	free(filecontent);
}

void setent(char* filename, int type, int id) {
	int sizeent=readfile(filename);
	char* ent=malloc(sizeent+8);
	*(unsigned int*)ent=0x0100|type; *(unsigned int*)(ent+4)=id;
	memcpy(ent+8,filecontent,sizeent);
	toraw(ent,sizeent+8);
	free(ent);
}

void setentnoid(char* filename, int type) {
	int sizeent=readfile(filename);
	char* ent=malloc(sizeent+4);
	*(unsigned int*)ent=0x0100|type;
	memcpy(ent+4,filecontent,sizeent);
	toraw(ent,sizeent+4);
	free(ent);
}

void setentdatats2(char* filename) {
	char data[2052]={0x23,0};
	FILE *in=fopen(filename,"r");
	char *p=data+4;
	fscanf(in,"%*[^\n]\n");
	while (fscanf(in,"%d;%d;%d;%hhu;%hhu;%hhu;%hhu;%u;%hd;%hd;%hu;%hu;%hhu;%hhu;%hhu;%hhu\n",(int*)(p),(int*)(p+4),(int*)(p+8),&p[12],&p[13],&p[14],&p[15],(unsigned int*)(p+16),(short*)(p+20),(short*)(p+22),(unsigned short*)(p+24),(unsigned short*)(p+26),&p[28],&p[29],&p[30],&p[31])>0) p+=32;
	toraw(data,2052);
}

int WinMain() {
	FILE *in=fopen("RAWLIST.TXT", "r");
	raw=fopen("OUTPUT.RAW", "wb");
	char filename[64];
	while(fscanf(in,"%[^\n]\n",filename)>0) {
		printf("processing %s...\n",filename);
		unsigned int n1,n2;
		if (sscanf(filename,"TEX_%03u_",&n1)==1) {	//BMP4
			setbmp4(n1);
			for (int i=0;i<15;i++) fscanf(in,"%[^\n]\n",filename);
		} else if (sscanf(filename,"TEX_ID_%u_%uBIT",&n1,&n2)==2) {	//BMP 8/16
			if (n2==8) setbmp8(filename,n1);
			else setbmp16(filename,n1);
		}else if (sscanf(filename,"ENT_%03d",&n1)) {	//ENT
			if (filename[10]=='L') setent(filename,0x02,n1);
			else setent(filename,0x01,n1);
		} else if (!strcmp(filename,"TERRAIN.ALL")) setentnoid(filename,0x03);
		else if (!strcmp(filename,"TESTTERR.ALL")) setentnoid(filename,0x04);
		else if (!strcmp(filename,"ENTDATA_TS2.CSV")) setentdatats2(filename);
		else {int filesize=readfile(filename); toraw(filecontent,filesize);}
	}
	fclose(in);
	for (int i=0;i<8;i++) fputc(0xFF,raw);
	fclose(raw);
}