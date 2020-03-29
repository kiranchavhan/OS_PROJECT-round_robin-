#include<stdio.h>

struct request{
    int process_id;//process id
    int temp;
    int burst_time;//burst time
    int completion_time;
    int rburst_time;
    int query_type;

}f[100], s[100], m[100];

int n, fc=0, sc=0, mc=0;
int quanta;
int ghanttchart[100];

void roundRobin(){
    int time= m[0].temp, mark=0, cc=0, i, rc,cnt=0;
    while(time!=120 && cc!=mc){
        for(; i<=mark; i++){
            if(m[i].rburst_time > quanta){
                time += quanta;
                m[i].rburst_time -= quanta;
                ghanttchart[cnt]=m[i].process_id;
                cnt++;

            }
            else if(m[i].rburst_time <=quanta && m[i].rburst_time !=0){
                time += m[i].rburst_time;
                m[i].rburst_time =0;
                m[i].completion_time = time;
                cc++;
                ghanttchart[cnt]=m[i].process_id;
                cnt++;
            }
            // else break;
        }
        int start = mark+1,flag=0;
        for(rc= start; rc<mc; rc++){
            if(m[rc].temp <= time){
                mark++;
                flag=1;
            }
            else if (m[i-1].rburst_time==0){
                time++;
            }

        }if(flag==1)i++;else i=0;
    }
}

void merger(){
    int isc=0, ifc= 0, min, flag;
    if( fc!=0  && sc!=0){
        while(isc<sc && ifc<fc){
            if(f[ifc].temp == s[isc].temp){
                m[mc] = f[ifc];
                mc++;
                ifc++;
                m[mc]= s[isc];
                mc++;
                isc++;
            }
            else if(f[ifc].temp < s[isc].temp){
                m[mc]= f[ifc];
                mc++;
                ifc++;
            }
            else if(f[ifc].temp > s[isc].temp){
                m[mc]= s[isc];
                mc++;
                isc++;
            }
            else;
        }
        if(mc != (fc+sc)){
            if(fc!=ifc){
                while(ifc!=fc){
                    m[mc]= f[ifc];
                    mc++;
                    ifc++;
                }
            }
            else if(sc!=isc){
                while(isc!=sc){
                    m[mc]= s[isc];
                    mc++;
                    isc++;
                }
            }
        }
    }
    else if(fc==0){
        while(isc!=sc){
            m[mc]= s[isc];
            mc++;
            isc++;
        }
    }
    else if(sc==0){
        while(ifc!=fc){
            m[mc]= f[ifc];
            mc++;
            ifc++;
        }
    }
    else {
        printf("\n No valid Requests available\n");
    }
}

void printer(){
    int i=0, total=0, sum=0,k=0;
    double avg;
    printf("\nEXECUTION SEQUENCE\n");
    printf("<");
    for(int j=0;ghanttchart[j]!=0;j++){

        printf("Q%d,",ghanttchart[j]);

    }
    printf(">");
    printf("\nSummary for the Execution\n");
    printf("\nQuery ID\tQuery Type\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time");
    for(i; i<mc; i++){
        char s;
        if(m[i].query_type==1)s='F';
        else s='S';
        printf("\n%d\t\t%c",
               m[i].process_id,s);
        printf("\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d", (m[i].temp+1000), m[i].burst_time, (m[i].completion_time+1000), (m[i].completion_time-m[i].temp), ((m[i].completion_time-m[i].temp)- m[i].burst_time));
        total= m[i].completion_time;
        sum+= (m[i].completion_time-m[i].temp);
    }
    avg = sum/mc;
    printf("\n\nTotal time Spent for all queries: %d", total);
    printf("\nAverage query time: %lf", avg);
    printf("\nProcess Execution Complete");
}

void input(){
    int map,  i, t;
    printf("Enter total no of queries: "); scanf("%d", &n);
    if(n==0) { printf("\n No queries\n"); }
    else{
        printf("\nEnter Quanta for each Process: "); scanf("%d", &quanta);
        printf("\nEnter 1 for faculty and 2 for student\n");
        for(i=0; i<n; i++){
            printf("\nRequest Type (1/2): "); scanf("%d", &map);
            if(map==1){
                f[fc].query_type=map;
                printf("Query Id: "); scanf("%d", &f[fc].process_id);
                printf("Arrival Time: "); scanf("%d", &t);
                if(t<1000 || t>1200){
                    printf("\n Sudesh is not available temp this moment . He is open for queries during 1000hrs to 1200hrs");
                    input();
                }
                else{f[fc].temp= t-1000;}
                printf("Burst Time: "); scanf("%d", &f[fc].burst_time);     f[fc].rburst_time= f[fc].burst_time;
                fc++;
            } else{
                s[sc].query_type=map;
                printf("Query Id: "); scanf("%d", &s[sc].process_id);
                printf("Arrival Time: "); scanf("%d", &t);
                if(t<1000 || t>1200){
                    printf("\n Sudesh is not available temp this moment . He is open for queries during 1000hrs to 1200hrs");
                    input();
                }
                else {s[sc].temp= t-1000; }
                printf("Burst Time: "); scanf("%d", &s[sc].burst_time);     s[sc].rburst_time= s[sc].burst_time;
                sc++;
            }
        }
    }
}

void inst(){
    printf("\t\tWelcome\n**> please follow these instruction for proper functioning of the program"
           "\n**>Enter time in 2400 hours formtemp. example for 12:00 pm enter 1200"
           "\n**>Enter Query arrival times in ascending order, i.e., in real time arrival manner\n"
           "\nAll Time units are in minutes. \n\n"
    );
}

int  main(){
    inst();
    input();
    merger();
    roundRobin();
    printer();
    return 0;
}

