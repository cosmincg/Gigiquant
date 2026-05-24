# GigiQuant

A C program that analyzes stock data using classic financial algorithms as an interview "game". Built as a university project.

## What it does

Given an input file with stock prices, it automatically detects which task to run based on the file number and writes the results to an output file.

- **Task 1 (data01–05):** Computes the Sharpe Ratio using a linked list of daily portfolio values
- **Task 2 (data06–10):** Detects arbitrage opportunities across 3 markets using stacks
- **Task 3 (data11–15):** Finds mirrored stock pairs using a binary tree of price movements for each day
- **Task 4 (data16–20):** Computes the probability of reaching a target price after K days using a Markov chain

## File structure
```
main.c              — entry point, dispatches to the right task
list.c / list.h     — linked list, used for Task 1
stack.c / stack.h   — stack, used for Task 2
tree.c / tree.h     — binary tree, used for Task 3
markov.c / markov.h — Markov chain graph and probability computation, used for Task 4
numberfile.c        — function to extract the task number from the filename
```
## How to build and run
```
In the src folder, use gcc -o gigiquant main.c list.c stack.a tree.c markov.c numberfile.c -lm
In the GigiQuant folder, use ./checker -i
In the options, change the executable path to src/gigiquant and the source path to ./src
```

## Limitations
- **Task 3** has a style issue due to the use of strtok
- **Task 4** has a memory limit issue because the probability is calculated iteratively instead of using matrix-row vector multiplication to directly find the value for day K
- There is no input validation, which can result in crashes if the values are not valid
