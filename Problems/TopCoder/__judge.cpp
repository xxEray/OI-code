// This is for judging, not a problem.

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <windows.h>

#define ProgramName "TreasureOfWinedag"
#define MethodName "solvePuzzle"
#define ResultType "int"
#define ClassName ProgramName

const int N = 100000 + 5;

std::string data[N], ans[N];
char tmp[N];
int total, passed;

int digitof(int x) {
	int cnt = 0;
	while(x) cnt++, x /= 10;
	return cnt ? cnt : 1;
}

int main() {
	FILE *fdata = fopen("_data.txt", "r");
	if(fdata == NULL) { perror("_data.txt"); return 0; }
	printf("Loading datas...");
	int i = 1;
	fscanf(fdata, "%*[ \t\n]");
	while(true) {
		fscanf(fdata, "%[^\t]", tmp), data[i] = tmp;
		fscanf(fdata, "%*[\t]");
		fscanf(fdata, "%[^\t]", tmp), ans[i] = tmp;
		fscanf(fdata, "%*[\t]");
		fscanf(fdata, "%[^ \t\n]", tmp);
		if(strcmp(tmp, "Passed")) { printf("\n[ERROR] An error occurs while loading data: line %d without null lines\n", i); return 0; }
		fscanf(fdata, "%*[ \n\t]");
		i++;
		if(feof(fdata)) break;
	}
	total = --i;
	fclose(fdata);
	int digit = digitof(total);
	printf(" %d data%s loaded.\n", total, total > 1 ? "s" : "");
	FILE *flog = fopen("_rewrite.txt", "w");
	for(i = 1; i <= total; i++) {
		printf("test #%0*d/%d: ", digit, i, total);
		system("copy " ProgramName ".cpp " ProgramName "-copy.cpp /Y > nul");
		FILE *fout = fopen(ProgramName "-copy.cpp", "a");
		fprintf(fout, "\n");
		fprintf(fout, "\n");
		fprintf(fout, "int main() {\n");
		fprintf(fout, "\t" ClassName " T;\n");
		fprintf(fout, ("\tif(!(T." MethodName "(" + data[i] + ") == (" ResultType ")" + ans[i] + "))\n").c_str());
		fprintf(fout, "\t\treturn 1;\n");
		fprintf(fout, "\telse return 0;\n");
		fprintf(fout, "}");
		fclose(fout);
		int state = system("g++ " ProgramName "-copy.cpp -o " ProgramName "-copy.exe -O2 -fexec-charset=GBK -std=c++17 -Wl,--stack=102400000 > nul 2> nul");
		if(state) {
			puts("");
			bool successful = false;
			int tried;
			for(int j = 1; j <= 5; j++) {
				printf("    Error while compiling, try again (%d/5)\n", j);
				Sleep(200);
				state = system("g++ " ProgramName "-copy.cpp -o " ProgramName "-copy.exe -O2 -fexec-charset=GBK -std=c++17 -Wl,--stack=102400000 > nul 2> nul");
				if(!state) { successful = true; tried = j; break; }
			}
			if(successful) {
				printf("    Compile success, judge result: ");
				fprintf(flog, "test #%d: Tried %d time%s.\n", i, tried, (tried == 1 ? "" : "s"));
				fflush(flog);
			} else {
				printf("    Compile Failed, skipped this test, read _rewrite.txt for more info.\n");
				fprintf(flog, "\n");
				fprintf(flog, "test #%d: Compile Failed\n", i);
				fprintf(flog, "    Input: %s\n", data[i].c_str());
				fprintf(flog, "    Answer: %s\n", ans[i].c_str());
				fprintf(flog, "    Compile Info:\n");
				fprintf(flog, "==================================\n");
				fclose(flog);
				system("g++ " ProgramName "-copy.cpp -o " ProgramName "-copy.exe -O2 -fexec-charset=GBK -std=c++17 -Wl,--stack=102400000 2>> _rewrite.txt");
				flog = fopen("_rewrite.txt", "a");
				fprintf(flog, "==================================\n");
				fprintf(flog, "\n");
				fflush(flog);
				continue;
			}
		}
		state = system(ProgramName "-copy");
		if(state == 0) {
			passed++;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
			puts("Accepted");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		} else if(state == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
			puts("Wrong Answer");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			fprintf(flog, "test #%d: Wrong Answer\n", i);
			fprintf(flog, "    Input: %s\n", data[i].c_str());
			fprintf(flog, "    Answer: %s\n", ans[i].c_str());
			fflush(flog);
		} else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
			puts("Runtime Error");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			fprintf(flog, "test #%d: Runtime Error (code=%d)\n", i, state);
			fprintf(flog, "    Input: %s\n", data[i].c_str());
			fprintf(flog, "    Answer: %s\n", ans[i].c_str());
			fflush(flog);

		}
	}
	fclose(flog);
	if(passed == total) printf("Passed all test cases.\n");
	else printf("Passed %d/%d test case%s.\n", passed, total, total > 1 ? "s" : "");
	system("del /q " ProgramName "-copy.cpp");
	system("del /q " ProgramName "-copy.exe");
	system("pause");
	return 0;
}