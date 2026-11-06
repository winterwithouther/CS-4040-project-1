## Build and Run

Compile the source code:

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o sorting
```

Run the executable:

```bash
./sorting
```

## Experimental Method

The experiments use the following input sizes:

`n = {10, 100, 1000, 2000, 5000, 10000, 20000}`

For every input size, two key ranges are tested: `k = n` and `k = 100n`.

Each configuration runs five trials using freshly generated random arrays. All three algorithms receive identical copies of the input. Execution times are measured using `std::chrono::steady_clock`, and the median of the five trials is reported in milliseconds.

Each sorting result is verified against `std::sort()`.

## Testing

The project includes the following tests:

- `TestMeInsertionSort()`
- `TestMeQuickSort()`
- `TestMeCountingSort()`
- `TestCountingSortStability()`

## Development Environment

- **Language:** C++17
- **Compiler:** GNU g++ 13.3.0
- **Operating System:** Ubuntu Linux through WSL
- **IDE:** Visual Studio Code

## Report

A PDF report is attached under this repository that contains the runtime table, graph, and a discussion about the time complexities.