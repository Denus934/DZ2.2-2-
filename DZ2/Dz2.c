#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_lenth 32

void terminal(char graph_mode, int num, char names[num][max_lenth], int table[num][num]){
    char string[4000] = {0};
    char arrow[3] = "";

    
    if(graph_mode == 1){
        strcat(string, "digraph G {");
        strcat(arrow, "->");
    } else {
        strcat(string, "graph G {");
        strcat(arrow, "--");
    }

    for(int i=0; i<num; i++){
        strcat(string, names[i]);
        strcat(string, "; ");
    }
    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            for(int k=0; k<table[i][j]; k++){
                strcat(string, names[i]);
                strcat(string, arrow);
                strcat(string, names[j]);
                strcat(string, "; ");
            }
        }
    }
    strcat(string, "}");
    FILE *fp=fopen("graph.dot", "w");

    if(fp == NULL) {
        printf("Unable to create file\n");
        exit(0);
    }
    fputs(string, fp);
    fclose(fp);

}

void PrintTableGraph(int num, char names[num][max_lenth], int table[num][num]){
    printf("\n");
    int graph_check = 1;
    for(int i=0; i<num; i++){
        int temp_graph_check = 0;
        for(int j=0; j<num; j++){
            if(table[i][j] == 1)
                temp_graph_check = 1;
    
            if(table[j][i] == 1)
                temp_graph_check = 1;
        }
        if(temp_graph_check == 0)
            graph_check=0;
    }
    if(graph_check == 0){
        printf("unrelated graph\n");
    } else {
        printf("related graph\n");
    }
    printf("--------------------\n");

    for(int i=0; i<num; i++) {
        printf("%s | ", names[i]);
        for (int j=0; j<num; j++) {
            printf("%d  ", table[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int mode;

    printf("0: graph\n1: digraph\n");
    scanf("%d", &mode);
    
    if( mode != 0 && mode != 1 )
        exit(0);

    printf("elements: ");
    int amount;
    scanf("%d", &amount);
    getchar(); // to ignore \n
    if (amount <= 0)
        exit(0);
    
    printf("ribs: ");
    int ribs;
    scanf("%d", &ribs);
    getchar(); // to ignore \n
    if (amount <= 0)
        exit(0);

    
    char elemetns[amount][max_lenth];
    int graph[amount][amount];
    int matrix[amount][ribs];
    
    for(int i=0; i<amount; i++){
        for(int j=0; j<amount; j++){
            graph[i][j] = 0;
        }
    }
    
    printf("Enter names (less than 32 symb)\n");
    for(int i=0; i<amount; i++){
        printf("%d: ",i+1);
        scanf("%s", elemetns[i]);
        for (int j=0; j<i; j++){
            if( strcmp(elemetns[i], elemetns[j]) == 0 ){
                printf("This name allready exist, enter another\n");
                i--;
            }
        }
    }
    
    getchar(); //from scanf to ignor \n
    
    printf("Enter matrix\n");
    
    for(int i=0; i<amount; i++){
        printf("%s\t", elemetns[i]);
        for(int j=0; j<ribs; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    
    
    int error = 0;
    for(int j=0; j<ribs; j++){
        int first_element = -1, second_element = -1;
        int temp1 = 0, temp2 = 0;
        for(int i=0; i<amount; i++){
            if(matrix[i][j] != 0){
                if(first_element == -1){
                    first_element = i;
                    temp1 = matrix[i][j];
                } else if(second_element == -1){
                    second_element = i;
                    temp2 = matrix[i][j];
                } else {
                    error = 1;
                    j = ribs;
                    i = amount;
                }
            }
        }
        int O = -1;
        if(mode == 0){ //if graph
            O = 1;
        }
        if(first_element != -1 && second_element == -1 && temp1 == 2 && temp2 == 0){
            graph[first_element][first_element] += 1;
        } else if(first_element != -1 && second_element != -1 && temp1 == 1 && temp2 == O){
            graph[first_element][second_element] += 1;
        } else if(first_element != -1 && second_element != -1 && temp1 == O && temp2 == 1){
            graph[second_element][first_element] += 1;
        } else {
            error = 1;
            j = ribs;
        }
    }
    if(error){
        printf("matrix not valid\n");
        exit(9);
    }

    PrintTableGraph(amount, elemetns, graph);
    terminal(mode, amount, elemetns, graph);
    
    return 0;
}
