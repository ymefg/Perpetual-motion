#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCTIME 100000

long filewz (char afname[], char bfname[], int mixtime, /*int mctime, */int mmover, int delmode, char zipname[], int mixcount);
//int ndoublec (int minmix, int maxmix, long mover, int mctime);
int doublec (int minmix, int maxmix, long mover, int mctime);
int filecopy (char ofname[], char nfname[]);
long filezip (char filename[], char zipname[], int zipmode);
int fdel (char filename[]);
void getseed (unsigned long *a, unsigned long *b);
void scount (unsigned long *a, unsigned long *b);
int fcheck (char filename[]);
long fcount (char filename[]);
void starbar ();
int innum ();

long sstl [3][MAXCTIME];
char ofname[120];
char mdir[120];
char nfname[20];
long fl;

int main()
{
	int selected;
	puts ("欢迎使用超级压缩!");
	puts ("请输入接下来的操作:");
	puts ("1) 压缩文件");
	puts ("2) 帮助&关于");
	puts ("others) 退出");
	innum ();
}

int innum (){
	int minmix, maxmix, ctime, mover, i, m, n;
	char atempc[123], btempc[123];
	
	puts ("输入要压缩文件的路径:");
	scanf (" %s",ofname);
	puts ("输入输出目录:(必须为空目录,且要以\"/\"结尾)");
	scanf (" %s",mdir);
	puts ("输入输出文件名:");
	scanf (" %s",nfname);
	//printf ("Enter copy mode.\n");
	//scanf (" %d",&cpmode);
	puts ("输入最低打乱次数(大于0的整数)");
	scanf (" %d",&minmix);
	puts ("输入最高打乱次数(大于或等于最低打乱次数的整数)");
	scanf (" %d",&maxmix);
	puts ("输入移动次数(大于或等于0的整数)");
	scanf (" %d",&mover);
	puts ("输入压缩次数(大于0的整数)");
	scanf (" %d",&ctime);
	
	starbar();
	puts ("你的选择:");
	printf ("压缩的文件路径:\t%s\n",ofname);
	printf ("输出目录:\t%s\n",mdir);
	printf ("输出文件名:\t%s\n",nfname);
	//printf ("copy mode:\t%d\n",cpmode);
	printf ("最小打乱次数:\t%d\n",minmix);
	printf ("最大打乱次数:\t%d\n",maxmix);
	printf ("移动距离:\t%d\n",mover);
	printf ("压缩次数:\t%d\n",ctime);
	//system ("pause");
	
	puts ("开始");
	starbar ();
	
	for (m = 0; m < 3; m++){
		for (n = 0; n < MAXCTIME; n++){
			sstl[m][n] = 0;
		}
	}
	
	//strcpy (atempc, mdir);
	//fl = fcount (ofname);
	for (i=0; i < ctime; i++){
		if (doublec(minmix, maxmix, mover, i) == 0){
			puts ("Cannot compress anymore!");
			return 0;
		}else{
			printf ("Compress complete!\t%d/%d\n", i + 1, ctime);
			//strcat (atempc, nfname);
			//strcat (atempc, ".scp");
			strcpy (btempc, mdir);
			strcat (btempc, "3");
			//filecopy (atempc, btempc);
			strcpy (ofname, btempc);
			//if (i != ctime - 1)
				//fdel (btempc);
			//fl = fcount (ofname);
		}
	}
	
	return 0;
}

int doublec (int minmix, int maxmix, long mover, int mctime){
	starbar ();
	puts ("doublec 参数:");
	printf ("minmix:\t%d\nmaxmix:\t%d\n", minmix, maxmix);
	printf ("mover:\t%ld\nmctime:\t%d\n", mover, mctime);
	printf ("ofname:\t%s\nmdir:\t%s\n", ofname, mdir);
	printf ("fl:\t%ld\n", fl);
	starbar ();
	puts ("doublec 流程:");
	puts ("加载文件名称...");
	
	char tempchar[122];
	strcpy (tempchar, mdir);
	char afname[123];
	strcpy (afname, strcat (tempchar, "1"));
	strcpy (tempchar, mdir);
	char bfname[123];
	strcpy (bfname, strcat (tempchar, "2"));
	strcpy (tempchar, mdir);
	char cfname[123];
	strcpy (cfname, strcat (tempchar, "3"));
	strcpy (tempchar, mdir);
	char zipname[123];
	strcat (tempchar, nfname);
	strcat (tempchar, ".scp");
	strcpy (zipname, tempchar);
	fl = fcount (ofname);
	int m, n, mixtime, delmode, mt;
	long tempnum, mmover, minl = fl;
	
	puts ("文件名称加载完毕");
	printf ("afname:\t%s\nbfname:\t%s\nmdir:\t%s\nzipname:\t%s\n", afname, bfname, mdir, zipname);
	
	puts ("进入mover循环和mix循环");
	
	for (m=0; m < mover; m++){
		puts ("开始复制");
		filecopy (ofname, afname);
		puts ("复制完毕");
		for (n = minmix; n < maxmix + 1; n++){
			if (n == maxmix) delmode = 1;
			if (n < maxmix) delmode = 3;
			/*if (minmix == 0){
				if (n > 0){
				mt = 1;
				}else{
				mt = 0;
				}
			}else{
				if (n == minmix)
					mt = n;
				if (n != minmix)
					mt = 1;
			}*/
			tempnum = filewz (afname, bfname, n, /*mctime,*/ m, delmode, zipname, n);
			printf ("mover:\t%d\nmixtime:\t%d\nlong:\t%ld\n", m, n, tempnum);
			if (minl > tempnum){
				minl = tempnum;
				mixtime = n;
				mmover = m;
			}
		}
	}
	printf ("minl:\t%ld\nmmover:\t%ld\nmixtime:\t%d", minl, mmover, mixtime);
	puts ("mover循环和mix循环完毕");
	printf ("最佳方案:\nmover:\t%ld\nmixtime:\t%d\nlong:\t%ld\n", mmover, mixtime, minl);
	puts ("开始最佳压缩");
	puts ("开始复制");
	filecopy (ofname, afname);
	puts ("复制完毕");
	if (minl < fl){
		if (minl != filewz (afname, bfname, mixtime,/* mctime,*/ mmover, 0, zipname, 0)){
			printf ("压缩错误");
			return 0;
		}
		sstl[0][mctime] = fl;
		sstl[1][mctime] = mmover;
		sstl[2][mctime] = mixtime;
		fdel (cfname);
		filecopy (zipname, cfname);
		strcpy (ofname, cfname);
		return 1;
	}else{
		puts ("找不到最佳方案");
		return 0;
	}
}

long filewz (char afname[], char bfname[], int mixtime, /*int mctime,*/ int mmover, int delmode, char zipname[], int mixcount){
	starbar ();
	puts ("filewz 参数:");
	printf ("afname:\t%s\nbfname:\t%s\n", afname, bfname);
	printf ("mixtime:\t%d\n", mixtime);
	printf ("mmover:\t%d\ndelmode:\t%d\n", mmover, delmode);
	printf ("fl:\t%ld\nzipname:\t%s\n", fl, zipname);
	
	FILE * ofp, * nfp;
	unsigned long a, b;
	char onr[1];
	long m, n;
	long i, ziplong, sstlmix, sstlmov;
	getseed(&a, &b);
	
	//printf ("mix time:\t%d\nmmove:\t%d\n", mixtime, mmover);
	puts ("filewz 流程:");
	puts ("开始跳过无用文件段");
	
	/*for (m = 0; m < 3; m++){
		for (n = 0; n < mctime; n++){
			for (i = 0; i < sstl[m][n]; i++){
				scount (&a, &b);
			}
		}
	}*/
	/*sstl数组
	sstl[0][n]表示一个长度
	sstl[1][n]表示mover移动距离
	sstl[2][n]表示mixtime混合的次数
	无用文件段=(sstl[0][n]+sstl[1][n])*sstl[2][n]
	*/
	for (m = 0; m < MAXCTIME; m++){
		//sstlmov = sstl[1][m];
		//sstlmix = sstl[2][m];
		for (i = 0; i < sstl[1][m]; i++){
			for (n = 0; n < sstl[0][m]; n++){
			scount (&a, &b);
			}
		}
		for (i = 0; i < sstl[2][m]; i++){
			for (n = 0; n < sstl[0][m]; n++){
			scount (&a, &b);
			}
		}
	}
	for (m = 0; m < 3; m++){
		for (n = 0; n < 10; n++){
			printf ("%ld\t", sstl[m][n]);
		}
		printf ("\n");
	}
	printf ("a:\t%ld\n", a);
	
	puts ("跳过无用文件段完毕");
	puts ("开始位移");
	
	for (m = 0; m < mmover; m++){
		for (n = 0; n < fl; n++){
			scount (&a, &b);
		}
	}
	printf ("a:\t%ld\n", a);
	
	puts ("位移完毕");
	/*puts ("开始跳过mix");
	for (m = 0; m < mixcount; m++){
		for (n = 0; n < fl; n++){
			scount (&a, &b);
		}
	}
	printf ("a:\t%ld\n", a);
	puts ("跳过mix完毕");*/
	puts ("进入mixtime循环");
	
	//if (delmode == 3)
		//mixtime = 1;
	
	for (m = 0; m < fl; m++){
		//printf ("m:\t%ld\n", m);
		//printf ("打开临时文件:\nafname:\t%s\nbfname:\t%s\n", afname, bfname);
		//if (m % 2 == 0){
			ofp = fopen (afname, "rb");
			nfp = fopen (bfname, "wb");
		//}else{
			//ofp = fopen (bfname, "rb");
			//nfp = fopen (afname, "wb");
		//}
		
		//puts ("打开临时文件完毕");
		//puts ("进入fl写临时文件循环");
		fread (onr, sizeof (char), 1, ofp);
		for (i = 0; i < mixtime; i++){
			scount (&a, &b);

			onr[0] ^= a;

			//if (i % (1024 * 1024) == 0)
				//printf ("mixing\t%.3f/100%%\n", float (fl) / float (i));
		}
		
		fwrite (onr, sizeof (char), 1, nfp);
		//printf ("a:\t%ld\n", a);
	
		//puts ("写文件循环完毕");
		//puts ("关闭临时文件");
		
		//puts ("关闭临时文件完毕");
		//puts ("mixtime循环完毕");
	}
	fclose (ofp);
	fclose (nfp);
	puts ("进入删除文件流程");
	//if (mixtime % 2 == 0){
		ziplong = filezip (bfname, zipname, 0);
		if (delmode == 0){
			fdel (afname);
			fdel (bfname);
		}else if (delmode == 1){
			fdel (afname);
			fdel (bfname);
			fdel (zipname);
		}else{
			fdel (bfname);
			fdel (zipname);
		}
		puts ("删除文件完毕");
		printf ("filewz 返回:\t%ld\n", ziplong);
		starbar ();
		return ziplong;
	/*}else{
		ziplong = filezip (bfname, zipname, 0);
		if (delmode == 0){
			fdel (afname);
			//fdel (bfname);
		}else if (delmode == 1){
			fdel (afname);
			//fdel (bfname);
			fdel (zipname);
		}else{
			fdel (afname);
			fdel (zipname);
			filecopy (bfname, afname);
			//fdel (bfname);
		}
		puts ("删除文件完毕");
		printf ("filewz 返回:\t%ld\n", ziplong);
		starbar ();
		return ziplong;
	}*/
}

int fcheck (char filename[]){
	//starbar ();
	//printf ("checkf 参数:\nfilename:\t%s\n", filename);
	//puts ("checkf 流程:");
	
	FILE * fp;
	if ((fp = fopen(filename, "r")) == NULL){
		//fclose (fp);
		puts ("找不到文件");
		//starbar ();
		return 0;
	}else{
		fclose (fp);
		//puts ("文件存在");
		//starbar ();
		return 1;
	}
}

long fcount (char filename[]){
    FILE * fp;
	
	//starbar();
	//printf ("fcount 参数:\nfilename:\t%s\n", filename);
    
	fp = fopen (filename, "r");
	if (fp == NULL){
		puts ("file open error");
		//printf("open file :%s\n", errno);
		exit (0);
	}else{
		fseek (fp, 0L, SEEK_END);
		long a = ftell (fp);
		fclose (fp);
		
		//printf ("fcount 返回:\t%ld\n", a);
		//starbar();
    	return a;
	}
}

int filecopy (char ofname[], char nfname[]){
	//starbar ();
	char ml[150];
	//puts ("filecopy 参数:");
	//printf ("ofname:\t%s\nnfname:\t%s\n", ofname, nfname);
	//puts ("filecopy 流程:");
	//puts ("正在复制...");
	
	/*if ((checkf (ofname)==0) || checkf (nfname)){
		puts ("FILE COPY ERROR!");
		return 0;
	}else{*/
		strcpy (ml, "cp ");
		strcat (ml, ofname);
		strcat (ml, " ");
		strcat (ml, nfname);
		//printf ("copy 命令:\t%s\n", ml);
		system (ml);
		
		//puts ("filecopy完毕");
		//starbar ();
		return 1;
	//}
}

long filezip (char filename[], char zipname[], int zipmode){
	//starbar ();
	//puts ("filezip 参数:");
	char ml [300];
	//printf ("filename:\t%s\nzipname:\t%s\n", filename, zipname);
	//puts ("filezip 流程:");
	
	if (fcheck (filename)){
		//if (zipmode == 0)
			//fdel (zipname);
		strcpy (ml, "zip ");
		strcat (ml, zipname);
		strcat (ml, " ");
		strcat (ml, filename);
		strcat (ml, " -9");
		//printf ("filezip 命令:\t%s\n", ml);
		system (ml);
		//puts ("filezip完毕");
		starbar ();
		return fcount (zipname);
	}else{
		puts ("fzip失败");
		//starbar ();
	}
	
	
}

int fdel (char filename[]){
	//starbar ();
	//printf ("fdel 参数:\nfilename\t%s\n", filename);
	//puts ("fdel 流程:");
	
	char ml[150];
	
	if (1){
		strcpy (ml, "rm ");
		strcat (ml, filename);
		//printf ("fdel 命令:\t%s\n", ml);
		system (ml);
		//starbar ();
		return 1;
	}else{
		puts ("fdel失败");
		//starbar ();
	}
}

void getseed (unsigned long * a, unsigned long * b){
	//starbar ();
	//puts ("正在getseed...");
	*a = 1;
	*b = 1;
	//puts ("getseed完毕");
	//starbar ();
}

void scount (unsigned long * a, unsigned long * b){
	//puts ("seed counting");
	*b += *a;
	*a = *b;
	while (*a > 2000000000) *a -= 2000000000;
	while (*b > 2000000000) *b -= 20000000000;
}

void starbar (){
	puts ("******************************************");
}
