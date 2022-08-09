// main.h 
// main file for turing simulator

#include <stdio.h>

#define length(str) sizeof(str) / sizeof(str[0])

int main() {
    
    FILE *fp;
    char buffer[255]; // buffer for lines
	int res; // result of reading lines
	int i;
	int state1[100], sym1[100], state2[100], 
		sym2[100], dir[100]; // symbols and directions
	int prog_size; // size of program.
	int machine_state;
	int tape[256];
	int head_pos;

    // Read from the file and add to arrays of symbols.
    fp = fopen("data/program.tur", "r");
	i = 0;
	prog_size = 0;
	while (1) {
		res = fscanf(fp, "%d %d %d %d %d\n", 
			&state1[i], &sym1[i], &state2[i], &sym2[i], &dir[i]);
		if (feof(fp)) {
			break;
		}
		i += 1;
		prog_size += 1;
		// fill the rest of the arrays with a random number.
		for (int j = i; j < length(state1); j++) {
			state1[j] = 69;
			sym1[j] = 69;
			state2[j] = 69;
			sym2[j] = 69;
			dir[j] = 69;
		}
	}
	fclose(fp);

	// Initialize the tape.
	// Loop through the file and copy symbols.
	// If the file ends, fill the rest with blanks.
	fp = fopen("data/input.tape", "r");
	i = 0;
	while (1) {
		fscanf(fp, "%d\n", &tape[i]);
		i++;
		if (feof(fp)) {
			for (int j = i; j < length(tape); j++) {
				tape[j] = 2;
			}
			break;
		}
	}
	fclose(fp);

	// Execute instructions until halt state (-1) is found.
	machine_state = 0;
	head_pos = 0;
	printf("state = %d head_pos = %d\n", machine_state, head_pos);
	for (int j = 0; j < length(tape); j++) {
		if (j < 50) printf("%d", tape[j]);
	}
	while(machine_state != -1) {
		// Find index corresponding to current state and symbol.
		for (int j = 0; j < length(state1); j++) {
			if ((machine_state == state1[j])
				& (tape[head_pos] == sym1[j])) {
				printf("%d %d %d %d %d\n",
				state1[j], sym1[j], state2[j], sym2[j],
				dir[j]);
				// Update machine state.
				machine_state = state2[j];
				tape[head_pos] = sym2[j];
				head_pos += dir[j];
				break;
			}
		}
		printf("state = %d head_pos = %d\n", machine_state, head_pos);
		for (int j = 0; j < length(tape); j++) {
			if (j < 50) printf("%d", tape[j]);
		}
		printf("\n");
	}

    return 0;
}
