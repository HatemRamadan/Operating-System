  void parseCommand(char*);
  int add2(char);
  
  int main(){
          
          while(1){
          char line[512];
          char nl[1];
          
          //nl[0]="/0";
          //interrupt(0x21,0,nl,0,0);
          interrupt(0x21,0,"SHELL>\0",0,0);    
          
          interrupt(0x21,1,line,0,0);    
        
          parseCommand(line);
          }    
  }

  void parseCommand(char* command){int z=0;
         if(command[1]=='v' && command[2]=='i' && command[3]=='e' && command[4]=='w')
          {
            char st [3];
            char st2 [3];
            char s [30];
            int flag;
            char buffer[13312];
            int i;
            int j;
            char dir [512];
            flag =0;
            st[0]=0xa;
            st[2]='\0';
            st[1]='\r'; 
            
            interrupt(0x21, 2 ,dir,2, 0);
            
            for(i=6;command[i]!=0xa;i++);
              command[i] = 0x0;

            for(i=6;command[i]!=0xd;i++);
              command[i] = 0x0;
            
            for(i=0;i<16;i++){
                char name2 [7];
                for(j=0;j<6;j++){
                    name2[j] = dir[(i*32)+j];
                }
                name2[6]='\0';

                if(compare(&(command[6]),name2)==1){
                flag = 1;
                break;
              
               }
            }
 
            if(flag==1){
              interrupt(0x21,3,&(command[6]),buffer,0);
              interrupt(0x21, 0, st, 0, 0);
              interrupt(0x21, 0, buffer, 0, 0); 
              //interrupt(0x21, 0, st, 0, 0);
             }
            if(flag==0){
              interrupt(0x21, 0, "\nfile does not exist\r\0", 0, 0); 
            st2[0]=0xa;
            st2[2]='\0';
            st2[1]='\r'; 
            interrupt(0x21, 0, st2, 0, 0);
            
             }                                        
          }   
          else if(command[1]=='e' && command[2]=='x' && command[3]=='e' && command[4]=='c' && command[5]=='u' && command[6]=='t' && command[7]=='e')
          {
              char st[3];
             st[0]=0xa;
             st[1]='\n';
             st[2]='\0';
             interrupt(0x21, 0, st, 0, 0);
             interrupt(0x21, 4, &(command[9]), 0x2000, 0);    

          }   
          else if(command[1]=='d' && command[2]=='e' && command[3]=='l' && command[4]=='e' && command[5]=='t' && command[6]=='e')
          {
            char st [3];
            char st2 [3];
            char s [30];
            int flag;
            int i;
            int j;
            char dir [512];
            flag =0;
            st[0]=0xa;
            st[2]='\0';
            st[1]='\r'; 
            
            interrupt(0x21, 2 ,dir,2, 0);
            
            for(i=8;command[i]!=0xa;i++);
              command[i] = 0x0;

            for(i=8;command[i]!=0xd;i++);
              command[i] = 0x0;

            for(i=0;i<16;i++){
                char name2 [7];
                for(j=0;j<6;j++){
                    name2[j] = dir[(i*32)+j];
                }
                name2[6]='\0';
                if(compare(&(command[8]),name2)==1){
                flag = 1;
                break;
              
               }
            }

            if(flag==1){
               interrupt(0x21, 7, &(command[8]), 0, 0);
               interrupt(0x21, 0, st, 0, 0);
             }
            if(flag==0){
              interrupt(0x21, 0, "\nfile does not exist\r\0", 0, 0); 
            st2[0]=0xa;
            st2[2]='\0';
            st2[1]='\r'; 
            interrupt(0x21, 0, st2, 0, 0);
            
             }
                
                        
          }else
          if(command[1]=='c' && command[2]=='o' && command[3]=='p' && command[4]=='y'){
            int k;
            char* name1;
            char st [3];
            char st2 [3];
            char s [30];
            int flag;
            int flag2;
            char buffer[13312];
            int i;
            int j;
            int count;
            int secN;
            char dir [512];

            for(i=6;command[i]!=0x20;i++)
              name1[i-6]=command[i];
           

            for(k=i+1;command[k]!=0xa;k++);
              command[k] = 0x0;

            for(k=i+1;command[k]!=0xd;k++);
              command[k] = 0x0;

            flag =0;
            flag2 = 0;
            st[0]=0xa;
            st[2]='\0';
            st[1]='\r'; 
            
            interrupt(0x21, 2 ,dir,2, 0);
            
            for(k=0;k<16;k++){
                char name3 [7];
                for(j=0;j<6;j++){
                    name3[j] = dir[(k*32)+j];
                }
                name3[6]='\0';
                                
                if(compare(&(command[i+1]),name3)==1){
                flag2 = 1;
                break;
              
               }
            }
            if(flag2==1){
              interrupt(0x21, 0, "\n\r\0", 0, 0);
              interrupt(0x21, 0,&(command[i+1]) , 0, 0);
              interrupt(0x21, 0, " already exists\r\0", 0, 0);
              interrupt(0x21, 0, st, 0, 0);
            }
            else{

            for(k=0;k<16;k++){
                char name2 [7];
                for(j=0;j<6;j++){
                    name2[j] = dir[(k*32)+j];
                }
                name2[6]='\0';
                                
                if(compare(name1,name2)==1){
                flag = 1;
                break;
              
               }
            }

            if(flag==1){
              interrupt(0x21,3,name1,buffer,0);
              
              for(count=0;buffer[count]!=0x0;count++);
              count--;

              secN = div(count,512);
              if(mod(count,512)!=0)
                secN++;
              
              interrupt(0x21, 8, &(command[i+1]), buffer, secN); 
              interrupt(0x21, 0, st, 0, 0);
             }
            if(flag==0){  
             interrupt(0x21, 0, "\n\r\0", 0, 0);
             interrupt(0x21, 0, "'\0", 0, 0);
             interrupt(0x21, 0,name1, 0, 0);
             interrupt(0x21, 0, "'\0", 0, 0);
             interrupt(0x21, 0, " does not exist\r\0", 0, 0);  
            //interrupt(0x21, 0, "\nfile does not exist\r\0", 0, 0); 
            st2[0]=0xa;
            st2[2]='\0';
            st2[1]='\r'; 
            interrupt(0x21, 0, st2, 0, 0);
            
             }
          }
           name1[0]=0x0;
           name1[1]=0x0;
           name1[2]=0x0;
           name1[3]=0x0;
           name1[4]=0x0;
           name1[5]=0x0;
           name1[6]=0x0;

          
          }
          else if(command[1]=='d' && command[2]=='i' && command[3]=='r'){
            int i;
            int j;
            char dir [512];
            char fileName [7];
            char size [2];  
            char size2 [3];
            char st[3];
            int flag;
            size[0] = 0x30;
            size[1] = 0x30;
            
            st[0]=0xa;
            st[2]='\0';
            st[1]='\r'; 
            
            interrupt(0x21, 0, st, 0, 0);
            interrupt(0x21, 2 ,dir,2, 0);
            for(i=0;i<16;i++){
              if(dir[32*i]!=0x0){
                   for(j=0;j<6;j++){
                    fileName[j] = dir[(32*i)+j];
                   }
                   fileName[6]=0x00;
                   interrupt(0x21,0,fileName,0,0);
                   interrupt(0x21,0,"  size: \0");
                   for(j=0;j<26;j++){
                     if(dir[(32*i)+j+6]!=0x00){
                      size[1] = size[1]+1;
                      flag = add2(size[1]);
                      if(flag==1){
                        if(size[0]==0x30){
                          size[0] = 0x31;
                          size[1] = 0x30;
                        }
                        else
                        {
                         size[0] = 0x32;
                         size[1] = 0x30; 
                        }
                      }
                     }
                   }
                   if(size[0]==0x30){
                   size2[0]=size[1];
                   size2[1] = '\0';
                   interrupt(0x21,0,size2,0,0);  
                   }
                   else{
                   size2[0]=size[0];
                   size2[1] = size[1];
                   size2[2]='\0';
                   interrupt(0x21,0,size2,0,0);
                   }
                   interrupt(0x21, 0, st, 0, 0);
                   for(j=0;j<6;j++){
                      fileName[j] = 0x00;
                   }
                   size[0] = 0x30;
                   size[1] = 0x30;
              }
            }
          }
          else if(command[1]=='c' && command[2]=='r' && command[3]=='e' && command[4]=='a' && command[5]=='t'&& command[6]=='e'){
            int flag;
            int i;
            int k;
            int j;
            int c;
            int secN;
            char dir [512];
            char st [3];
            char line2 [13312];
            char file [13312];
            int counter ;
            char tst [3];
            secN =0;
            counter=0;
            st[0]=0xa;
            st[2]='\0';
            st[1]='\r';
            interrupt(0x21, 2 ,dir,2, 0);
            

            for(i=8;command[i]!=0xa;i++);
              command[i] = 0x0;

            for(i=8;command[i]!=0xd;i++);
              command[i] = 0x0;


            for(k=0;k<16;k++){
                char name2 [7];
                for(j=0;j<6;j++){
                    name2[j] = dir[(k*32)+j];
                }
                name2[6]='\0';                                
                if(compare(&(command[8]),name2)==1){
                flag = 1;
                break;
              
               }
            }
          if(flag==1){
              interrupt(0x21,0,st,0,0);
              interrupt(0x21,0,"file already exists\0",0,0);
              interrupt(0x21,0,st,0,0);              
          }
          else
          {
            interrupt(0x21,0,st,0,0);            
            while(1){
             interrupt(0x21,1,line2,0,0);                            
              for(c=0;c<13312;c++){
                if(line2[c]==0x0){
                  counter--;
                  break;
                }
              file[counter] = line2[c];
              tst[0]=line2[c];
              tst[1]='\0';
              counter++;
              }
            interrupt(0x21,0,st,0,0);
            
            //if(line2[2]==0xa){interrupt(0x21,0,"spotted\0",0,0);}
            if(line2[0]==0xa && line2[2]==0xa ){
              break;
            }
            }
            secN = div(counter,512);
              if(mod(counter,512)!=0)
                secN++;               
            //write file
              if(file[1]=='\0')
              interrupt(0x21,0,"zerooo\0",0,0);
            else{
              interrupt(0x21,0,st,0,0);
              interrupt(0x21, 8, &(command[8]), file, secN);
            counter=0;
            for(i=0;i<13312;i++)
              file[i]=0x0;
          }
        }
          }
          else if(command[1]=='k' && command[2]=='i' && command[3]=='l' && command[4]=='l' ){
            char st [3];
            int c = command[6]-'0';
            st[0]=0xa;
            st[2]='\0';
            st[1]='\r';
            interrupt(0x21,0,st,0,0);
            interrupt(0x21, 9, c, 0, 0);
          }
             else 
            {
              char st[20];
              st[0]=0xa;
              st[1]='b';
              st[2]='a';
              st[3]='d';
              st[4]=' ';
              st[5]='c';
              st[6]='o';
              st[7]='m';
              st[8]='m';
              st[9]='a';
              st[10]='n';
              st[11]='d';
              st[12]='\n';
              st[13]='\r';
              st[14]='\0';
              
              interrupt(0x21,0,st,0,0);
           }
           //for(z=0;z<512;z++){
            //command[z]=0x0;
           //} 
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

int add2(char number){
if(number > 0x39)
  return 1;
else
  return 0;
}