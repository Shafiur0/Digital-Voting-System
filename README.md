# Digital-Voting-System
Digital Voting System
Project Title

Digital Voting System (Using C, with Data Structures)

📖 Project Description

This project is a menu-driven C program that simulates a digital voting system. It allows candidates to be added/removed, voters to be registered/deleted, and then manages the voting process using fundamental data structures such as arrays, linked lists, stacks, and queues.

The system ensures that:

Only registered voters can vote.

Voters vote in the order they arrive (queue).

Every vote is recorded, and can also be undone (stack).

Results can be displayed at any time.

⚙️ Core Features

Candidate Management (Dynamic Array)

Add new candidates.

Remove existing candidates.

Store and update vote counts.

Dynamic resizing of the candidate list using malloc and realloc.

Voter Management (Linked List)

Register new voters by ID.

Delete voters by ID.

View all registered voters.

Prevents duplicate registration.

Voting Queue (Queue - FIFO)

Voters are placed in a queue when they come to vote.

Voting is processed in First-In-First-Out (FIFO) order.

Ensures fairness in the voting line.

Vote Recording & Undo (Stack - LIFO)

Each vote is stored in a stack for auditing.

If needed, the last vote can be undone (LIFO).

Ensures transparency and correction of mistakes.

Result Display

Show all candidates and their current vote counts.

Provides live election results.

🏗️ Data Structures Used

Dynamic Array (Candidates): Stores candidates with flexible resizing.

Linked List (Voters): Stores registered voters for easy insertion/deletion.

Queue (Voting Line): Manages voters waiting to vote in order.

Stack (Votes): Stores votes so the last one can be undone.

📊 Menu Options in Main Program

Add Candidate

Remove Candidate

Register Voter

Delete Voter

Enqueue Voter for Voting

Process Vote (Dequeue & Vote)

Undo Last Vote

View Candidates and Results

View Registered Voters

Exit

🖥️ How the System Works (Flow)

Admin adds candidates (e.g., "Alice", "Bob").

Voters are registered with unique IDs.

When voting starts:

Voters are placed in a queue.

Each voter, when their turn comes, selects a candidate.

Vote is recorded and pushed onto the stack.

If a mistake occurs, the last vote can be undone.

At any point, the admin can view live results.

🎯 Purpose of the Project

Demonstrates how different data structures (array, linked list, stack, queue) can work together in a real-world application.

Simulates a real digital voting system with fairness (queue) and transparency (stack undo).

Beginner-friendly, but covers memory allocation, pointer usage, and structured programming in C.

👉 In short, this is a Digital Voting Simulation that showcases data structure applications in C programming while solving a real-life problem in a simple way.
