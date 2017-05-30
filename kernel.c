void printString(char*);
void readString(char*);
int div(int,int);
int mod(int,int);
void readSector(char*,int);
void handleInterrupt21(int , int, int, int );
void readFile(char*,char*);
int compare(char*,char*);
void executeProgram(char*);
void terminate();
void writeSector(char*,int);
void deleteFile(char*);
void writeFile(char*, char*, int);
void checkExistance(char*,char);
void handleTimerInterrupt(int, int);
int status[8];
int SPs [8];
int currentProcess;
int counter =0;
int main()
{
	//M1
	/*
    char line[512];
	makeInterrupt21();
	interrupt(0x21,1,line,0,0);
	interrupt(0x21,0,line,0,0);
	*/
	
	//M2-Task 1
	
	/*char buffer[13312]; //this is the maximum size of a file
    makeInterrupt21();
    interrupt(0x21, 3, "messag", buffer, 0); //read the file into buffer
    interrupt(0x21, 0, buffer, 0, 0); //print out the file
    while(1);*/
    

    //M2-Task 2
    /*makeInterrupt21();
    interrupt(0x21, 4, "tstprg\0", 0x2000, 0);
    while(1);*/

    //M2-Task 4
	int i;
	currentProcess = -1;
    for (i = 0; i < 8; i++)
    {status[i]=0;
     SPs[i]=0xFF00;  
    }

    makeTimerInterrupt();
    makeInterrupt21();
    //interrupt(0x21, 4, "hello1\0", 0, 0);
	//interrupt(0x21, 4, "hello2\0", 0, 0);


    interrupt(0x21, 4, "shell\0", 0x2000, 0);
    
    //M3-Task1
    /*char buffer [512];
    makeInterrupt21();
    interrupt(0x21,6,"hatem\0",10,0);    
    interrupt(0x21,2,buffer,10,0);    
    interrupt(0x21,0,buffer,0,0);
    while(1);*/   

    //M3-Task 2
    /*char buffer[13312]; 
    makeInterrupt21();
    interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
    interrupt(0x21, 3, "messag\0", buffer, 0); // try to read messag
    interrupt(0x21, 0, buffer, 0, 0); //print out the contents of buffer*/

    //M3-Task 3
    /*int i=0;
    char buffer1[13312];
	char buffer2[13312];
	buffer2[0]='h'; buffer2[1]='e'; buffer2[2]='l'; buffer2[3]='l';
	buffer2[4]='o';
	for(i=5; i<13312; i++) buffer2[i]=0x0;
	makeInterrupt21();
	interrupt(0x21,8, "testW\0", buffer2, 1); //write file testW
	interrupt(0x21,3, "testW\0", buffer1, 0); //read file testW
	interrupt(0x21,0, buffer1, 0, 0); // print out contents of testW
    while(1);*/

}

void readString(char* line)
{
	
	int i=0;
	line[0]=0xa;
	while(line[i] != 0xd)
	{
		i++;
		line[i] = interrupt(0x16, 0, 0, 0, 0);
		if(line[i] != 0x8)
		interrupt(0x10, 0xE*256+ line[i], 0, 0, 0);
		else
		{
			if(i !=0)
			{
			
			interrupt(0x10, 0xE*256+ line[i], 0, 0, 0);
			interrupt(0x10, 0xE*256+ ' ', 0, 0, 0);
			interrupt(0x10, 0xE*256+ line[i], 0, 0, 0);
			i-=2;
			
			}
		}
		
	}
	
	line[i+1]=0xa;
	line[i+2]='\0';
	
}


void printString(char* line)
{
	int i=0;
	while(line[i]!= '\0')
	{
	interrupt(0x10, 0xE*256+ line[i], 0, 0, 0);
	i++;
	}
}

int div(int x,int y)
{
int c=0;
while(x>=y)
{
	c++;
	x-=y;
}
return c;
}
int mod(int x,int y)
{
	int c=0;
	c= x-y*div(x,y);
}
void readSector(char* Buffer,int sector)
{
	int relative_sector = mod(sector,18)+1;
	int head = mod(div(sector,18),2);
	interrupt(0x13,2*256+1,Buffer,div(sector,36)*256+relative_sector,head*256);
}
void writeSector(char* Buffer,int sector){
	int relative_sector = mod(sector,18)+1;
	int head = mod(div(sector,18),2);
	interrupt(0x13,3*256+1,Buffer,div(sector,36)*256+relative_sector,head*256);
}
void deleteFile(char* name){
char dir[512];
char map[512];
int i=0;
readSector(map,1);
readSector(dir,2);
for(i=0;i<16;i++)
	{
	char fileName [7];
 	       int j;
		for(j=0;j<6;j++)
		{
			fileName[j] = dir[(i*32)+j];
		}
		fileName[6]='\0';
		 if(compare(name,fileName)==1)
		 {
        //delete file
		 	dir[i*32]=0x0;
		 	for(j=0;j<26;j++)
		 	{
		 		if(dir[(i*32)+6+j]!=0)
		 			map[dir[(i*32)+6+j]]=0x00;
		 		else
		 			break;
		 	}

        }
	}
	writeSector(map,1);
	writeSector(dir,2);
	
}

void writeFile(char* name, char* buffer, int secNum){
	char dir[512];
	char map[512];
	int i=0;
	int j=0;
	int k = 0;
	int entry = -1;
	char test [7];
	readSector(map,1);
	readSector(dir,2);
	
	for(i=0;i<16;i++){
		if(dir[i*32]==0x0){
			entry = i;
			break;
		}
	}
	if(entry == -1){
		printString("error, directory is full\0");
	}

	else

	{   // saving file name in the dirctory
		for(i=0;i<6;i++){
			if(name[i]=='\0' || name[i]==0xa || name[i]==0xd){
				for(j=i;j<6;j++){
					dir[(entry*32)+j]=0x00;}
					break;
				}
				else{
					dir[(entry*32)+i]=name[i];
					
				}
			}
		
        k = secNum;
		for(i=0;i<secNum;i++){
			for(j=0;j<512;j++){
				if(map[j]==0x00){
					map[j]=0xFF;
					dir[(entry*32)+6+i] = j;
					writeSector(buffer,j);
					buffer += 512;
					k--;
					break;
				}
			}
		}
		for(i=0;i<(26-secNum);i++){
			dir[(entry*32)+6+secNum+i]=0x00;
		}
        if(k==0){
		writeSector(map,1);
		writeSector(dir,2);
	    }
	        else{
                 printString("error, there's not enough sectors\0");
		}
	}
}

void handleInterrupt21(int a, int b, int c, int d){	 
	if(a==0)
		 printString(b);
	else
		if(a==1)
			 readString(b);
		else
			if(a==2)
				 readSector(b,c);
			else
				if(a==3)
					 readFile(b,c);
				else
					if(a==4)
						 executeProgram(b);
					else 
						if(a==5)
							 terminate();
						else 
							if(a==6)
								 writeSector(b,c);
							else
								if(a==7)
								     deleteFile(b);
								else
									if(a==8)
                                          writeFile(b,c,d);   
									else
										if(a==9)
											killProcess(b);
											else
												printString("OS error\0");
}

void readFile(char* name,char* buffer){
	char dir[512];
	int flag=0;
	int entry = 0;
	int i;
	char sectors[26];
	readSector(dir,2);
	for(i=0;i<16;i++){
		char name2 [7];
 	       int j;
		for(j=0;j<6;j++){
			name2[j] = dir[(i*32)+j];
		}
		name2[6]='\0';
		 if(compare(name,name2)==1){
            flag = 1;
            entry = i;
			break;
		}
	}
	if(flag==0)
		return;
	else{
		for(i=0;i<26;i++){
        	sectors[i] = dir[(entry*32)+6+i];
		}

		for(i=0;i<26;i++){	
			if(sectors[i]==0x0){
				break;
			}
			else{
				readSector(buffer,sectors[i]);
				buffer += 512;
			}
		}
	}

	printString(buffer);
}

int compare(char* name,char* nameR){
	int i;
	char nameA[7];
	int j;
	
	if(nameR[0]==0x0)
		return 0;
	
	for(i=0;i<6;i++){
		if(name[i]=='\0'){
              while(i<6){
         		nameA[i] = 0x0;
         		i++;
          	}
		}else
			nameA[i] = name[i];
	}
	nameA[6]='\0';

	for(i=0;i<6;i++)
		if(nameA[i]!=nameR[i])
			return 0;
	return 1;
}
void checkExistance(char* name,int *flag){
    char dir[512];
	int i;
	readSector(dir,2);
	for(i=0;i<16;i++){
		char name2 [7];
 	       int j;
		for(j=0;j<6;j++){
			name2[j] = dir[(i*32)+j];
		}
		name2[6]='\0';
		 if(compare(name,name2)==1){
            flag = 1;
            return;
            
		}
	}
	flag = 0;
}

void executeProgram(char* name){
	char buffer[13312];
	int i;
	int j = 0x0000;
	int k=0;
	int segment;
    readFile(name,buffer);
	if(buffer[0]!=0x0){
	setKernelDataSegment();
	for(i=0;i<8;i++){
		if(status[i]==0){
			k=i;
			break;
		}
	}
	status[k]=1;
	SPs[k]=0xff00;
	restoreDataSegment();
	segment = (k+2)*0x1000;
    for(i=0;i<13312;i++){
      putInMemory(segment, i , buffer[i]);
      j++;
    }
    initializeProgram(segment);
	}
    else{
     	return;
    }
}

void terminate(){
	setKernelDataSegment();
	status[currentProcess]=0;
	while(1);
}

void handleTimerInterrupt(int segment, int sp){
//printString("Tic");
int i;
char t[2];
int current;
current=currentProcess;
counter++;
t[0]= '0'+div(counter,10);
t[1]= '0'+mod(counter,10);
//printString(t);
if(counter==100){
	counter=0;
	SPs[currentProcess]=sp;
	
	for (i = 0; i < 7; i++)
	{
		if (current!=7)
		{current++;
			if(status[current]==1)
				break;
		}
		else
		{
			current=0;
			if(status[current]==1)
				break;

		}
	}
	if(i==7){
		returnFromTimer(segment,sp);}
	else
	{
		currentProcess = current;
		returnFromTimer((current+2)*0x1000,SPs[currentProcess]);		
	}			
}
returnFromTimer(segment,sp);
}
killProcess(int process){
setKernelDataSegment();
status[process] = 0;
restoreDataSegment();	
}