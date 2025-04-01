#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

#define MAX_QUESTIONS 50
#define QUESTIONS_PER_GAME 10
#define POINTS_PER_QUESTION 50
#define RANK_POINTS 500
#define SAVE_FILE "cybersecurity_quiz_save.dat"

typedef struct {
    int id;
    char question[500];
    char options[4][200];
    char correct_answer;
    char section[100];
} Question;

typedef struct {
    char name[50];
    int total_points;
    int rank;
    int questions_answered;
    int correct_answers;
} Player;

Question questions[MAX_QUESTIONS];
int total_questions = 0;

Player current_player;
char ranks[][30] = {
    "Novizio",
    "Apprendista",
    "Esploratore",
    "Specialista",
    "Esperto",
    "Maestro",
    "Guru",
    "Hacker Leggendario"
};
int total_ranks = sizeof(ranks)/sizeof(ranks[0]);

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void wait_for_enter() {
    printf("\nPremi Invio per continuare...");
    while(getchar() != '\n');
}

void load_questions() {
    // Section 1: Cybersecurity Fundamentals
    questions[total_questions++] = (Question){1, "Quale tra i seguenti è un principio fondamentale della sicurezza informatica?", 
        {"Accessibilità, Disponibilità, Affidabilità", "Riservatezza, Integrità, Disponibilità", 
         "Performance, Efficienza, Cifratura", "Affidabilità, Riconoscimento, Replicazione"}, 'B', "Fondamenti di Cybersecurity"};
    
    questions[total_questions++] = (Question){2, "Cosa rappresenta un attacco di tipo \"Man-in-the-Middle\" (MitM)?", 
        {"Un hacker che intercetta la comunicazione tra due entità per spiarla o modificarla", "Un malware che cripta i file di un utente richiedendo un riscatto", 
         "Un attacco DoS per bloccare un sito web", "Un tentativo di phishing per rubare credenziali"}, 'A', "Fondamenti di Cybersecurity"};
    
    questions[total_questions++] = (Question){3, "Qual è la differenza tra autenticazione e autorizzazione?", 
        {"L'autenticazione verifica l'identità, l'autorizzazione controlla i permessi", "L'autorizzazione viene prima dell'autenticazione", 
         "Sono due concetti equivalenti", "L'autenticazione è usata solo nelle reti Wi-Fi"}, 'A', "Fondamenti di Cybersecurity"};
    
    questions[total_questions++] = (Question){4, "Qual è lo scopo di un penetration test?", 
        {"Attaccare un sistema per comprometterlo", "Individuare e correggere vulnerabilità di sicurezza", 
         "Analizzare le prestazioni di un sistema informatico", "Installare software di monitoraggio"}, 'B', "Fondamenti di Cybersecurity"};
    
    questions[total_questions++] = (Question){5, "Quale livello del modello OSI gestisce il routing dei pacchetti?", 
        {"Trasporto", "Rete", 
         "Collegamento Dati", "Sessione"}, 'B', "Fondamenti di Cybersecurity"};

    // Section 2: Cryptography and Data Security
    questions[total_questions++] = (Question){6, "Qual è la differenza tra crittografia simmetrica e asimmetrica?", 
        {"La simmetrica usa una chiave per cifrare e decifrare, l'asimmetrica ne usa due", "La crittografia simmetrica è più lenta", 
         "L'asimmetrica non usa chiavi ma solo hash", "Sono la stessa cosa"}, 'A', "Crittografia e Sicurezza dei Dati"};
    
    questions[total_questions++] = (Question){7, "Cos'è il plaintext?", 
        {"Testo cifrato che necessita di una chiave per essere letto", "Un tipo di hashing usato nei database", 
         "Testo non crittografato, leggibile senza decodifica", "Un attacco basato sulla sostituzione di caratteri"}, 'C', "Crittografia e Sicurezza dei Dati"};
    
    questions[total_questions++] = (Question){8, "Quale algoritmo è considerato più sicuro per l'hashing delle password?", 
        {"MD5", "SHA-1", 
         "bcrypt", "Base64"}, 'C', "Crittografia e Sicurezza dei Dati"};
    
    questions[total_questions++] = (Question){9, "Quale metodo di autenticazione è considerato più sicuro?", 
        {"Password semplice", "Autenticazione a due fattori (2FA)", 
         "Autenticazione via email", "Nessuno è sicuro"}, 'B', "Crittografia e Sicurezza dei Dati"};

    // Section 3: Malware and Attacks
    questions[total_questions++] = (Question){10, "Cos'è un ransomware?", 
        {"Un tipo di spyware che raccoglie informazioni sugli utenti", "Un malware che cripta i dati della vittima e chiede un riscatto per il loro recupero", 
         "Un virus che si replica automaticamente", "Un software per proteggere i dati"}, 'B', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){11, "Cosa fa un Trojan Horse?", 
        {"Cattura le sequenze di tasti premuti dall'utente", "Intercetta il traffico di rete", 
         "Nasconde un malware all'interno di un programma apparentemente legittimo", "Blocca l'accesso alla rete"}, 'C', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){12, "Cos'è il phishing?", 
        {"Un attacco DoS per sovraccaricare un server", "Una tecnica per rubare credenziali attraverso email o siti web falsi", 
         "Un metodo di cifratura", "Un attacco fisico ai server"}, 'B', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){13, "Come si chiama un malware che si attiva solo in determinate condizioni?", 
        {"Worm", "Keylogger", 
         "Logic Bomb", "Spyware"}, 'C', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){14, "Cos'è un rootkit?", 
        {"Un software che permette di ottenere accesso amministrativo nascosto", "Un tipo di antivirus avanzato", 
         "Un tool per crittografare i file di un sistema operativo", "Un attacco di tipo phishing"}, 'A', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){15, "Cosa fa un keylogger?", 
        {"Registra tutte le sequenze di tasti premute dall'utente", "Esegue attacchi DDoS automaticamente", 
         "Blocca l'accesso a siti web specifici", "Protegge le password tramite autenticazione a due fattori"}, 'A', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){16, "Quale di questi è un attacco di social engineering?", 
        {"SQL Injection", "Phishing", 
         "Attacco brute-force", "Exploit zero-day"}, 'B', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){17, "Qual è l'obiettivo principale di un attacco DoS (Denial of Service)?", 
        {"Ottenere credenziali di accesso", "Impedire il funzionamento di un servizio o di un sito web", 
         "Intercettare il traffico di rete", "Criptare i file della vittima"}, 'B', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){18, "Un attacco di smishing sfrutta principalmente:", 
        {"Email con allegati infetti", "Messaggi SMS per ingannare gli utenti", 
         "Exploit nei sistemi operativi", "Router compromessi"}, 'B', "Malware e Attacchi"};
    
    questions[total_questions++] = (Question){19, "Quale tra questi è un esempio di spyware?", 
        {"Un programma che raccoglie informazioni sugli utenti e le invia a terze parti", "Un malware che cripta i dati e richiede un riscatto", 
         "Un attacco contro il protocollo WPA2", "Un software che impedisce la connessione a Internet"}, 'A', "Malware e Attacchi"};

    // Section 4: Networks and Security Protocols
    questions[total_questions++] = (Question){20, "Cos'è un proxy?", 
        {"Un dispositivo hardware che intercetta e manipola il traffico web", "Un server che funge da intermediario tra client e Internet", 
         "Un malware che nasconde la connessione Internet di un utente", "Un software di protezione contro phishing e ransomware"}, 'B', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){21, "Qual è la funzione principale di un firewall?", 
        {"Bloccare automaticamente tutti i pacchetti di rete", "Analizzare e filtrare il traffico di rete in base a regole predefinite", 
         "Proteggere il sistema da attacchi fisici", "Nascondere l'indirizzo IP dell'utente"}, 'B', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){22, "Quali azioni può compiere un firewall sulle connessioni di rete?", 
        {"Allow, Drop, Deny", "Accept, Encrypt, Block", 
         "Monitor, Delete, Control", "Scan, Filter, Redirect"}, 'A', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){23, "Qual è la differenza tra una chiave crittografica simmetrica e asimmetrica?", 
        {"La chiave simmetrica usa una chiave unica per cifrare e decifrare, l'asimmetrica utilizza due chiavi distinte", "La chiave asimmetrica è più veloce della simmetrica", 
         "La chiave simmetrica è usata solo per i certificati SSL/TLS", "Non c'è differenza, entrambi i sistemi funzionano allo stesso modo"}, 'A', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){24, "Cos'è il plaintext?", 
        {"Un testo crittografato che necessita di una chiave per essere letto", "Un tipo di attacco basato sulla sostituzione di caratteri", 
         "Un testo in chiaro non crittografato", "Un malware che intercetta le comunicazioni"}, 'C', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){25, "Il ciphertext è:", 
        {"Un testo cifrato non leggibile senza chiave", "Un tipo di firewall avanzato", 
         "Un metodo di compressione dei dati", "Un attacco DoS"}, 'A', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){26, "Qual è la funzione di un hash crittografico?", 
        {"Crittografare e decrittografare i dati", "Generare una rappresentazione univoca di un file o testo", 
         "Bloccare attacchi di phishing", "Stabilire connessioni sicure su reti Wi-Fi"}, 'B', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){27, "Il 3-Way Handshake è un meccanismo di:", 
        {"Autenticazione utente", "Crittografia avanzata", 
         "Stabilimento di connessioni TCP sicure", "Monitoraggio delle comunicazioni"}, 'C', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){28, "Qual è lo scopo principale del protocollo TLS?", 
        {"Rendere più veloce la trasmissione dei dati", "Proteggere la comunicazione tra client e server attraverso crittografia", 
         "Bloccare il traffico non autorizzato su una rete", "Analizzare pacchetti di rete"}, 'B', "Reti e Protocolli di Sicurezza"};
    
    questions[total_questions++] = (Question){29, "Quale di questi algoritmi è considerato un sistema di crittografia simmetrica?", 
        {"RSA", "AES", 
         "SHA-256", "MD5"}, 'B', "Reti e Protocolli di Sicurezza"};

    // Section 5: Network and System Security
    questions[total_questions++] = (Question){30, "Cos'è il port scanning?", 
        {"Una tecnica per analizzare quali porte di un sistema sono aperte o chiuse", "Un metodo di autenticazione a due fattori", 
         "Un sistema di protezione avanzato contro il phishing", "Un attacco DoS che sfrutta le porte vulnerabili"}, 'A', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){31, "Un attacco Man-in-the-Middle (MitM) avviene quando:", 
        {"L'attaccante intercetta e modifica la comunicazione tra due dispositivi", "Si verifica un errore nel DNS che impedisce la connessione", 
         "Un utente viene ingannato con un'email di phishing", "Il firewall blocca le connessioni non autorizzate"}, 'A', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){32, "Quale tra questi protocolli viene utilizzato per l'invio delle email?", 
        {"HTTP", "SMTP", 
         "SNMP", "ARP"}, 'B', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){33, "In una rete, un attacco di ARP Spoofing permette di:", 
        {"Modificare i pacchetti di dati crittografati", "Fingere di essere un altro dispositivo della rete per intercettare il traffico", 
         "Nascondere l'indirizzo IP del mittente", "Creare un punto di accesso Wi-Fi malevolo"}, 'B', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){34, "Cos'è un honeypot?", 
        {"Un attacco brute-force avanzato", "Un sistema creato per attirare gli attaccanti e studiare i loro metodi", 
         "Un algoritmo di crittografia per proteggere i file", "Un sistema firewall avanzato"}, 'B', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){35, "L'autenticazione a due fattori (2FA) fornisce maggiore sicurezza perché:", 
        {"Richiede sempre una password più lunga", "Aggiunge un ulteriore livello di verifica, come un codice OTP", 
         "Crittografa automaticamente i dati degli utenti", "Permette il login automatico senza credenziali"}, 'B', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){36, "Quale strumento è usato per analizzare il traffico di rete?", 
        {"Wireshark", "Metasploit", 
         "Nmap", "John the Ripper"}, 'A', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){37, "Qual è il principale compito di un IDS (Intrusion Detection System)?", 
        {"Bloccare automaticamente le connessioni malevoli", "Analizzare il traffico e segnalare attività sospette", 
         "Crittografare le email inviate da una rete aziendale", "Monitorare le password degli utenti"}, 'B', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){38, "Quale tra questi firewall analizza lo stato delle connessioni?", 
        {"Firewall a pacchetti", "Firewall stateless", 
         "Firewall stateful", "Firewall open-source"}, 'C', "Sicurezza delle Reti e dei Sistemi"};
    
    questions[total_questions++] = (Question){39, "Una DMZ (Demilitarized Zone) è:", 
        {"Una rete isolata dalla rete interna e da Internet per proteggere i servizi pubblici", "Un server utilizzato per inviare spam", 
         "Una rete che blocca automaticamente gli attacchi brute-force", "Un tool di sniffing del traffico di rete"}, 'A', "Sicurezza delle Reti e dei Sistemi"};

    // Section 6: Cryptography and Hashing
    questions[total_questions++] = (Question){40, "SHA-256 è un algoritmo di:", 
        {"Crittografia simmetrica", "Hashing", 
         "Compressione dei dati", "Firewall"}, 'B', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){41, "Quale tra questi algoritmi utilizza chiavi pubbliche e private?", 
        {"AES", "RSA", 
         "MD5", "SHA-256"}, 'B', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){42, "L'hashing dei dati garantisce:", 
        {"La protezione contro il phishing", "L'integrità dei dati", 
         "La protezione dei sistemi informatici da DDoS", "La cifratura end-to-end"}, 'B', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){43, "Cosa significa hardening di un sistema operativo?", 
        {"Rimuovere software superflui e applicare configurazioni di sicurezza avanzate", "Installare un antivirus per proteggere il sistema", 
         "Usare firewall per filtrare le connessioni", "Bloccare tutti i processi non essenziali"}, 'A', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){44, "I sistemi di autenticazione biometrici utilizzano:", 
        {"Codici PIN univoci", "Riconoscimento facciale, impronte digitali o scansione dell'iride", 
         "Domande di sicurezza preimpostate", "Password lunghe almeno 12 caratteri"}, 'B', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){45, "Quale tecnica viene utilizzata per proteggere la comunicazione su reti mobili?", 
        {"VPN (Virtual Private Network)", "WEP (Wired Equivalent Privacy)", 
         "Utilizzo di porte alternative per le connessioni HTTP", "Autenticazione solo con username e password"}, 'A', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){46, "Quale metodo di protezione aiuta a prevenire gli attacchi CSRF (Cross-Site Request Forgery)?", 
        {"Disabilitare i cookie del browser", "Utilizzare token CSRF per verificare le richieste", 
         "Implementare una VPN sul server", "Usare firewall con regole personalizzate"}, 'B', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){47, "Cos'è il DNS Spoofing?", 
        {"Una tecnica per proteggere i server DNS dalle minacce", "Una manipolazione dei record DNS per reindirizzare gli utenti a siti malevoli", 
         "Un attacco per rubare credenziali di accesso ai siti web", "Un protocollo di sicurezza avanzato per la navigazione web"}, 'B', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){48, "Come funziona un attacco XSS (Cross-Site Scripting)?", 
        {"Un attaccante inserisce codice JavaScript malevolo in una pagina web per colpire gli utenti", "Un hacker modifica il routing dei pacchetti per intercettare traffico web", 
         "Un sistema viene colpito da un attacco DDoS su larga scala", "Un utente viene ingannato tramite phishing per rivelare credenziali"}, 'A', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){49, "Quale componente di rete assegna dinamicamente indirizzi IP ai dispositivi?", 
        {"DNS", "DHCP", 
         "ARP", "NAT"}, 'B', "Crittografia e Hashing"};
    
    questions[total_questions++] = (Question){50, "Il protocollo SNMP è usato principalmente per:", 
        {"Monitorare e gestire dispositivi di rete", "Crittografare la comunicazione tra client e server", 
         "Configurare firewall aziendali", "Proteggere le password utente"}, 'A', "Crittografia e Hashing"};
}

void initialize_player() {
    strcpy(current_player.name, "Giocatore");
    current_player.total_points = 0;
    current_player.rank = 0;
    current_player.questions_answered = 0;
    current_player.correct_answers = 0;
}

void save_game() {
    FILE *file = fopen(SAVE_FILE, "wb");
    if (file != NULL) {
        fwrite(&current_player, sizeof(Player), 1, file);
        fclose(file);
    }
}

void load_game() {
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file != NULL) {
        fread(&current_player, sizeof(Player), 1, file);
        fclose(file);
    } else {
        initialize_player();
    }
}

void display_stats() {
    clear_screen();
    printf("=== STATISTICHE GIOCATORE ===\n");
    printf("Nome: %s\n", current_player.name);
    printf("Punteggio totale: %d\n", current_player.total_points);
    printf("Rank attuale: %s\n", ranks[current_player.rank]);
    printf("Prossimo rank: %s (%d punti necessari)\n", 
           (current_player.rank < total_ranks-1) ? ranks[current_player.rank+1] : "MAX", 
           (current_player.rank < total_ranks-1) ? (current_player.rank+1)*RANK_POINTS - current_player.total_points : 0);
    printf("Domande totali: %d\n", current_player.questions_answered);
    printf("Risposte corrette: %d (%.1f%%)\n", current_player.correct_answers, 
           current_player.questions_answered > 0 ? (float)current_player.correct_answers/current_player.questions_answered*100 : 0);
    wait_for_enter();
}

void update_rank() {
    int new_rank = current_player.total_points / RANK_POINTS;
    if (new_rank >= total_ranks) {
        new_rank = total_ranks - 1;
    }
    
    if (new_rank > current_player.rank) {
        clear_screen();
        printf("=== PROMOZIONE DI RANK! ===\n");
        printf("Complimenti! Sei passato da %s a %s!\n", ranks[current_player.rank], ranks[new_rank]);
        current_player.rank = new_rank;
        wait_for_enter();
    }
}

void play_game() {
    int selected_questions[QUESTIONS_PER_GAME];
    int score = 0;
    
    // Select random questions
    for (int i = 0; i < QUESTIONS_PER_GAME; i++) {
        int question_index;
        int duplicate;
        
        do {
            duplicate = 0;
            question_index = rand() % total_questions;
            
            // Check if this question was already selected
            for (int j = 0; j < i; j++) {
                if (selected_questions[j] == question_index) {
                    duplicate = 1;
                    break;
                }
            }
        } while (duplicate);
        
        selected_questions[i] = question_index;
    }
    
    // Ask each question
    for (int i = 0; i < QUESTIONS_PER_GAME; i++) {
        Question q = questions[selected_questions[i]];
        char answer;
        int valid_input;
        
        do {
            clear_screen();
            printf("=== DOMANDA %d/%d ===\n", i+1, QUESTIONS_PER_GAME);
            printf("Sezione: %s\n", q.section);
            printf("Punteggio attuale: %d\n", score);
            printf("Prossimo rank: %d/%d punti\n", current_player.total_points + score, (current_player.rank+1)*RANK_POINTS);
            printf("\n%s\n\n", q.question);
            
            for (int j = 0; j < 4; j++) {
                printf("%c) %s\n", 'A' + j, q.options[j]);
            }
            
            printf("\nLa tua risposta (A-D): ");
            answer = toupper(getchar());
            while(getchar() != '\n'); // Clear input buffer
            
            valid_input = (answer >= 'A' && answer <= 'D');
            if (!valid_input) {
                printf("Input non valido. Per favore inserisci A, B, C o D.\n");
                wait_for_enter();
            }
        } while (!valid_input);
        
        if (answer == q.correct_answer) {
            printf("\nEsatto! +%d punti\n", POINTS_PER_QUESTION);
            score += POINTS_PER_QUESTION;
            current_player.correct_answers++;
        } else {
            printf("\nSbagliato! La risposta corretta era %c.\n", q.correct_answer);
        }
        
        current_player.questions_answered++;
        wait_for_enter();
    }
    
    // Update player stats
    current_player.total_points += score;
    update_rank();
    save_game();
    
    // Show results
    clear_screen();
    printf("=== RISULTATI FINALI ===\n");
    printf("Hai totalizzato %d punti in questa sessione!\n", score);
    printf("Punteggio totale: %d\n", current_player.total_points);
    printf("Rank attuale: %s\n", ranks[current_player.rank]);
    printf("Risposte corrette: %d/%d\n", current_player.correct_answers, current_player.questions_answered);
    
    if (current_player.rank < total_ranks-1) {
        int points_needed = (current_player.rank+1)*RANK_POINTS - current_player.total_points;
        printf("\nTi mancano %d punti per il prossimo rank (%s)\n", 
               points_needed, ranks[current_player.rank+1]);
    } else {
        printf("\nHai raggiunto il massimo rank! Complimenti!\n");
    }
    
    wait_for_enter();
}

void main_menu() {
    int choice;
    
    do {
        clear_screen();
        printf("=== CYBERSECURITY QUIZ GAME ===\n");
        printf("1. Avvia gioco\n");
        printf("2. Statistiche\n");
        printf("3. Esci\n");
        printf("\nSeleziona un'opzione: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear invalid input
            choice = 0; // Force default case
        }
        while(getchar() != '\n'); // Clear input buffer
        
        switch(choice) {
            case 1:
                play_game();
                break;
            case 2:
                display_stats();
                break;
            case 3:
                printf("Arrivederci!\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
                wait_for_enter();
        }
    } while (choice != 3);
}

int main() {
    srand(time(NULL)); // Initialize random seed
    
    load_questions();
    load_game();
    
    clear_screen();
    printf("Benvenuto al Cybersecurity Quiz Game!\n");
    printf("Inserisci il tuo nome: ");
    fgets(current_player.name, sizeof(current_player.name), stdin);
    current_player.name[strcspn(current_player.name, "\n")] = '\0'; // Remove newline
    
    if (strlen(current_player.name) == 0) {
        strcpy(current_player.name, "Giocatore");
    }
    
    main_menu();
    
    return 0;
}
