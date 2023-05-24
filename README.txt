CIOBOTEA ALEXANDRU-MARIAN 313AA ACS - IS
TEMA LANPARTY
PROIECTAREA ALGORITMILOR

ALGORITM PENTRU SIMULAREA UNUI TURNEU INTRE ECHIPE

Algoritmul proiectat are ca scop simularea unui turneu intre mai multe echipe prin efectuarea a mai multor meciuri intre echipe pana cand in final ramane un singur castigator.

BEFORE MAIN:
Am definit structura Player necesara conform cerintei problemei ce contine campurile firstName, secondName de tipul char* pentru reprezentarea numelui si a prenumelui unui jucator si campul points de tip int pentru reprezentarea punctajului individual al fiecarui jucator.

Am definit structura Team ce contine structura Player definita anterior, in plus, campurile teamName, numPlayers, teamScore de tipurile char*, int si float ce reprezinta numele unei echipe, numarul de jucatori unei echipe, respectiv scorul final al unei echipe.

Structura Node este folosita pentru a stoca mai multe echipe inspre prelucrare.

In functia addTeam cu parametri head(de tipul Node*) si team(de tipul Team) adaugam un nou nod la inceputul listei head. In functie am alocat dinamic memorie pentru noul nod pe care voiam sa il introducem in lista. Apoi, pentru a putea adauga si alte noduri tot la inceputul listei, nodul adaugat anterior devine capul listei, iar apoi returnam capul listei.

Functia printTeams cu parametri head(de tipul Node*) si ROUT(de tipul FILE*) este o functie care parcurge lista head si afiseaza echipele din lista folosindu-se de o structura repetitiva de tip "while" in care lista este parcursa pana la final si se afiseaza la fiecare pas echipa stocata in acea zona a listei.

Functia freeList cu parametrul head(de tipul Node*) elibereaza memoria alocata pentru campurile listei, deci, pentru lista. Cu o structura repetitiva de tip "while" parcurgem lista de la inceput pana la final, iar la fiecare pas se elibereaza memoria alocata pentru jucatori, pentru numele echipei din care fac parte jucatorii si pentru nodul curent.

In functia calculateTeamScores cu parametrul head de tip Node* se calculeaza punctajul fiecarei echipe stocate in lista head. Se parcurge toata lista de la inceput la final, iar la fiecare pas se parcurge cu un for fiecare membru al echipei din zona curenta a listei, jucator al carui punctaj individual va fi adaugat la variabila locala totalPoints. Dupa ce s-au adunat toate punctajele individuale ale fiecarui jucator din echipa curenta, totalPoints se imparte la numarul total de jucatori din acea echipa pentru a salva in current->team.teamScore media aritmetica a punctajelor individuale. Aceasta medie va reprezenta scorul echipei din zona curenta a listei.

Functia countTeams cu parametrul head de tipul Node* returneaza numarul echipelor din lista head.

Functia removeTeam este o functie care elimina o echipa din lista cu toate componentele ei. Functia este preluata din curs.

Functia delete este o functie care elimina o echipa din lista cu toate componentele ei. Functia este preluata din curs.

Functia de tip bool "isPowerOf2" cu parametru un numar intreg returneaza 1 daca numarul este putere a lui 2, 0 in caz contrar.

Functia removeTeamsWithMinScore cu parametrul head(de tipul Node**) are ca obiectiv eliminarea echipelor din lista head cu punctajul minim pana cand numarul de echipe ramas in lista (determinat la fiecare pas de functia countTeams) este o putere a lui 2. In functie se parcurge lista cat timp nodul curent este diferit de sfarsitul listei si cat timp numarul de echipe din lista nu este putere a lui 2. La fiecare pas se cauta echipa cu scorul minim. Dupa ce este gasita, aceasta va fi eliminata cu ajutorul functiei removeTeam.

Se vor defini structurile necesare pentru simularea meciurilor, si anume structura Match ce contine 2 campuri de tip Team ce vor reprezenta echipele participante la un meci, structura StackNode ce reprezinta o lista populata cu date de tip Team, structura Stack. De asemenea, se vor defini structuri pentru crearea de cozi specifice, structura QueueNode ce contine campul match de tipul Match, structura Queue ce va avea memorate primul si ultimul element al cozii.

Structura createQueue de tipul *Queue aloca memorie pentru coada.

Functia bool isQueueEmpty returneaza 1 daca coada este goala, 0 in caz contrar.

Funcția enqueue(Queue* queue, Match match) adaugă un element la sfârșitul unei cozi. Se aloca memorie pentru un nou nod al cozii, utilizând funcția malloc() și se atribuie adresa de memorie rezultată variabilei newNode. Noul nod newNode este inițializat cu meciul (match) dat ca argument și se setează câmpul next al nodului la NULL. Se verifică dacă coada este goală utilizând funcția isQueueEmpty(queue). Dacă da, înseamnă că este primul element adăugat în coadă și atât front cât și rear vor fi setate să indice către newNode. Dacă coada nu este goală, înseamnă că există deja elemente în coadă. În acest caz, se setează câmpul next al nodului de pe ultima poziție (rear->next) să indice către newNode, iar rear este actualizat să indice newNode. Astfel, fiecare element adăugat în coadă prin funcția enqueue() este plasat corect la sfârșitul cozii, iar rear este actualizată corespunzător pentru a indica către ultimul element adăugat.

Funcția dequeue(Queue* queue) extrage și elimină primul element dintr-o coadă și îl returnează. Se verifică dacă coada este goală utilizând funcția isQueueEmpty(queue). Dacă este goală, se afișează un mesaj de eroare cu ajutorul funcției printf() și se încheie programul cu exit(EXIT_FAILURE), semnalând astfel o eroare. Se obține nodul de pe poziția front al cozii și se atribuie adresa acestuia variabilei frontNode. Meciul (match) din nodul frontNode este atribuit variabilei match. Se actualizează front să indice următorul nod din coadă (queue->front->next). Astfel, primul element din coadă este eliminat. Se verifică dacă front a devenit NULL, ceea ce înseamnă că coada a devenit goală după eliminarea primului element. În acest caz, și rear este actualizată să fie NULL. Se eliberează memoria alocată pentru nodul frontNode folosind funcția free(). Se returnează meciul (match) extras din coadă. Astfel, funcția dequeue() extrage și elimină primul element din coadă și îl returnează, asigurându-se că coada este actualizată corect pentru următoarele operații.

Functia freeQueue elibereaza memoria alocata pentru o coada de tipul Queue*.

Functia createStack aloca memorie pentru o stiva implementata cu ajutorul unei liste de tip Stack*, lista pe care o returneaza.

Functia bool isStackEmpty returneaza 1 daca stiva este goala sau 0 daca stiva are macar un element.

Functia push aloca memorie pentru un nod nou in stiva stack si il populeaza cu datele din variabila team, pe cand functia pop elimina o echipa din stiva.

freeStack este functia care elibereaza memoria alocata pentru stiva.

Functia createMatches parcurge lista cu echipe din 2 in 2, iar la fiecare pas plaseaza in cate un nod al cozii queue doua echipe care vor efectua meciuri intre ele.

Functia showStack este functia care afiseaza stiva de echipe din fisierul de echipe.

addMatchToList este functia care adauga echipele dintr-un meci in lista de echipe.

In functia processMatches se vor efectua meciurile pana cand ramane o singura echipa, aceea fiind castigatorea. Cat timp sunt mai mult de 2 echipe in turneu, se va afisa runda, iar cst timp coada de meciuri are cel putin un element, se vor afisa echipele care se joaca in formatul cerut in cerinta. Verifivam ce echipa a castigat meciul prin compararea scorurilor echipelor concurente. Castigatorului ii incrementam scorul cu 1 si il adaugam in stiva cu invingatori, iar echipa ce a pierdut este adaugata in stiva cu invinsi. Dupa efectuarea tuturor meciurilor, numarul de echipe ramase scade cu jumatate. Daca numarul de echipe ramase este mai mare decat 1, afisam castigatorii rundei respective. Se vor adauga castigatorii in coada de meciuri pentru runda urmatoare.

Functia showList afiseaza topul primelor 8 echipe din clasament dupa efectuarea meciurilor.

Pentru cerinta 4, a fost nevoie de o structura specifica unui arbore de tip BST.

Functia newNode de tip BSTNode* este preluata din curs si aloca memorie pentru un nou nod in arbore, ce este populat ulterior cu variabila de tip Teamm data.

Este folosita functia de inserare a unui nod in arbore BST precum cea de la curs.

Functia sortTeams sorteaza o lista de echipe prioritar descrescator dupa scor, dar in cazul in care 2 echipe au acelasi scor, se vor sorta descrescator dupa nume.

Pentru cerinta 5, s-a folosit o structura care defineste un arbore de tip AVL. 

Functia createAVLNode aloca memorie pentru un nod intr-o lista de tip AVLNode si populeaza nodul cu datele variabilei Team team.

Functia height returneaza inaltimea arborelui AVL din antet.

Functia getBalance este functia care calculeaza diferenta de inaltime intre subarborii unui arbore AVL.

Functia maxx returneaza maximul dintre 2 intregi a si b.

S-au definit apoi functiile specifice de rotatie la stanga sau la dreapta intr-un arbore de tip AVL.

Functia de inserare a unui nod in AVL este similara cu cea intr-un BST. In aceasta functie am actualizat inaltimea arborelui la fiecare adaugare a unui nod. Dupa incepe etapa de echilibrare a arborelui pentru ca arborele sa fie adus in forma echilibrata prin tratarea fiecarei posibilitati.

Am folosit functia convertBSTListToAVLList pentru un arbore BST pentru a-l transforma intr-unul de tip AVL. 

Functia printLevel afiseaza in fisierul de iesire numele echipelor aflate la nivelul level in arborele AVL.

IN MAIN:

In main se initializeaza o lista numita head de tipul Node* pentru echipe.

Se citesc din fisierul de intrare numele echipelor si toate informatiile despre acestea si se adauga in lista head.

Se apeleaza functia calculateTeamScores(head) pentru a determina punctajele fiecarei echipa din lista.

Pentru task-ul 1 se afiseaza echipele din lista cu functia printTeams(head, ROUT).

Pentru task-ul 2 se elimina echipele cu punctaj minim pana cand numarul de echipe ramane o putere a lui 2, apoi se afiseaza in fisierul de iesire echipele ramase cu functia printTeams(head, ROUT).

Pentru task-ul 3, se creeaza meciurile si se adauga in coada. Se va realiza un clasament al ultimelor 8 echipe.

Pentru task-ul 4 se vor sorta echipele descrescator si se vor adauga intr-un arbore BST ce se va afisa in fisierul de iesire.

Pentru task-ul 5 se va converti arborele BST de la task-ul 4 intr-un arbore de tip AVL si se vor afisa echipele de pe nivelul al arborelui.

