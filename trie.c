#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include <string.h>



Node* newNode(char l){
    Node* n;
    n=(Node*)malloc(sizeof(Node));
    n->count=0;
    n->letter=l;
    for(int i=0;i<NUM_LETTER;i++){
        n->children[i]=NULL;
    }
    return n;
}

void addWord(Node *root,char *word){
 char letter=*word;
 if(letter>='A'&&letter<='Z'){
        letter=letter+'a'-'A';
    }
 else if(letter>='a'&&letter<='z'){

       }
 else {
        printf("the input is illegal\n");
        exit(-1);
    }
    if((strlen(word)-1)==0){
        if(root->children[letter-'a']==NULL){
            Node *temp=NULL;
            temp=newNode(letter);
            root->children[letter-'a']=temp;
            root->children[letter-'a']->count++;
            return;       
        }
        else {
            root->children[letter-'a']->count++;
            return;
        }
     }
    if(root->children[letter-'a']==NULL){
        Node *temp=NULL;
        temp=newNode(letter);//allocate new address
        root->children[letter-'a']=temp;
    }
    word++;//for get the next letter
    addWord(root->children[letter-'a'],word);
    return;
}


void TriePrintUp(Node *root){
    for (int i = 0; i < NUM_LETTER; i++)
    {
        if(root->children[i]!=NULL){
            char str[255];
            str[0]='\0';
            uEachPrint(root->children[i],str);
            strcpy(str,"\0");
            /* code */
        }
    }
}

void uEachPrint(Node *node, char* str){

    if(isLeaf(node)){
        char tmp[2];
        tmp[0]=node->letter;
        tmp[1]='\0';
        char str2[255];
        str2[0]='\0';
        strcpy(str2,str);
        strcat(str2,tmp);
        printf("%s\t%d\n",str2,node->count);
        return;
    }

    char tmp[2];
    tmp[0]=node->letter;
    tmp[1]='\0';
    strcat(str,tmp);

    for (int i = 0; i < NUM_LETTER; i++){
        if(node->children[i]!=NULL){
            if(node->count>0){
                printf("%s\t%d\n",str,node->count);
            }
            char str2[255];
            str2[0]='\0';
            strcpy(str2,str);
            uEachPrint(node->children[i],str2);
        }
    }
    
}

void TriePrintDown(Node *root){
    for (int i = NUM_LETTER-1; i >= 0; i--)
    {
        if(root->children[i]!=NULL){
            char str[255];
            str[0]='\0';
            dEachPrint(root->children[i],str);
            strcpy(str,"\0");
            /* code */
        }
    }
}

void dEachPrint(Node *node, char* str){

    if(isLeaf(node)){
        char tmp[2];
        tmp[0]=node->letter;
        tmp[1]='\0';
        char str2[255];
        str2[0]='\0';
        strcat(str2,str);
        strcat(str2,tmp);
        printf("%s\t%d\n",str2,node->count);
        str[strlen(str)-1]='\0';
        return;
    }

    char tmp[2];
    tmp[0]=node->letter;
    tmp[1]='\0';
    strcat(str,tmp);

    for (int i = NUM_LETTER-1; i >=0; i--){
        if(node->children[i]!=NULL){
            if(node->count>0){
                printf("%s\t%d\n",str,node->count);
            }
            char str2[255];
            str2[0]='\0';
            strcpy(str2,str);
            dEachPrint(node->children[i],str2);
        }
    }
}

boolean isLeaf(Node *n){
    for(int i=0;i<NUM_LETTER;i++){
        if(n->children[i]!=NULL){
            return FALSE;
        }
    }
    return TRUE;
}

char* getWord(char *str){
    char letter;
    int i=0;
    while(scanf("%c",&letter)!=EOF&&letter!='\n'){
        if(letter==','||letter=='.'){
            continue;
        }
        if(letter==' '||letter=='\t'){
            str[i]='\0';
            return str;
        }
        str[i]=letter;
        i++;
    }
    str[i]='\0';
    return str;
}

void freeTrie(Node *root){
    for(int i=0;i<NUM_LETTER;i++){
        if(root->children[i]!=NULL){
            freeTrie(root->children[i]);
        }
    }
    if(root->letter!='*'){
        free(root);
    }
}

int main(int argc, char *argv[]){
    Node *root=newNode('*');
    char word[255];
    getWord(word);
    while(strlen(word)!=0){
        addWord(root,word);
        strcpy(word,getWord(word));
    }

    if(argc==2){
        if(strcmp(argv[1],"r")==0){
            TriePrintDown(root);   
        }    
    }
    else {
        TriePrintUp(root);
    }
    freeTrie(root);
    free(root);
    return 0;
}