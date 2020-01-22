#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include <string.h>


/**
 * Function that allocating a new node and return the pointer of this node
 */
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

/**
 * Recursive Function that add a word to the trie tree
 * root - pointer to the root of the tree
 * word - the word you want to add to the trie tree
 */
void addWord(Node *root,char *word){
 char letter=*word;
 if(letter>='A'&&letter<='Z'){
        letter=letter+'a'-'A';//changing upcase to lowcase
    }

 if(!(letter>='a'&&letter<='z')){
        printf("the input is illegal\n");
        exit(-1);
    }
    if((strlen(word)-1)==0){
        if(root->children[letter-'a']==NULL){//this is end of word
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

    if(root->children[letter-'a']==NULL){//not end of word, create new node
        Node *temp=NULL;
        temp=newNode(letter);//allocate new address
        root->children[letter-'a']=temp;
    }

    word++;//for get the next letter
    addWord(root->children[letter-'a'],word);//recurse to the next leter till the end of the word
    return;
}

/**
 * Function that print each groups of words that starts with the same letter
 * increase order
 */ 
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

/**
 * print specific root's children words increase order
 */ 
void uEachPrint(Node *node, char* str){

    if(isLeaf(node)){//end of word
        char tmp[2];
        tmp[0]=node->letter;
        tmp[1]='\0';
        char str2[255];
        str2[0]='\0';
        strcpy(str2,str);
        strcat(str2,tmp);
        printf("%s\t%d\n",str2,node->count);//printing one word and its count
        return;
    }

    char tmp[2];
    tmp[0]=node->letter;//mid word
    tmp[1]='\0';
    strcat(str,tmp);

    for (int i = 0; i < NUM_LETTER; i++){
        if(node->children[i]!=NULL){
            if(node->count>0){
                printf("%s\t%d\n",str,node->count);//end of word but not the most child
            }
            char str2[255];
            str2[0]='\0';
            strcpy(str2,str);
            uEachPrint(node->children[i],str2);//recurse to the next letter
        }
    }
    
}

/**
 * Function that print each groups of words that starts with the same letter
 * decrease order
 */ 
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


/**
 * print specific root's children words decrease order
 */ 
void dEachPrint(Node *node, char* str){

    if(isLeaf(node)){//end of word
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
    tmp[0]=node->letter;//mid word
    tmp[1]='\0';
    strcat(str,tmp);

    for (int i = NUM_LETTER-1; i >=0; i--){
        if(node->children[i]!=NULL){
            if(node->count>0){
                printf("%s\t%d\n",str,node->count);//end of word but not the most child
            }
            char str2[255];
            str2[0]='\0';
            strcpy(str2,str);
            dEachPrint(node->children[i],str2);//recurse to the next letter
        }
    }
}

/**
 * boolean function that checks if node is leaf
 */ 
boolean isLeaf(Node *n){
    for(int i=0;i<NUM_LETTER;i++){
        if(n->children[i]!=NULL){
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * function that return word from buffer, using scanf each char to build that word
 */ 
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
        str[i]=letter;//add each char to the string
        i++;
    }
    str[i]='\0';//end of string
    return str;
}

/**
 * Rcursive function that free each node alocation, except the root
 */ 
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
    Node *root=newNode('*');//creating root to tree
    char word[255];
    getWord(word);//getting the first word inorder to allow get in the while
    while(strlen(word)!=0){
        addWord(root,word);//add word to the trie tree
        strcpy(word,getWord(word));
    }

    if(argc==2){  // for frequency r - decrease order
        if(strcmp(argv[1],"r")==0){
            TriePrintDown(root);   
        }    
    }
    else {  //for frequency - increase order
        TriePrintUp(root);
    }
    freeTrie(root);//free all the childrens
    free(root);//free the root
    return 0;
}