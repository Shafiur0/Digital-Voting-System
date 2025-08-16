#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store candidate information (name and vote count)
typedef struct {
    char name[50];  // Candidate's name
    int votes;      // Number of votes for the candidate
} Candidate;

// Global variables for dynamic array of candidates
Candidate *candidates = NULL;  // Pointer to dynamic array of candidates
int num_candidates = 0;        // Current number of candidates
int capacity = 0;              // Current capacity of the array

// Initialize the candidate array with a given initial capacity
void init_candidates(int init_cap) {
    capacity = init_cap;  // Set initial capacity
    candidates = (Candidate*)malloc(capacity * sizeof(Candidate));  // Allocate memory
}

// Add a new candidate to the array
void add_candidate(char* name) {
    // Check if array is full; if so, resize it
    if (num_candidates == capacity) {
        capacity = capacity == 0 ? 1 : capacity * 2;  // Double capacity or set to 1 if empty
        candidates = (Candidate*)realloc(candidates, capacity * sizeof(Candidate));  // Reallocate memory
    }
    strcpy(candidates[num_candidates].name, name);  // Copy candidate name
    candidates[num_candidates].votes = 0;           // Initialize votes to 0
    num_candidates++;                               // Increment candidate count
}

// Find a candidate by name, return index or -1 if not found
int find_candidate(char* name) {
    for (int i = 0; i < num_candidates; i++) {
        if (strcmp(candidates[i].name, name) == 0) return i;  // Return index if name matches
    }
    return -1;  // Candidate not found
}

// Remove a candidate by name
void remove_candidate(char* name) {
    int idx = find_candidate(name);  // Find candidate index
    if (idx == -1) return;          // Exit if candidate not found
    // Shift elements to fill the gap
    for (int i = idx; i < num_candidates - 1; i++) {
        candidates[i] = candidates[i + 1];
    }
    num_candidates--;  // Decrease candidate count
}

// Display all candidates and their vote counts
void display_candidates() {
    printf("Candidates and Results:\n");
    for (int i = 0; i < num_candidates; i++) {
        printf("%d. %s - Votes: %d\n", i + 1, candidates[i].name, candidates[i].votes);
    }
}

// Structure for a voter node in the linked list
typedef struct Voter {
    char id[20];          // Voter ID
    struct Voter *next;   // Pointer to next voter
} Voter;

Voter *voter_head = NULL;  // Head of the voter linked list

// Add a new voter to the linked list
void insert_voter(char* id) {
    Voter *new_v = (Voter*)malloc(sizeof(Voter));  // Allocate memory for new voter
    strcpy(new_v->id, id);                        // Copy voter ID
    new_v->next = voter_head;                     // Link to current head
    voter_head = new_v;                           // Update head to new voter
}

// Check if a voter ID exists in the linked list
int search_voter(char* id) {
    Voter *curr = voter_head;  // Start at head
    while (curr) {
        if (strcmp(curr->id, id) == 0) return 1;  // Return 1 if ID found
        curr = curr->next;                        // Move to next voter
    }
    return 0;  // ID not found
}

// Delete a voter from the linked list
void delete_voter(char* id) {
    Voter *curr = voter_head;  // Start at head
    Voter *prev = NULL;        // Previous node pointer
    while (curr) {
        if (strcmp(curr->id, id) == 0) {  // Found voter
            if (prev) prev->next = curr->next;  // Link previous to next
            else voter_head = curr->next;       // Update head if deleting first node
            free(curr);                         // Free memory
            return;
        }
        prev = curr;           // Update previous
        curr = curr->next;     // Move to next
    }
}

// Display all registered voters
void display_voters() {
    printf("Registered Voters:\n");
    Voter *curr = voter_head;  // Start at head
    while (curr) {
        printf("%s\n", curr->id);  // Print voter ID
        curr = curr->next;         // Move to next
    }
}

// Structure to store a vote (candidate index and voter ID)
typedef struct Vote {
    int cand_idx;      // Index of candidate voted for
    char voter_id[20]; // ID of voter
} Vote;

// Structure for a stack node to store votes
typedef struct StackNode {
    Vote vote;              // Vote data
    struct StackNode *next; // Pointer to next node
} StackNode;

StackNode *stack_top = NULL;  // Top of the vote stack

// Check if the vote stack is empty
int is_stack_empty() {
    return stack_top == NULL;  // Return true if stack is empty
}

// Push a vote onto the stack
void push_vote(int cand_idx, char* voter_id) {
    StackNode *new_n = (StackNode*)malloc(sizeof(StackNode));  // Allocate memory
    new_n->vote.cand_idx = cand_idx;                          // Set candidate index
    strcpy(new_n->vote.voter_id, voter_id);                   // Copy voter ID
    new_n->next = stack_top;                                  // Link to current top
    stack_top = new_n;                                        // Update top
}

// Pop and return the last vote from the stack
Vote pop_vote() {
    if (is_stack_empty()) {  // Check if stack is empty
        Vote v;
        v.cand_idx = -1;     // Return invalid vote if empty
        return v;
    }
    StackNode *temp = stack_top;  // Store current top
    stack_top = stack_top->next;  // Move top to next
    Vote v = temp->vote;          // Get vote data
    free(temp);                   // Free memory
    return v;                     // Return vote
}

// Peek at the last vote without removing it
Vote peek_vote() {
    if (is_stack_empty()) {  // Check if stack is empty
        Vote v;
        v.cand_idx = -1;     // Return invalid vote if empty
        return v;
    }
    return stack_top->vote;  // Return top vote
}

// Structure for a queue node to store voters waiting to vote
typedef struct QueueNode {
    char id[20];             // Voter ID
    struct QueueNode *next;  // Pointer to next node
} QueueNode;

QueueNode *queue_front = NULL;  // Front of the voter queue
QueueNode *queue_rear = NULL;   // Rear of the voter queue

// Check if the queue is empty
int is_queue_empty() {
    return queue_front == NULL;  // Return true if queue is empty
}

// Add a voter to the end of the queue
void enqueue_voter(char* id) {
    QueueNode *new_n = (QueueNode*)malloc(sizeof(QueueNode));  // Allocate memory
    strcpy(new_n->id, id);                                    // Copy voter ID
    new_n->next = NULL;                                       // Set next to NULL
    if (queue_rear) queue_rear->next = new_n;                 // Link to rear if exists
    else queue_front = new_n;                                 // Set as front if queue empty
    queue_rear = new_n;                                       // Update rear
}

// Remove and return the voter at the front of the queue
char* dequeue_voter() {
    if (is_queue_empty()) return NULL;  // Return NULL if queue empty
    QueueNode *temp = queue_front;      // Store front node
    queue_front = queue_front->next;    // Move front to next
    if (!queue_front) queue_rear = NULL; // Update rear if queue becomes empty
    char* id = (char*)malloc(20 * sizeof(char));  // Allocate memory for ID
    strcpy(id, temp->id);                 // Copy voter ID
    free(temp);                           // Free node memory
    return id;                            // Return voter ID
}

// View the voter at the front of the queue
char* front_voter() {
    if (is_queue_empty()) return NULL;  // Return NULL if queue empty
    return queue_front->id;             // Return front voter ID
}

// Main function with menu-driven interface
int main() {
    init_candidates(5);  // Initialize candidate array with capacity 5
    int choice;
    do {
        // Display menu options
        printf("\nDigital Voting System Menu:\n");
        printf("1. Add Candidate\n");
        printf("2. Remove Candidate\n");
        printf("3. Register Voter\n");
        printf("4. Delete Voter\n");
        printf("5. Enqueue Voter for Voting\n");
        printf("6. Process Vote (Dequeue and Vote)\n");
        printf("7. Undo Last Vote\n");
        printf("8. View Candidates and Results\n");
        printf("9. View Voters\n");
        printf("10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {  // Add a new candidate
                char name[50];
                printf("Enter candidate name: ");
                scanf("%s", name);
                add_candidate(name);
                printf("Candidate added.\n");
                break;
            }
            case 2: {  // Remove a candidate
                char name[50];
                printf("Enter candidate name to remove: ");
                scanf("%s", name);
                remove_candidate(name);
                printf("Candidate removed if existed.\n");
                break;
            }
            case 3: {  // Register a new voter
                char id[20];
                printf("Enter voter ID: ");
                scanf("%s", id);
                if (search_voter(id)) {
                    printf("Voter already registered.\n");
                } else {
                    insert_voter(id);
                    printf("Voter registered.\n");
                }
                break;
            }
            case 4: {  // Delete a voter
                char id[20];
                printf("Enter voter ID to delete: ");
                scanf("%s", id);
                delete_voter(id);
                printf("Voter deleted if existed.\n");
                break;
            }
            case 5: {  // Add voter to voting queue
                char id[20];
                printf("Enter voter ID to enqueue: ");
                scanf("%s", id);
                if (!search_voter(id)) {
                    printf("Voter not registered.\n");
                } else {
                    enqueue_voter(id);
                    printf("Voter enqueued.\n");
                }
                break;
            }
            case 6: {  // Process a vote
                if (is_queue_empty()) {
                    printf("No voters in queue.\n");
                    break;
                }
                printf("Next voter in queue: %s\n", front_voter());
                char* id = dequeue_voter();  // Get voter from queue
                printf("Voter %s is now voting.\n", id);
                display_candidates();        // Show candidates
                int cand;
                printf("Enter candidate number to vote for: ");
                scanf("%d", &cand);
                cand--;  // Adjust to 0-based index
                if (cand < 0 || cand >= num_candidates) {
                    printf("Invalid candidate.\n");
                    free(id);
                    break;
                }
                candidates[cand].votes++;    // Increment candidate's vote count
                push_vote(cand, id);         // Record vote in stack
                printf("Vote recorded.\n");
                free(id);                    // Free allocated ID
                break;
            }
            case 7: {  // Undo the last vote
                Vote v = peek_vote();
                if (v.cand_idx == -1) {
                    printf("No votes to undo.\n");
                    break;
                }
                printf("Undoing vote for %s by %s\n", candidates[v.cand_idx].name, v.voter_id);
                v = pop_vote();              // Remove vote from stack
                candidates[v.cand_idx].votes--;  // Decrease candidate's vote count
                break;
            }
            case 8:  // Display candidates and votes
                display_candidates();
                break;
            case 9:  // Display registered voters
                display_voters();
                break;
            case 10:  // Exit program
                printf("Exiting system.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 10);

    // Free allocated memory for candidates
    free(candidates);
    // Note: Memory for linked list, stack, and queue nodes should also be freed,
    // but omitted here for simplicity to avoid complex traversal
    return 0;
}