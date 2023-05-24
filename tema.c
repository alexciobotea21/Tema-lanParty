#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
} Player;

typedef struct Team
{
    Player* players;
    char* teamName;
    int numPlayers;
    float teamScore;
} Team;

typedef struct Node
{
    Team team;
    struct Node* next;
} Node;


// Funcție pentru a adăuga un nou nod la începutul listei
Node* addTeam(Node* head, Team team)
{
    // Alocă memorie pentru noul nod
    Node* newNode = (Node*)malloc(sizeof(Node));

    // Setează informațiile echipei în noul nod
    newNode->team = team;
    // Noul nod devine capul listei
    newNode->next = head;

    // Returnează noul cap al listei
    return newNode;
}

// Funcție pentru a accesa și afișa echipele din listă
void printTeams(Node* head, FILE *ROUT)
{
    Node* current = head;

    while (current != NULL)
    {
        fprintf(ROUT, "%s\n", current->team.teamName);
        current = current->next;
    }
}


// Funcție pentru a elibera memoria alocată pentru lista
void freeList(Node* head)
{
    Node* current = head;

    while (current != NULL)
    {

        Node* next = current->next;

        // Eliberează memoria pentru jucători
        free(current->team.players);

        // Eliberează memoria pentru numele echipei
        free(current->team.teamName);

        // Eliberează memoria pentru nodul curent
        free(current);

        // Mergi la următorul nod din listă
        current = next;
    }
}

void calculateTeamScores(Node* head)
{
    Node* current = head;

    while (current != NULL)
    {
        int i;
        int totalPoints = 0;

        for (i = 0; i < current->team.numPlayers; i++)
        {
            totalPoints += current->team.players[i].points;
        }

        current->team.teamScore = (float)totalPoints / current->team.numPlayers;

        current = current->next;
    }
}

int countTeams(Node* head)
{
    Node* current = head;
    int count = 0;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

void removeTeam(Node** head, Node** prev, Node* curr)
{
    if (*prev == NULL)
    {
        *head = curr->next;
    }
    else
    {
        (*prev)->next = curr->next;
    }

    free(curr->team.teamName);

    int i;
    for (i = 0; i < curr->team.numPlayers; i++)
    {
        free(curr->team.players[i].firstName);
        free(curr->team.players[i].secondName);
    }

    free(curr->team.players);
    free(curr);
}

bool isPowerOf2(int num)
{
    while (num % 2 == 0)
        num/=2;
    if (num == 1)
        return 1;
    return 0;
}
void removeTeamsWithMinScore(Node** head)
{

    while (*head != NULL && isPowerOf2(countTeams(*head)) == 0)
    {
        float minScore = INFINITY;

        Node* minScoreTeam = NULL;

        // Găsește echipa cu cel mai mic punctaj
        Node* prev = NULL;
        Node* temp = *head;
        minScore = temp->team.teamScore;
        minScoreTeam = temp;
        while(temp->next != NULL)
        {
            if(temp->next->team.teamScore < minScore)
            {
                prev = temp;
                minScore = temp->next->team.teamScore;
                minScoreTeam = temp->next;
            }
            temp = temp->next;
        }

        if (minScoreTeam != NULL)
        {
            removeTeam(head, &prev, minScoreTeam);
        }
    }
}

typedef struct Match
{
    Team team1;
    Team team2;
} Match;

typedef struct StackNode
{
    Team team;
    struct StackNode* next;
} StackNode;

typedef struct Stack
{
    StackNode* top;
} Stack;

typedef struct QueueNode
{
    Match match;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue
{
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

bool isQueueEmpty(Queue* queue)
{
    return queue->front == NULL;
}

void enqueue(Queue* queue, Match match)
{
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->match = match;
    newNode->next = NULL;

    if (isQueueEmpty(queue))
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Match dequeue(Queue* queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Error: Queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    QueueNode* frontNode = queue->front;
    Match match = frontNode->match;

    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(frontNode);
    return match;
}

void freeQueue(Queue* queue)
{
    while (!isQueueEmpty(queue))
    {
        dequeue(queue);
    }
    free(queue);
}

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

bool isStackEmpty(Stack* stack)
{
    return stack->top == NULL;
}

void push(Stack* stack, Team team)
{
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->team = team;
    newNode->next = stack->top;
    stack->top = newNode;
}

Team pop(Stack* stack)
{
    if (isStackEmpty(stack))
    {
        printf("Error: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    StackNode* topNode = stack->top;
    Team team = topNode->team;

    stack->top = stack->top->next;
    free(topNode);
    return team;
}

void freeStack(Stack* stack)
{
    while (!isStackEmpty(stack))
    {
        pop(stack);
    }
    free(stack);
}

//Functie care creaza meciurile din lista de echipe si le adauga in coada
void createMatches(Node* head, Queue* queue)
{
    Node* current = head;

    while (current != NULL && current->next != NULL)
    {
        Match match;
        match.team1 = current->team;
        match.team2 = current->next->team;

        enqueue(queue, match);

        current = current->next->next;
    }
}

//Functie care afiseaza stiva de echipe in fisierul de iesire
void showStack(Stack* stack, FILE* ROUT)
{
    StackNode* current = stack->top;
    while (current != NULL)
    {
        fprintf(ROUT, "%-34s-  %4.2f\n", current->team.teamName, current->team.teamScore);
        current = current->next;
    }
}

//Functie care adauga echipele dintr-un meci in lista de echipe
void addMatchToList(Node** head, Match match)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->team = match.team1;
    newNode->next = NULL;
    ///daca lista e goala se adauga prima echipa
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        //altfel lista se parcurge pana la ultimul element si se adauga echipa
        Node* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    //se adauga si a doua echipa
    newNode = (Node*)malloc(sizeof(Node));
    newNode->team = match.team2;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void processMatches(Queue* queue, Stack* winnersStack, Stack* losersStack, Node **last8, int *remainingTeams, FILE* ROUT)
{
    fprintf(ROUT, "\n");
    int round = 1;
    //cat timp mai sunt echipe in turneu
    while(*remainingTeams >= 2)
    {
        //afisare runda
        fprintf(ROUT, "--- ROUND NO:%d\n", round);
        while (!isQueueEmpty(queue))
        {
            Match match = dequeue(queue);
            //afisare echipele care se joaca cu formatul cerut "TOUCANS                          -                      TERMINATORS" in fisier
            fprintf(ROUT, "%-33s-%33s\n", match.team1.teamName, match.team2.teamName);
            // Verificăm care echipă a câștigat meciul
            Team winner, loser;
            if (match.team1.teamScore > match.team2.teamScore)
            {
                winner = match.team1;
                loser = match.team2;
            }
            else
            {
                winner = match.team2;
                loser = match.team1;
            }
            // Incrementam scorul câștigătorului
            winner.teamScore += 1;
            // Adăugăm echipele în stivele corespunzătoare
            push(winnersStack, winner);
            push(losersStack, loser);
        }
        //numarul de echipe ramase scade la jumatate
        *remainingTeams /= 2;

        if(*remainingTeams > 1)
        {
            ///afisare echipele care au castigat runda
            fprintf(ROUT, "\n");
            fprintf(ROUT, "WINNERS OF ROUND NO:%d\n", round);
            showStack(winnersStack, ROUT);
            fprintf(ROUT, "\n");


            //adauga castigatorii in coada pentru urmatoarea runda
            while (!isStackEmpty(winnersStack))
            {
                Match winner;
                winner.team1 = pop(winnersStack);
                winner.team2 = pop(winnersStack);
                //adaugam castigatorii in lista pentru ultimele 8 echipe
                if(*remainingTeams == 8)
                {
                    addMatchToList(last8, winner);
                }

                enqueue(queue, winner);
            }
            round++;
        }
        else
        {
            fprintf(ROUT, "\n");
            fprintf(ROUT, "WINNERS OF ROUND NO:%d\n", round);
            showStack(winnersStack, ROUT);
        }
    }
}

//Afisarea ultimelor 8 echipe
void showList(Node *head, FILE *ROUT)
{
    fprintf(ROUT, "\n");
    while(head != NULL)
    {
        fprintf(ROUT, "%-34s-  %4.2f\n", head->team.teamName, head->team.teamScore);
        head = head->next;
    }
}

//BSTNODE
typedef struct bstnode
{
    Team team;
    struct bstnode *left, *right;
} BSTNode;

//functie de creare a unui nod
BSTNode *newNode(Team data)
{
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    node->team = data;
    node->left = node->right = NULL ;
    return node ;
}

//functie de afisare in fisier a BST
void printBST(BSTNode *root, FILE *ROUT)
{
    if (root != NULL)
    {
        printBST(root->right, ROUT);
        fprintf(ROUT, "%-34s-  %4.2f\n", root->team.teamName, root->team.teamScore);
        printBST(root->left, ROUT);
    }
}

//funcție de inserare in BST
BSTNode* insert(BSTNode *node,Team key)
{
    //daca nodul este null, il creez
    if (node == NULL) return newNode (key);
    //daca scorul echipei este mai mic sau egal decat scorul nodului, inserez in stanga
    if (key.teamScore <= node->team.teamScore)
        node->left = insert( node->left, key);
    else//altfel inserez in dreapta
        node->right = insert(node->right, key);
    return node;
}

//sorteaza descrescator echipele dupa scor si nume
void sortTeams(Node* team)
{
    Node* i, *j;
    Team aux;
    for(i = team; i != NULL; i = i->next)
        for(j = i->next; j != NULL; j = j->next)
            //sortare descrescatoare dupa scor
            if(i->team.teamScore < j->team.teamScore)
            {
                aux = i->team;
                i->team = j->team;
                j->team = aux;
            }
            else if(i->team.teamScore == j->team.teamScore)
            {
                //sortare descrescător după nume
                if(strcmp(i->team.teamName, j->team.teamName) < 0)
                {
                    aux = i->team;
                    i->team = j->team;
                    j->team = aux;
                }
            }
}

typedef struct avlnode
{
    Team team;
    int height;
    struct avlnode *left, *right;
} AVLNode;

AVLNode* createAVLNode(Team team)
{
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->team = team;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int height(AVLNode* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Funcție pentru a calcula diferența de înălțime între subarborii unui nod AVL
int getBalance(AVLNode* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

int maxx(int a, int b)
{
    return (a > b) ? a : b;
}


AVLNode* rotateLeft(AVLNode* node)
{
    AVLNode* newRoot = node->right;
    AVLNode* newLeftSubtree = newRoot->left;

    newRoot->left = node;
    node->right = newLeftSubtree;

    // Actualizarea înălțimilor
    node->height = 1 + maxx(height(node->left), height(node->right));
    newRoot->height = 1 + maxx(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

// Funcție pentru a roti în dreapta subarborele cu rădăcina dată
AVLNode* rotateRight(AVLNode* node)
{
    AVLNode* newRoot = node->left;
    AVLNode* newRightSubtree = newRoot->right;

    newRoot->right = node;
    node->left = newRightSubtree;

    // Actualizarea înălțimilor
    node->height = 1 + maxx(height(node->left), height(node->right));
    newRoot->height = 1 + maxx(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

AVLNode* insertAVLNode(AVLNode* root, Team team)
{
    // Pasul de inserare similar cu inserarea într-un BST obișnuit
    if (root == NULL)
        return createAVLNode(team);

    if (team.teamScore < root->team.teamScore)
        root->left = insertAVLNode(root->left, team);
    else if (team.teamScore > root->team.teamScore)
        root->right = insertAVLNode(root->right, team);
    else
        return root; // Nodurile cu același scor nu sunt permise în AVL

    // Actualizarea înălțimii
    root->height = 1 + maxx(height(root->left), height(root->right));

    // Echilibrarea arborelui
    int balance = getBalance(root);

    // Cazul 1: Nodul devine neechilibrat în stânga-stânga
    if (balance > 1 && team.teamScore < root->left->team.teamScore)
        return rotateRight(root);

    // Cazul 2: Nodul devine neechilibrat în dreapta-dreapta
    if (balance < -1 && team.teamScore > root->right->team.teamScore)
        return rotateLeft(root);

    // Cazul 3: Nodul devine neechilibrat în stânga-dreapta
    if (balance > 1 && team.teamScore > root->left->team.teamScore)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Cazul 4: Nodul devine neechilibrat în dreapta-stânga
    if (balance < -1 && team.teamScore < root->right->team.teamScore)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

AVLNode* convertBSTListToAVLList(BSTNode* bstList)
{
    AVLNode* avlList = NULL;
    BSTNode* current = bstList;

    while (current != NULL)
    {
        avlList = insertAVLNode(avlList, current->team);
        current = current->right;
    }

    return avlList;
}

void printLevel(AVLNode* root, int level, FILE *ROUT)
{
    if (root == NULL)
        return;
    if (level == 1) fprintf(ROUT, "%s\n", root->team.teamName);
    else if (level > 1)
    {
        printLevel(root->left, level-1, ROUT);
        printLevel(root->right, level-1, ROUT);
    }
}
int main(int argc, char *argv[])
{
    Node* head = NULL; // Capul listei

    // Creați și adăugați echipe în listă

    FILE *CIN = fopen(argv[1], "rt"), *DIN = fopen(argv[2], "rt"), *ROUT = fopen(argv[3], "wt");

    int task[5], i = 0, j;
    while(!feof(CIN))
        fscanf(CIN, "%d", &task[i++]);

    int teams;
    fscanf(DIN, "%d", &teams);

    Team team;
    for(i = 0; i < teams; i++)
    {
        char ceva;
        fscanf(DIN, "%d%c", &team.numPlayers, &ceva);
        team.teamName = (char*)malloc(100 * sizeof(char));
        fgets(team.teamName, 100, DIN);
        //stergere caracterul \n
        team.teamName[strlen(team.teamName) - 2] = '\0';
        //sterge spatiul de la final
        if(team.teamName[strlen(team.teamName) - 1] == ' ')
            team.teamName[strlen(team.teamName) - 1] = '\0';

        team.players = (Player*)malloc(team.numPlayers * sizeof(Player));

        for(j = 0; j < team.numPlayers; j++)
        {
            team.players[j].firstName = (char*)malloc(100 * sizeof(char));
            fscanf(DIN, "%s%c", team.players[j].firstName, &ceva);
            team.players[j].secondName = (char*)malloc(100 * sizeof(char));
            fscanf(DIN, "%s%c", team.players[j].secondName, &ceva);
            fscanf(DIN, "%d", &team.players[j].points);
        }

        head = addTeam(head, team);
    }

    //calculeaza punctajul fiecarei echipe
    calculateTeamScores(head);

    if(task[0] == 1 && task[1] == 0)
    {
        // Afișați echipele din listă
        printTeams(head, ROUT);
    }
    else if(task[1])
    {
        //Elimină echipele cu punctaj minim
        removeTeamsWithMinScore(&head);

        // Afișează echipele rămase
        printTeams(head, ROUT);
    }
    // Creați meciurile și adăugați-le în coadă
    Node* last8 = NULL;
    int remainingTeams = countTeams(head);
    if(task[2])
    {
        Queue* matchQueue = createQueue();
        Stack* winnersStack = createStack();
        Stack* losersStack = createStack();
        createMatches(head, matchQueue);
        processMatches(matchQueue, winnersStack, losersStack, &last8, &remainingTeams, ROUT);

    }
    //Se va realiza un clasament al ultimelor 8 echipe (salvate la subpunctul anterior) sub forma unui BST(Binary Search Tree). Acesta va fi ordonat după punctajul pe echipă și i se va afișa conținutul în ordine descrescătoare(in cazul in care doua echipe au acelasi punctaj se vor ordona in functie de nume, descrescator).
    if(task[3])
    {
        BSTNode* root = NULL;

        //sortare dupa punctaj și nume descrescator
        sortTeams(last8);
        while(last8 != NULL)
        {
            //adăugare in BST
            root = insert(root, last8->team);
            last8 = last8->next;
        }

        //afisare BST
        fprintf(ROUT, "\nTOP 8 TEAMS:\n");
        printBST(root, ROUT);
    }

    if (task[4])
    {
        fprintf(ROUT, "\nTHE LEVEL 2 TEAMS ARE:\n");

        BSTNode* root = NULL;

        //sortare dupa punctaj și nume descrescator
        sortTeams(last8);
        while(last8 != NULL)
        {
            //adăugare in BST
            root = insert(root, last8->team);
            last8 = last8->next;
        }

        AVLNode* dest = NULL;
        dest = convertBSTListToAVLList(root);

        printLevel(dest,2,ROUT);
    }

    freeList(head);

    return 0;
}
